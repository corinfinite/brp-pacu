/* GTK+ Integration for the Mac OS X Menubar.
 *
 * Copyright (C) 2007 Pioneer Research Center USA, Inc.
 * Copyright (C) 2007, 2008 Imendio AB
 *
 * For further information, see:
 * http://developer.imendio.com/projects/gtk-macosx/menubar
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; version 2.1
 * of the License.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "config.h"

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <gdk/gdkquartz.h>
#include <Carbon/Carbon.h>
#import <Cocoa/Cocoa.h>

#include "ige-mac-menu.h"
#include "ige-mac-private.h"

/* TODO
 *
 * - Adding a standard Window menu (Minimize etc)?
 * - Sync reordering items? Does that work now?
 * - Create on demand? (can this be done with gtk+? ie fill in menu
     items when the menu is opened)
 *
 * - Deleting a menu item that is not the last one in a menu doesn't work
 */

#define IGE_QUARTZ_MENU_CREATOR 'IGEC'
#define IGE_QUARTZ_ITEM_WIDGET  'IWID'

#define IGE_MAC_KEY_HANDLER     "ige-mac-key-handler"

static MenuID   last_menu_id;
static gboolean global_key_handler_enabled = TRUE;

static void   sync_menu_shell (GtkMenuShell *menu_shell,
                               MenuRef       carbon_menu,
                               gboolean      toplevel,
                               gboolean      debug);

/* A category that exposes the protected carbon event for an NSEvent. */
@interface NSEvent (GdkQuartzNSEvent)
- (void *)gdk_quartz_event_ref;
@end

@implementation NSEvent (GdkQuartzNSEvent)
- (void *)gdk_quartz_event_ref
{
   return _eventRef;
}
@end

static gboolean
menu_flash_off_cb (gpointer data)
{
   /* Disable flash by flashing a non-existing menu id. */
   FlashMenuBar (last_menu_id + 1);

   return FALSE;
}

/*
 * utility functions
 */

static GtkWidget *
find_menu_label (GtkWidget *widget)
{
   GtkWidget *label = NULL;

   if (GTK_IS_LABEL (widget))
      return widget;

   if (GTK_IS_CONTAINER (widget))
   {
      GList *children;
      GList *l;

      children = gtk_container_get_children (GTK_CONTAINER (widget));

      for (l = children; l; l = l->next)
      {
         label = find_menu_label (l->data);
         if (label)
            break;
      }

      g_list_free (children);
   }

   return label;
}

static const gchar *
get_menu_label_text (GtkWidget  *menu_item,
                     GtkWidget **label)
{
   GtkWidget *my_label;

   my_label = find_menu_label (menu_item);
   if (label)
      *label = my_label;

   if (my_label)
      return gtk_label_get_text (GTK_LABEL (my_label));

   return NULL;
}

static gboolean
accel_find_func (GtkAccelKey *key,
                 GClosure    *closure,
                 gpointer     data)
{
   return (GClosure *) data == closure;
}


/*
 * CarbonMenu functions
 */

typedef struct
{
   MenuRef menu;
guint   toplevel :
   1;
} CarbonMenu;

static GQuark carbon_menu_quark = 0;

static CarbonMenu *
carbon_menu_new (void)
{
   return g_slice_new0 (CarbonMenu);
}

static void
carbon_menu_free (CarbonMenu *menu)
{
   g_slice_free (CarbonMenu, menu);
}

static CarbonMenu *
carbon_menu_get (GtkWidget *widget)
{
   return g_object_get_qdata (G_OBJECT (widget), carbon_menu_quark);
}

static void
carbon_menu_connect (GtkWidget *menu,
                     MenuRef    menuRef,
                     gboolean   toplevel)
{
   CarbonMenu *carbon_menu = carbon_menu_get (menu);

   if (!carbon_menu)
   {
      carbon_menu = carbon_menu_new ();

      g_object_set_qdata_full (G_OBJECT (menu), carbon_menu_quark,
                               carbon_menu,
                               (GDestroyNotify) carbon_menu_free);
   }

   carbon_menu->menu     = menuRef;
   carbon_menu->toplevel = toplevel;
}


/*
 * CarbonMenuItem functions
 */

typedef struct
{
   MenuRef        menu;
   MenuItemIndex  index;
   MenuRef        submenu;
   GClosure      *accel_closure;
} CarbonMenuItem;

static GQuark carbon_menu_item_quark = 0;

static CarbonMenuItem *
carbon_menu_item_new (void)
{
   return g_slice_new0 (CarbonMenuItem);
}

static void
carbon_menu_item_free (CarbonMenuItem *menu_item)
{
   if (menu_item->accel_closure)
      g_closure_unref (menu_item->accel_closure);

   g_slice_free (CarbonMenuItem, menu_item);
}

static CarbonMenuItem *
carbon_menu_item_get (GtkWidget *widget)
{
   return g_object_get_qdata (G_OBJECT (widget), carbon_menu_item_quark);
}

static void
carbon_menu_item_update_state (CarbonMenuItem *carbon_item,
                               GtkWidget      *widget)
{
   gboolean sensitive;
   gboolean visible;
   UInt32   set_attrs = 0;
   UInt32   clear_attrs = 0;

   g_object_get (widget,
                 "sensitive", &sensitive,
                 "visible",   &visible,
                 NULL);

   if (!sensitive)
      set_attrs |= kMenuItemAttrDisabled;
   else
      clear_attrs |= kMenuItemAttrDisabled;

   if (!visible)
      set_attrs |= kMenuItemAttrHidden;
   else
      clear_attrs |= kMenuItemAttrHidden;

   ChangeMenuItemAttributes (carbon_item->menu, carbon_item->index,
                             set_attrs, clear_attrs);
}

static void
carbon_menu_item_update_active (CarbonMenuItem *carbon_item,
                                GtkWidget      *widget)
{
   gboolean active;

   g_object_get (widget,
                 "active", &active,
                 NULL);

   CheckMenuItem (carbon_item->menu, carbon_item->index,
                  active);
}

static void
carbon_menu_item_update_submenu (CarbonMenuItem *carbon_item,
                                 GtkWidget      *widget)
{
   GtkWidget *submenu;

   submenu = gtk_menu_item_get_submenu (GTK_MENU_ITEM (widget));

   if (submenu)
   {
      const gchar *label_text;
      CFStringRef  cfstr = NULL;

      label_text = get_menu_label_text (widget, NULL);
      if (label_text)
         cfstr = CFStringCreateWithCString (NULL, label_text,
                                            kCFStringEncodingUTF8);

      CreateNewMenu (++last_menu_id, 0, &carbon_item->submenu);
      SetMenuTitleWithCFString (carbon_item->submenu, cfstr);
      SetMenuItemHierarchicalMenu (carbon_item->menu, carbon_item->index,
                                   carbon_item->submenu);

      /* FIXME: This makes it possible to hide toplevel menu items
       * completely, but it only works if you hide the menu item before
       * setting up the menu, not dynamically afterwards.
       */
      if (!GTK_WIDGET_VISIBLE (widget))
      {
         ChangeMenuAttributes (carbon_item->submenu, kMenuAttrHidden, 0);
      }

      sync_menu_shell (GTK_MENU_SHELL (submenu), carbon_item->submenu, FALSE, FALSE);

      if (cfstr)
         CFRelease (cfstr);
   }
   else
   {
      SetMenuItemHierarchicalMenu (carbon_item->menu, carbon_item->index,
                                   NULL);
      carbon_item->submenu = NULL;
   }
}

static void
carbon_menu_item_update_label (CarbonMenuItem *carbon_item,
                               GtkWidget      *widget)
{
   const gchar *label_text;
   CFStringRef  cfstr = NULL;

   label_text = get_menu_label_text (widget, NULL);
   if (label_text)
      cfstr = CFStringCreateWithCString (NULL, label_text,
                                         kCFStringEncodingUTF8);

   SetMenuItemTextWithCFString (carbon_item->menu, carbon_item->index,
                                cfstr);

   if (cfstr)
      CFRelease (cfstr);
}

static void
carbon_menu_item_update_accelerator (CarbonMenuItem *carbon_item,
                                     GtkWidget      *widget)
{
   GtkWidget *label;

   get_menu_label_text (widget, &label);

   if (GTK_IS_ACCEL_LABEL (label) &&
         GTK_ACCEL_LABEL (label)->accel_closure)
   {
      GtkAccelKey *key;

      key = gtk_accel_group_find (GTK_ACCEL_LABEL (label)->accel_group,
                                  accel_find_func,
                                  GTK_ACCEL_LABEL (label)->accel_closure);

      if (key            &&
            key->accel_key &&
            key->accel_flags & GTK_ACCEL_VISIBLE)
      {
         GdkDisplay      *display = gtk_widget_get_display (widget);
         GdkKeymap       *keymap  = gdk_keymap_get_for_display (display);
         GdkKeymapKey    *keys;
         gint             n_keys;

         if (gdk_keymap_get_entries_for_keyval (keymap, key->accel_key,
                                                &keys, &n_keys))
         {
            UInt8 modifiers = 0;

            SetMenuItemCommandKey (carbon_item->menu, carbon_item->index,
                                   true, keys[0].keycode);

            g_free (keys);

            if (key->accel_mods)
            {
               if (key->accel_mods & GDK_SHIFT_MASK)
                  modifiers |= kMenuShiftModifier;

               if (key->accel_mods & GDK_MOD1_MASK)
                  modifiers |= kMenuOptionModifier;
            }

            if (!(key->accel_mods & GDK_CONTROL_MASK))
            {
               modifiers |= kMenuNoCommandModifier;
            }

            SetMenuItemModifiers (carbon_item->menu, carbon_item->index,
                                  modifiers);

            return;
         }
      }
   }

   /*  otherwise, clear the menu shortcut  */
   SetMenuItemModifiers (carbon_item->menu, carbon_item->index,
                         kMenuNoModifiers | kMenuNoCommandModifier);
   ChangeMenuItemAttributes (carbon_item->menu, carbon_item->index,
                             0, kMenuItemAttrUseVirtualKey);
   SetMenuItemCommandKey (carbon_item->menu, carbon_item->index,
                          false, 0);
}

static void
carbon_menu_item_accel_changed (GtkAccelGroup   *accel_group,
                                guint            keyval,
                                GdkModifierType  modifier,
                                GClosure        *accel_closure,
                                GtkWidget       *widget)
{
   CarbonMenuItem *carbon_item = carbon_menu_item_get (widget);
   GtkWidget      *label;

   get_menu_label_text (widget, &label);

   if (GTK_IS_ACCEL_LABEL (label) &&
         GTK_ACCEL_LABEL (label)->accel_closure == accel_closure)
      carbon_menu_item_update_accelerator (carbon_item, widget);
}

static void
carbon_menu_item_update_accel_closure (CarbonMenuItem *carbon_item,
                                       GtkWidget      *widget)
{
   GtkAccelGroup *group;
   GtkWidget     *label;

   get_menu_label_text (widget, &label);

   if (carbon_item->accel_closure)
   {
      group = gtk_accel_group_from_accel_closure (carbon_item->accel_closure);

      g_signal_handlers_disconnect_by_func (group,
                                            carbon_menu_item_accel_changed,
                                            widget);

      g_closure_unref (carbon_item->accel_closure);
      carbon_item->accel_closure = NULL;
   }

   if (GTK_IS_ACCEL_LABEL (label))
      carbon_item->accel_closure = GTK_ACCEL_LABEL (label)->accel_closure;

   if (carbon_item->accel_closure)
   {
      g_closure_ref (carbon_item->accel_closure);

      group = gtk_accel_group_from_accel_closure (carbon_item->accel_closure);

      g_signal_connect_object (group, "accel-changed",
                               G_CALLBACK (carbon_menu_item_accel_changed),
                               widget, 0);
   }

   carbon_menu_item_update_accelerator (carbon_item, widget);
}

static void
carbon_menu_item_notify (GObject        *object,
                         GParamSpec     *pspec,
                         CarbonMenuItem *carbon_item)
{
   if (!strcmp (pspec->name, "sensitive") ||
         !strcmp (pspec->name, "visible"))
   {
      carbon_menu_item_update_state (carbon_item, GTK_WIDGET (object));
   }
   else if (!strcmp (pspec->name, "active"))
   {
      carbon_menu_item_update_active (carbon_item, GTK_WIDGET (object));
   }
   else if (!strcmp (pspec->name, "submenu"))
   {
      carbon_menu_item_update_submenu (carbon_item, GTK_WIDGET (object));
   }
}

static void
carbon_menu_item_notify_label (GObject    *object,
                               GParamSpec *pspec,
                               gpointer    data)
{
   CarbonMenuItem *carbon_item = carbon_menu_item_get (GTK_WIDGET (object));

   if (!strcmp (pspec->name, "label"))
   {
      carbon_menu_item_update_label (carbon_item,
                                     GTK_WIDGET (object));
   }
   else if (!strcmp (pspec->name, "accel-closure"))
   {
      carbon_menu_item_update_accel_closure (carbon_item,
                                             GTK_WIDGET (object));
   }
}

static CarbonMenuItem *
carbon_menu_item_connect (GtkWidget     *menu_item,
                          GtkWidget     *label,
                          MenuRef        menu,
                          MenuItemIndex  index)
{
   CarbonMenuItem *carbon_item = carbon_menu_item_get (menu_item);

   if (!carbon_item)
   {
      carbon_item = carbon_menu_item_new ();

      g_object_set_qdata_full (G_OBJECT (menu_item), carbon_menu_item_quark,
                               carbon_item,
                               (GDestroyNotify) carbon_menu_item_free);

      g_signal_connect (menu_item, "notify",
                        G_CALLBACK (carbon_menu_item_notify),
                        carbon_item);

      if (label)
         g_signal_connect_swapped (label, "notify::label",
                                   G_CALLBACK (carbon_menu_item_notify_label),
                                   menu_item);
   }

   carbon_item->menu  = menu;
   carbon_item->index = index;

   return carbon_item;
}

typedef struct
{
   GtkWidget *widget;
} ActivateIdleData;

static void
activate_destroy_cb (gpointer user_data)
{
   ActivateIdleData *data = user_data;

   if (data->widget)
      g_object_remove_weak_pointer (G_OBJECT (data->widget), (gpointer) &data->widget);

   g_free (data);
}

static gboolean
activate_idle_cb (gpointer user_data)
{
   ActivateIdleData *data = user_data;

   if (data->widget)
      gtk_menu_item_activate (GTK_MENU_ITEM (data->widget));

   return FALSE;
}

/*
 * carbon event handler
 */

static OSStatus
menu_event_handler_func (EventHandlerCallRef  event_handler_call_ref,
                         EventRef             event_ref,
                         void                *data)
{
   UInt32 event_class = GetEventClass (event_ref);
   UInt32 event_kind = GetEventKind (event_ref);

   switch (event_class)
   {
   case kEventClassCommand:
      /* This is called when activating (is that the right GTK+ term?)
       * a menu item.
       */
      if (event_kind == kEventCommandProcess)
      {
         HICommand command;
         OSStatus  err;

         /*g_printerr ("Menu: kEventClassCommand/kEventCommandProcess\n");*/

         err = GetEventParameter (event_ref, kEventParamDirectObject,
                                  typeHICommand, 0,
                                  sizeof (command), 0, &command);

         if (err == noErr)
         {
            GtkWidget *widget = NULL;

            /* Get any GtkWidget associated with the item. */
            err = GetMenuItemProperty (command.menu.menuRef,
                                       command.menu.menuItemIndex,
                                       IGE_QUARTZ_MENU_CREATOR,
                                       IGE_QUARTZ_ITEM_WIDGET,
                                       sizeof (widget), 0, &widget);
            if (err == noErr && GTK_IS_WIDGET (widget))
            {
               ActivateIdleData *data;

               /* Activate from an idle handler so that the event is
                * emitted from the main loop instead of in the middle of
                * handling quartz events.
                */
               data = g_new0 (ActivateIdleData, 1);
               data->widget = widget;

               g_object_add_weak_pointer (G_OBJECT (widget), (gpointer) &data->widget);

               g_idle_add_full (G_PRIORITY_HIGH,
                                activate_idle_cb,
                                data,
                                activate_destroy_cb);
               return noErr;
            }
         }
      }
      break;

   case kEventClassMenu:
      if (event_kind == kEventMenuEndTracking)
         g_idle_add (menu_flash_off_cb, NULL);
      break;

   default:
      break;
   }

   return CallNextEventHandler (event_handler_call_ref, event_ref);
}

static gboolean
nsevent_handle_menu_key (NSEvent *nsevent)
{
   EventRef      event_ref;
   MenuRef       menu_ref;
   MenuItemIndex index;

   if ([nsevent type] != NSKeyDown)
      return FALSE;

   event_ref = [nsevent gdk_quartz_event_ref];
   if (IsMenuKeyEvent (NULL, event_ref,
                       kMenuEventQueryOnly,
                       &menu_ref, &index))
   {
      MenuCommand menu_command;
      HICommand   hi_command;

      if (GetMenuItemCommandID (menu_ref, index, &menu_command) != noErr)
         return FALSE;

      hi_command.commandID = menu_command;
      hi_command.menu.menuRef = menu_ref;
      hi_command.menu.menuItemIndex = index;

      CreateEvent (NULL, kEventClassCommand, kEventCommandProcess,
                   0, kEventAttributeUserEvent, &event_ref);
      SetEventParameter (event_ref, kEventParamDirectObject,
                         typeHICommand,
                         sizeof (HICommand), &hi_command);

      FlashMenuBar (GetMenuID (menu_ref));
      g_timeout_add (30, menu_flash_off_cb, NULL);

      SendEventToEventTarget (event_ref, GetMenuEventTarget (menu_ref));

      ReleaseEvent (event_ref);

      return TRUE;
   }

   return FALSE;
}

gboolean
ige_mac_menu_handle_menu_event (GdkEventKey *event)
{
   NSEvent *nsevent;

   /* FIXME: If the event here is unallocated, we crash. */
   nsevent = gdk_quartz_event_get_nsevent ((GdkEvent *) event);
   if (nsevent)
      return nsevent_handle_menu_key (nsevent);

   return FALSE;
}

static GdkFilterReturn
global_event_filter_func (gpointer  windowing_event,
                          GdkEvent *event,
                          gpointer  user_data)
{
   NSEvent *nsevent = windowing_event;

   /* Handle menu events with no window, since they won't go through the
    * regular event processing.
    */
   if ([nsevent window] == nil)
   {
      if (nsevent_handle_menu_key (nsevent))
         return GDK_FILTER_REMOVE;
   }
   else if (global_key_handler_enabled && [nsevent type] == NSKeyDown)
   {
      GList *toplevels, *l;
      GtkWindow *focus = NULL;

      toplevels = gtk_window_list_toplevels ();
      for (l = toplevels; l; l = l->next)
      {
         if (gtk_window_has_toplevel_focus (l->data))
         {
            focus = l->data;
            break;
         }
      }
      g_list_free (toplevels);

      /* FIXME: We could do something to skip menu events if there is a
       * modal dialog...
       */
      if (!focus || !g_object_get_data (G_OBJECT (focus), IGE_MAC_KEY_HANDLER))
      {
         if (nsevent_handle_menu_key (nsevent))
            return GDK_FILTER_REMOVE;
      }
   }

   return GDK_FILTER_CONTINUE;
}

static gboolean
key_press_event (GtkWidget   *widget,
                 GdkEventKey *event,
                 gpointer     user_data)
{
   GtkWindow *window = GTK_WINDOW (widget);
   GtkWidget *focus = gtk_window_get_focus (window);
   gboolean handled = FALSE;

   /* Text widgets get all key events first. */
   if (GTK_IS_EDITABLE (focus) || GTK_IS_TEXT_VIEW (focus))
      handled = gtk_window_propagate_key_event (window, event);

   if (!handled)
      handled = ige_mac_menu_handle_menu_event (event);

   /* Invoke control/alt accelerators. */
   if (!handled && event->state & (GDK_CONTROL_MASK | GDK_MOD1_MASK))
      handled = gtk_window_activate_key (window, event);

   /* Invoke focus widget handlers. */
   if (!handled)
      handled = gtk_window_propagate_key_event (window, event);

   /* Invoke non-(control/alt) accelerators. */
   if (!handled && !(event->state & (GDK_CONTROL_MASK | GDK_MOD1_MASK)))
      handled = gtk_window_activate_key (window, event);

   return handled;
}

static void
setup_menu_event_handler (void)
{
   static gboolean is_setup = FALSE;

   EventHandlerUPP menu_event_handler_upp;
   EventHandlerRef menu_event_handler_ref;
   const EventTypeSpec menu_events[] =
   {
      { kEventClassCommand, kEventCommandProcess },
      { kEventClassMenu, kEventMenuEndTracking }
   };

   if (is_setup)
      return;

   gdk_window_add_filter (NULL, global_event_filter_func, NULL);

   menu_event_handler_upp = NewEventHandlerUPP (menu_event_handler_func);
   InstallEventHandler (GetApplicationEventTarget (), menu_event_handler_upp,
                        GetEventTypeCount (menu_events), menu_events, 0,
                        &menu_event_handler_ref);

#if 0
   /* Note: If we want to supporting shutting down, remove the handler
    * with:
    */
   RemoveEventHandler(menu_event_handler_ref);
   DisposeEventHandlerUPP(menu_event_handler_upp);
#endif

   is_setup = TRUE;
}

static void
sync_menu_shell (GtkMenuShell *menu_shell,
                 MenuRef       carbon_menu,
                 gboolean      toplevel,
                 gboolean      debug)
{
   GList         *children;
   GList         *l;
   MenuItemIndex  carbon_index = 1;

   if (debug)
      g_printerr ("%s: syncing shell %p\n", G_STRFUNC, menu_shell);

   carbon_menu_connect (GTK_WIDGET (menu_shell), carbon_menu, toplevel);

   children = gtk_container_get_children (GTK_CONTAINER (menu_shell));

   for (l = children; l; l = l->next)
   {
      GtkWidget      *menu_item = l->data;
      CarbonMenuItem *carbon_item;

      if (GTK_IS_TEAROFF_MENU_ITEM (menu_item))
         continue;

      if (toplevel && (g_object_get_data (G_OBJECT (menu_item),
                                          "gtk-empty-menu-item") ||
                       GTK_IS_SEPARATOR_MENU_ITEM (menu_item)))
         continue;

      carbon_item = carbon_menu_item_get (menu_item);

      if (debug)
         g_printerr ("%s: carbon_item %d for menu_item %d (%s, %s)\n",
                     G_STRFUNC, carbon_item ? carbon_item->index : -1,
                     carbon_index, get_menu_label_text (menu_item, NULL),
                     g_type_name (G_TYPE_FROM_INSTANCE (menu_item)));

      if (carbon_item && carbon_item->index != carbon_index)
      {
         if (debug)
            g_printerr ("%s:   -> not matching, deleting\n", G_STRFUNC);

         DeleteMenuItem (carbon_item->menu, carbon_index);
         carbon_item = NULL;
      }

      if (!carbon_item)
      {
         GtkWidget          *label      = NULL;
         const gchar        *label_text;
         CFStringRef         cfstr      = NULL;
         MenuItemAttributes  attributes = 0;

         if (debug)
            g_printerr ("%s:   -> creating new\n", G_STRFUNC);

         label_text = get_menu_label_text (menu_item, &label);
         if (label_text)
            cfstr = CFStringCreateWithCString (NULL, label_text,
                                               kCFStringEncodingUTF8);

         if (GTK_IS_SEPARATOR_MENU_ITEM (menu_item))
            attributes |= kMenuItemAttrSeparator;

         if (!GTK_WIDGET_IS_SENSITIVE (menu_item))
            attributes |= kMenuItemAttrDisabled;

         if (!GTK_WIDGET_VISIBLE (menu_item))
            attributes |= kMenuItemAttrHidden;

         InsertMenuItemTextWithCFString (carbon_menu, cfstr,
                                         carbon_index - 1,
                                         attributes, 0);
         SetMenuItemProperty (carbon_menu, carbon_index,
                              IGE_QUARTZ_MENU_CREATOR,
                              IGE_QUARTZ_ITEM_WIDGET,
                              sizeof (menu_item), &menu_item);

         if (cfstr)
            CFRelease (cfstr);

         carbon_item = carbon_menu_item_connect (menu_item, label,
                                                 carbon_menu,
                                                 carbon_index);

         if (GTK_IS_CHECK_MENU_ITEM (menu_item))
            carbon_menu_item_update_active (carbon_item, menu_item);

         carbon_menu_item_update_accel_closure (carbon_item, menu_item);

         if (gtk_menu_item_get_submenu (GTK_MENU_ITEM (menu_item)))
            carbon_menu_item_update_submenu (carbon_item, menu_item);
      }

      carbon_index++;
   }

   g_list_free (children);
}

static gulong emission_hook_id    = 0;
static gint   emission_hook_count = 0;

static gboolean
parent_set_emission_hook (GSignalInvocationHint *ihint,
                          guint                  n_param_values,
                          const GValue          *param_values,
                          gpointer               data)
{
   GtkWidget *instance = g_value_get_object (param_values);

   if (GTK_IS_MENU_ITEM (instance))
   {
      GtkWidget *previous_parent = g_value_get_object (param_values + 1);
      GtkWidget *menu_shell      = NULL;

      if (GTK_IS_MENU_SHELL (previous_parent))
      {
         menu_shell = previous_parent;
      }
      else if (GTK_IS_MENU_SHELL (instance->parent))
      {
         menu_shell = instance->parent;
      }

      if (menu_shell)
      {
         CarbonMenu *carbon_menu = carbon_menu_get (menu_shell);

         if (carbon_menu)
         {
#if 0
            g_printerr ("%s: item %s %p (%s, %s)\n", G_STRFUNC,
                        previous_parent ? "removed from" : "added to",
                        menu_shell,
                        get_menu_label_text (instance, NULL),
                        g_type_name (G_TYPE_FROM_INSTANCE (instance)));
#endif

            sync_menu_shell (GTK_MENU_SHELL (menu_shell),
                             carbon_menu->menu,
                             carbon_menu->toplevel,
                             FALSE);
         }
      }
   }

   return TRUE;
}

static void
parent_set_emission_hook_remove (GtkWidget *widget,
                                 gpointer   data)
{
   emission_hook_count--;

   if (emission_hook_count > 0)
      return;

   g_signal_remove_emission_hook (g_signal_lookup ("parent-set",
                                  GTK_TYPE_WIDGET),
                                  emission_hook_id);
   emission_hook_id = 0;
}


/*
 * public functions
 */

void
ige_mac_menu_set_menu_bar (GtkMenuShell *menu_shell)
{
   CarbonMenu *current_menu;
   MenuRef     carbon_menubar;

   g_return_if_fail (GTK_IS_MENU_SHELL (menu_shell));

   if (carbon_menu_quark == 0)
      carbon_menu_quark = g_quark_from_static_string ("CarbonMenu");

   if (carbon_menu_item_quark == 0)
      carbon_menu_item_quark = g_quark_from_static_string ("CarbonMenuItem");

   current_menu = carbon_menu_get (GTK_WIDGET (menu_shell));
   if (current_menu)
   {
      SetRootMenu (current_menu->menu);
      return;
   }

   CreateNewMenu (0 /*id*/, 0 /*options*/, &carbon_menubar);
   SetRootMenu (carbon_menubar);

   setup_menu_event_handler ();

   if (emission_hook_id == 0)
   {
      emission_hook_id =
         g_signal_add_emission_hook (g_signal_lookup ("parent-set",
                                     GTK_TYPE_WIDGET),
                                     0,
                                     parent_set_emission_hook,
                                     NULL, NULL);
   }

   emission_hook_count++;

   g_signal_connect (menu_shell, "destroy",
                     G_CALLBACK (parent_set_emission_hook_remove),
                     NULL);

   sync_menu_shell (menu_shell, carbon_menubar, TRUE, FALSE);
}

void
ige_mac_menu_set_quit_menu_item (GtkMenuItem *menu_item)
{
   MenuRef       appmenu;
   MenuItemIndex index;

   g_return_if_fail (GTK_IS_MENU_ITEM (menu_item));

   setup_menu_event_handler ();

   if (GetIndMenuItemWithCommandID (NULL, kHICommandQuit, 1,
                                    &appmenu, &index) == noErr)
   {
      SetMenuItemCommandID (appmenu, index, 0);
      SetMenuItemProperty (appmenu, index,
                           IGE_QUARTZ_MENU_CREATOR,
                           IGE_QUARTZ_ITEM_WIDGET,
                           sizeof (menu_item), &menu_item);

      gtk_widget_hide (GTK_WIDGET (menu_item));
   }
}

void
ige_mac_menu_connect_window_key_handler (GtkWindow *window)
{
   if (g_object_get_data (G_OBJECT (window), IGE_MAC_KEY_HANDLER))
   {
      g_warning ("Window %p is already connected", window);
      return;
   }

   g_signal_connect (window, "key-press-event", G_CALLBACK (key_press_event), NULL);
   g_object_set_data (G_OBJECT (window), IGE_MAC_KEY_HANDLER, GINT_TO_POINTER (1));
}

/* Most applications will want to have this enabled (which is the
 * defalt). For apps that need to deal with the events themselves, the
 * global handling can be disabled.
 */
void
ige_mac_menu_set_global_key_handler_enabled (gboolean enabled)
{
   global_key_handler_enabled = enabled;
}

/* For internal use only. Returns TRUE if there is a GtkMenuItem assigned to
 * the Quit menu item.
 */
gboolean
_ige_mac_menu_is_quit_menu_item_handled (void)
{
   MenuRef       appmenu;
   MenuItemIndex index;

   if (GetIndMenuItemWithCommandID (NULL, kHICommandQuit, 1,
                                    &appmenu, &index) == noErr)
   {
      return FALSE;
   }

   return TRUE;
}


struct _IgeMacMenuGroup
{
   GList *items;
};

static GList *app_menu_groups = NULL;

IgeMacMenuGroup *
ige_mac_menu_add_app_menu_group (void)
{
   IgeMacMenuGroup *group = g_slice_new0 (IgeMacMenuGroup);

   app_menu_groups = g_list_append (app_menu_groups, group);

   return group;
}

void
ige_mac_menu_add_app_menu_item (IgeMacMenuGroup *group,
                                GtkMenuItem     *menu_item,
                                const gchar     *label)
{
   MenuRef  appmenu;
   GList   *list;
   gint     index = 0;

   g_return_if_fail (group != NULL);
   g_return_if_fail (GTK_IS_MENU_ITEM (menu_item));

   setup_menu_event_handler ();

   if (GetIndMenuItemWithCommandID (NULL, kHICommandHide, 1,
                                    &appmenu, NULL) != noErr)
   {
      g_warning ("%s: retrieving app menu failed",
                 G_STRFUNC);
      return;
   }

   for (list = app_menu_groups; list; list = g_list_next (list))
   {
      IgeMacMenuGroup *list_group = list->data;

      index += g_list_length (list_group->items);

      /*  adjust index for the separator between groups, but not
       *  before the first group
       */
      if (list_group->items && list->prev)
         index++;

      if (group == list_group)
      {
         CFStringRef cfstr;

         /*  add a separator before adding the first item, but not
          *  for the first group
          */
         if (!group->items && list->prev)
         {
            InsertMenuItemTextWithCFString (appmenu, NULL, index,
                                            kMenuItemAttrSeparator, 0);
            index++;
         }

         if (!label)
            label = get_menu_label_text (GTK_WIDGET (menu_item), NULL);

         cfstr = CFStringCreateWithCString (NULL, label,
                                            kCFStringEncodingUTF8);

         InsertMenuItemTextWithCFString (appmenu, cfstr, index, 0, 0);
         SetMenuItemProperty (appmenu, index + 1,
                              IGE_QUARTZ_MENU_CREATOR,
                              IGE_QUARTZ_ITEM_WIDGET,
                              sizeof (menu_item), &menu_item);

         CFRelease (cfstr);

         gtk_widget_hide (GTK_WIDGET (menu_item));

         group->items = g_list_append (group->items, menu_item);

         return;
      }
   }

   if (!list)
      g_warning ("%s: app menu group %p does not exist",
                 G_STRFUNC, group);
}
