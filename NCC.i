# 1 "gui.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/nognu" 1
# 1 "<command-line>" 2
# 1 "gui.c"
# 23 "gui.c"
# 1 "/usr/include/stdio.h" 1 3 4
# 28 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 330 "/usr/include/features.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 348 "/usr/include/sys/cdefs.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 349 "/usr/include/sys/cdefs.h" 2 3 4
# 331 "/usr/include/features.h" 2 3 4
# 354 "/usr/include/features.h" 3 4
# 1 "/usr/include/gnu/stubs.h" 1 3 4



# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 5 "/usr/include/gnu/stubs.h" 2 3 4




# 1 "/usr/include/gnu/stubs-64.h" 1 3 4
# 10 "/usr/include/gnu/stubs.h" 2 3 4
# 355 "/usr/include/features.h" 2 3 4
# 29 "/usr/include/stdio.h" 2 3 4





# 1 "/usr/lib/gcc/x86_64-linux-gnu/4.3.2/include/stddef.h" 1 3 4
# 214 "/usr/lib/gcc/x86_64-linux-gnu/4.3.2/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 35 "/usr/include/stdio.h" 2 3 4

# 1 "/usr/include/bits/types.h" 1 3 4
# 28 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 29 "/usr/include/bits/types.h" 2 3 4


typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;







typedef long int __quad_t;
typedef unsigned long int __u_quad_t;
# 131 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/typesizes.h" 1 3 4
# 132 "/usr/include/bits/types.h" 2 3 4


typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;

typedef int __daddr_t;
typedef long int __swblk_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void * __timer_t;


typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;

typedef long int __ssize_t;



typedef __off64_t __loff_t;
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;
# 37 "/usr/include/stdio.h" 2 3 4
# 45 "/usr/include/stdio.h" 3 4
struct _IO_FILE;



typedef struct _IO_FILE FILE;





# 65 "/usr/include/stdio.h" 3 4
typedef struct _IO_FILE __FILE;
# 75 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/libio.h" 1 3 4
# 32 "/usr/include/libio.h" 3 4
# 1 "/usr/include/_G_config.h" 1 3 4
# 15 "/usr/include/_G_config.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/4.3.2/include/stddef.h" 1 3 4
# 16 "/usr/include/_G_config.h" 2 3 4




# 1 "/usr/include/wchar.h" 1 3 4
# 78 "/usr/include/wchar.h" 3 4
typedef struct
{
  int __count;
  union
  {

    unsigned int __wch;



    char __wchb[4];
  } __value;
} __mbstate_t;
# 21 "/usr/include/_G_config.h" 2 3 4

typedef struct
{
  __off_t __pos;
  __mbstate_t __state;
} _G_fpos_t;
typedef struct
{
  __off64_t __pos;
  __mbstate_t __state;
} _G_fpos64_t;
# 53 "/usr/include/_G_config.h" 3 4
typedef int _G_int16_t ;
typedef int _G_int32_t ;
typedef unsigned int _G_uint16_t ;
typedef unsigned int _G_uint32_t ;
# 33 "/usr/include/libio.h" 2 3 4
# 53 "/usr/include/libio.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/4.3.2/include/stdarg.h" 1 3 4
# 43 "/usr/lib/gcc/x86_64-linux-gnu/4.3.2/include/stdarg.h" 3 4
typedef char* __gnuc_va_list;
# 54 "/usr/include/libio.h" 2 3 4
# 170 "/usr/include/libio.h" 3 4
struct _IO_jump_t; struct _IO_FILE;
# 180 "/usr/include/libio.h" 3 4
typedef void _IO_lock_t;





struct _IO_marker {
  struct _IO_marker *_next;
  struct _IO_FILE *_sbuf;



  int _pos;
# 203 "/usr/include/libio.h" 3 4
};


enum __codecvt_result
{
  __codecvt_ok,
  __codecvt_partial,
  __codecvt_error,
  __codecvt_noconv
};
# 271 "/usr/include/libio.h" 3 4
struct _IO_FILE {
  int _flags;




  char* _IO_read_ptr;
  char* _IO_read_end;
  char* _IO_read_base;
  char* _IO_write_base;
  char* _IO_write_ptr;
  char* _IO_write_end;
  char* _IO_buf_base;
  char* _IO_buf_end;

  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;



  int _flags2;

  __off_t _old_offset;



  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];



  _IO_lock_t *_lock;
# 319 "/usr/include/libio.h" 3 4
  __off64_t _offset;
# 328 "/usr/include/libio.h" 3 4
  void *__pad1;
  void *__pad2;
  void *__pad3;
  void *__pad4;
  size_t __pad5;

  int _mode;

  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];

};


typedef struct _IO_FILE _IO_FILE;


struct _IO_FILE_plus;

extern struct _IO_FILE_plus _IO_2_1_stdin_;
extern struct _IO_FILE_plus _IO_2_1_stdout_;
extern struct _IO_FILE_plus _IO_2_1_stderr_;
# 364 "/usr/include/libio.h" 3 4
typedef __ssize_t __io_read_fn (void *__cookie, char *__buf, size_t __nbytes);







typedef __ssize_t __io_write_fn (void *__cookie, const char *__buf,
     size_t __n);







typedef int __io_seek_fn (void *__cookie, __off64_t *__pos, int __w);


typedef int __io_close_fn (void *__cookie);
# 416 "/usr/include/libio.h" 3 4
extern int __underflow (_IO_FILE *);
extern int __uflow (_IO_FILE *);
extern int __overflow (_IO_FILE *, int);
# 458 "/usr/include/libio.h" 3 4
extern int _IO_getc (_IO_FILE *__fp);
extern int _IO_putc (int __c, _IO_FILE *__fp);
extern int _IO_feof (_IO_FILE *__fp) ;
extern int _IO_ferror (_IO_FILE *__fp) ;

extern int _IO_peekc_locked (_IO_FILE *__fp);





extern void _IO_flockfile (_IO_FILE *) ;
extern void _IO_funlockfile (_IO_FILE *) ;
extern int _IO_ftrylockfile (_IO_FILE *) ;
# 488 "/usr/include/libio.h" 3 4
extern int _IO_vfscanf (_IO_FILE * , const char * ,
   __gnuc_va_list, int *);
extern int _IO_vfprintf (_IO_FILE *, const char *,
    __gnuc_va_list);
extern __ssize_t _IO_padn (_IO_FILE *, int, __ssize_t);
extern size_t _IO_sgetn (_IO_FILE *, void *, size_t);

extern __off64_t _IO_seekoff (_IO_FILE *, __off64_t, int, int);
extern __off64_t _IO_seekpos (_IO_FILE *, __off64_t, int);

extern void _IO_free_backup_area (_IO_FILE *) ;
# 76 "/usr/include/stdio.h" 2 3 4
# 89 "/usr/include/stdio.h" 3 4


typedef _G_fpos_t fpos_t;




# 141 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/bits/stdio_lim.h" 1 3 4
# 142 "/usr/include/stdio.h" 2 3 4



extern struct _IO_FILE *stdin;
extern struct _IO_FILE *stdout;
extern struct _IO_FILE *stderr;







extern int remove (const char *__filename) ;

extern int rename (const char *__old, const char *__new) ;














extern FILE *tmpfile (void) ;
# 186 "/usr/include/stdio.h" 3 4
extern char *tmpnam (char *__s) ;





extern char *tmpnam_r (char *__s) ;
# 204 "/usr/include/stdio.h" 3 4
extern char *tempnam (const char *__dir, const char *__pfx)
     ;








extern int fclose (FILE *__stream);




extern int fflush (FILE *__stream);

# 229 "/usr/include/stdio.h" 3 4
extern int fflush_unlocked (FILE *__stream);
# 243 "/usr/include/stdio.h" 3 4






extern FILE *fopen (const char * __filename,
      const char * __modes) ;




extern FILE *freopen (const char * __filename,
        const char * __modes,
        FILE * __stream) ;
# 272 "/usr/include/stdio.h" 3 4

# 283 "/usr/include/stdio.h" 3 4
extern FILE *fdopen (int __fd, const char *__modes) ;
# 304 "/usr/include/stdio.h" 3 4



extern void setbuf (FILE * __stream, char * __buf) ;



extern int setvbuf (FILE * __stream, char * __buf,
      int __modes, size_t __n) ;





extern void setbuffer (FILE * __stream, char * __buf,
         size_t __size) ;


extern void setlinebuf (FILE *__stream) ;








extern int fprintf (FILE * __stream,
      const char * __format, ...);




extern int printf (const char * __format, ...);

extern int sprintf (char * __s,
      const char * __format, ...) ;





extern int vfprintf (FILE * __s, const char * __format,
       __gnuc_va_list __arg);




extern int vprintf (const char * __format, __gnuc_va_list __arg);

extern int vsprintf (char * __s, const char * __format,
       __gnuc_va_list __arg) ;





extern int snprintf (char * __s, size_t __maxlen,
       const char * __format, ...)
     ;

extern int vsnprintf (char * __s, size_t __maxlen,
        const char * __format, __gnuc_va_list __arg)
     ;

# 398 "/usr/include/stdio.h" 3 4





extern int fscanf (FILE * __stream,
     const char * __format, ...) ;




extern int scanf (const char * __format, ...) ;

extern int sscanf (const char * __s,
     const char * __format, ...) ;
# 441 "/usr/include/stdio.h" 3 4

# 504 "/usr/include/stdio.h" 3 4





extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);





extern int getchar (void);

# 528 "/usr/include/stdio.h" 3 4
extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
# 539 "/usr/include/stdio.h" 3 4
extern int fgetc_unlocked (FILE *__stream);











extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);





extern int putchar (int __c);

# 572 "/usr/include/stdio.h" 3 4
extern int fputc_unlocked (int __c, FILE *__stream);







extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);






extern int getw (FILE *__stream);


extern int putw (int __w, FILE *__stream);








extern char *fgets (char * __s, int __n, FILE * __stream)
     ;






extern char *gets (char *__s) ;

# 653 "/usr/include/stdio.h" 3 4





extern int fputs (const char * __s, FILE * __stream);





extern int puts (const char *__s);






extern int ungetc (int __c, FILE *__stream);






extern size_t fread (void * __ptr, size_t __size,
       size_t __n, FILE * __stream) ;




extern size_t fwrite (const void * __ptr, size_t __size,
        size_t __n, FILE * __s) ;

# 706 "/usr/include/stdio.h" 3 4
extern size_t fread_unlocked (void * __ptr, size_t __size,
         size_t __n, FILE * __stream) ;
extern size_t fwrite_unlocked (const void * __ptr, size_t __size,
          size_t __n, FILE * __stream) ;








extern int fseek (FILE *__stream, long int __off, int __whence);




extern long int ftell (FILE *__stream) ;




extern void rewind (FILE *__stream);

# 742 "/usr/include/stdio.h" 3 4
extern int fseeko (FILE *__stream, __off_t __off, int __whence);




extern __off_t ftello (FILE *__stream) ;
# 761 "/usr/include/stdio.h" 3 4






extern int fgetpos (FILE * __stream, fpos_t * __pos);




extern int fsetpos (FILE *__stream, const fpos_t *__pos);
# 784 "/usr/include/stdio.h" 3 4

# 793 "/usr/include/stdio.h" 3 4


extern void clearerr (FILE *__stream) ;

extern int feof (FILE *__stream) ;

extern int ferror (FILE *__stream) ;




extern void clearerr_unlocked (FILE *__stream) ;
extern int feof_unlocked (FILE *__stream) ;
extern int ferror_unlocked (FILE *__stream) ;








extern void perror (const char *__s);






# 1 "/usr/include/bits/sys_errlist.h" 1 3 4
# 27 "/usr/include/bits/sys_errlist.h" 3 4
extern int sys_nerr;
extern const char *const sys_errlist[];
# 823 "/usr/include/stdio.h" 2 3 4




extern int fileno (FILE *__stream) ;




extern int fileno_unlocked (FILE *__stream) ;
# 842 "/usr/include/stdio.h" 3 4
extern FILE *popen (const char *__command, const char *__modes) ;





extern int pclose (FILE *__stream);





extern char *ctermid (char *__s) ;
# 882 "/usr/include/stdio.h" 3 4
extern void flockfile (FILE *__stream) ;



extern int ftrylockfile (FILE *__stream) ;


extern void funlockfile (FILE *__stream) ;
# 912 "/usr/include/stdio.h" 3 4

# 24 "gui.c" 2
# 33 "gui.c"
# 1 "/usr/local/include/gtkdatabox.h" 1 3
# 23 "/usr/local/include/gtkdatabox.h" 3
# 1 "/usr/local/include/gtkdatabox_typedefs.h" 1 3
# 25 "/usr/local/include/gtkdatabox_typedefs.h" 3
G_BEGIN_DECLS
# 38 "/usr/local/include/gtkdatabox_typedefs.h" 3
   typedef struct _GtkDatabox GtkDatabox;
# 51 "/usr/local/include/gtkdatabox_typedefs.h" 3
typedef struct _GtkDataboxGraph GtkDataboxGraph;
G_END_DECLS
# 24 "/usr/local/include/gtkdatabox.h" 2 3
# 1 "/usr/local/include/gtkdatabox_graph.h" 1 3
# 40 "/usr/local/include/gtkdatabox_graph.h" 3
# 1 "/usr/local/include/gtkdatabox.h" 1 3
# 41 "/usr/local/include/gtkdatabox_graph.h" 2 3

G_BEGIN_DECLS
# 58 "/usr/local/include/gtkdatabox_graph.h" 3
   typedef struct _GtkDataboxGraphClass GtkDataboxGraphClass;
# 67 "/usr/local/include/gtkdatabox_graph.h" 3
   typedef struct _GtkDataboxGraphPrivate GtkDataboxGraphPrivate;
# 77 "/usr/local/include/gtkdatabox_graph.h" 3
   struct _GtkDataboxGraph
   {

      GObject parent;

      GtkDataboxGraphPrivate *priv;
   };

   struct _GtkDataboxGraphClass
   {
      GObjectClass parent_class;




      void (*draw) (GtkDataboxGraph * graph, GtkDatabox * box);

      gint (*calculate_extrema) (GtkDataboxGraph * graph,
                                 gfloat * min_x, gfloat * max_x,
     gfloat * min_y, gfloat * max_y);
      GdkGC* (*create_gc) (GtkDataboxGraph * graph, GtkDatabox * box);
   };

   GType gtk_databox_graph_get_type (void);

   GdkGC* gtk_databox_graph_get_gc (GtkDataboxGraph * graph);
   void gtk_databox_graph_set_gc (GtkDataboxGraph * graph, GdkGC *gc);

   void gtk_databox_graph_set_hide (GtkDataboxGraph * graph, gboolean hide);
   gboolean gtk_databox_graph_get_hide (GtkDataboxGraph * graph);

   void gtk_databox_graph_set_color (GtkDataboxGraph * graph,
         GdkColor * color);
   GdkColor *gtk_databox_graph_get_color (GtkDataboxGraph * graph);

   void gtk_databox_graph_set_size (GtkDataboxGraph * graph, gint size);
   gint gtk_databox_graph_get_size (GtkDataboxGraph * graph);

   gint gtk_databox_graph_calculate_extrema (GtkDataboxGraph * graph,
          gfloat * min_x, gfloat * max_x,
          gfloat * min_y, gfloat * max_y);

   void gtk_databox_graph_draw (GtkDataboxGraph * graph, GtkDatabox * box);


   GdkGC* gtk_databox_graph_create_gc (GtkDataboxGraph * graph, GtkDatabox * box);

G_END_DECLS
# 25 "/usr/local/include/gtkdatabox.h" 2 3
# 1 "/usr/local/include/gtkdatabox_ruler.h" 1 3
# 67 "/usr/local/include/gtkdatabox_ruler.h" 3
# 1 "/usr/local/include/gtkdatabox_scale.h" 1 3
# 32 "/usr/local/include/gtkdatabox_scale.h" 3
G_BEGIN_DECLS
# 43 "/usr/local/include/gtkdatabox_scale.h" 3
typedef enum
{
   GTK_DATABOX_SCALE_LINEAR = 0,
   GTK_DATABOX_SCALE_LOG,
   GTK_DATABOX_SCALE_LOG2
}
GtkDataboxScaleType;

GType gtk_databox_scale_type_get_type (void);

G_END_DECLS
# 68 "/usr/local/include/gtkdatabox_ruler.h" 2 3

G_BEGIN_DECLS
# 82 "/usr/local/include/gtkdatabox_ruler.h" 3
typedef struct _GtkDataboxRuler GtkDataboxRuler;
typedef struct _GtkDataboxRulerClass GtkDataboxRulerClass;
# 99 "/usr/local/include/gtkdatabox_ruler.h" 3
 typedef struct _GtkDataboxRulerPrivate GtkDataboxRulerPrivate;

struct _GtkDataboxRuler
{
   GtkWidget widget;

   GtkDataboxRulerPrivate *priv;
};

struct _GtkDataboxRulerClass
{
   GtkWidgetClass parent_class;
};


GType
gtk_databox_ruler_get_type (void)
   G_GNUC_CONST;
     GtkWidget *gtk_databox_ruler_new (GtkOrientation orientation);

     void gtk_databox_ruler_set_range (GtkDataboxRuler * ruler,
           gdouble lower,
           gdouble upper, gdouble position);
     void gtk_databox_ruler_set_max_length (GtkDataboxRuler * ruler,
         guint max_length);
     void gtk_databox_ruler_set_scale_type (GtkDataboxRuler * ruler,
         guint scale_type);

     void gtk_databox_ruler_get_range (GtkDataboxRuler * ruler,
           gdouble * lower,
           gdouble * upper, gdouble * position);
     guint gtk_databox_ruler_get_max_length (GtkDataboxRuler * ruler);
     GtkDataboxScaleType gtk_databox_ruler_get_scale_type (GtkDataboxRuler *
          ruler);

     void gtk_databox_ruler_set_orientation (GtkDataboxRuler * ruler,
          GtkOrientation orientation);

     GtkOrientation gtk_databox_ruler_get_orientation (GtkDataboxRuler *
             ruler);

G_END_DECLS
# 26 "/usr/local/include/gtkdatabox.h" 2 3
# 54 "/usr/local/include/gtkdatabox.h" 3
G_BEGIN_DECLS
# 71 "/usr/local/include/gtkdatabox.h" 3
   typedef struct _GtkDataboxClass GtkDataboxClass;
# 80 "/usr/local/include/gtkdatabox.h" 3
   typedef struct _GtkDataboxPrivate GtkDataboxPrivate;

   typedef struct
   {
      gfloat x1;
      gfloat x2;
      gfloat y1;
      gfloat y2;
   } GtkDataboxValueRectangle;
# 98 "/usr/local/include/gtkdatabox.h" 3
   struct _GtkDatabox
   {

      GtkWidget box;

      GtkDataboxPrivate *priv;
   };

   struct _GtkDataboxClass
   {
      GtkWidgetClass parent_class;

      void (*zoomed) (GtkDatabox * box);
      void (*selection_started) (GtkDatabox * box,
     GtkDataboxValueRectangle * selectionValues);
      void (*selection_changed) (GtkDatabox * box,
     GtkDataboxValueRectangle * selectionValues);
      void (*selection_finalized) (GtkDatabox * box,
       GtkDataboxValueRectangle *
       selectionValues);
      void (*selection_canceled) (GtkDatabox * box);
   };

   GType gtk_databox_get_type (void);

   GtkWidget *gtk_databox_new (void);

   gint gtk_databox_graph_add (GtkDatabox * box, GtkDataboxGraph * graph);
   gint gtk_databox_graph_remove (GtkDatabox * box, GtkDataboxGraph * graph);
   gint gtk_databox_graph_remove_all (GtkDatabox * box);

   gint gtk_databox_auto_rescale (GtkDatabox * box, gfloat border);
   gint gtk_databox_calculate_extrema (GtkDatabox * box,
           gfloat * min_x, gfloat * max_x,
           gfloat * min_y, gfloat * max_y);

   void gtk_databox_set_total_limits (GtkDatabox * box,
          gfloat left, gfloat right,
          gfloat top, gfloat bottom);
   void gtk_databox_set_visible_limits (GtkDatabox * box,
     gfloat left, gfloat right,
     gfloat top, gfloat bottom);
   void gtk_databox_get_total_limits (GtkDatabox * box,
          gfloat * left, gfloat * right,
          gfloat * top, gfloat * bottom);
   void gtk_databox_get_visible_limits (GtkDatabox * box,
     gfloat * left, gfloat * right,
     gfloat * top, gfloat * bottom);

   void gtk_databox_set_adjustment_x (GtkDatabox * box, GtkAdjustment * adj);
   void gtk_databox_set_adjustment_y (GtkDatabox * box, GtkAdjustment * adj);
   GtkAdjustment *gtk_databox_get_adjustment_x (GtkDatabox * box);
   GtkAdjustment *gtk_databox_get_adjustment_y (GtkDatabox * box);

   void gtk_databox_set_ruler_x (GtkDatabox * box, GtkDataboxRuler * ruler);
   void gtk_databox_set_ruler_y (GtkDatabox * box, GtkDataboxRuler * ruler);
   GtkDataboxRuler *gtk_databox_get_ruler_x (GtkDatabox * box);
   GtkDataboxRuler *gtk_databox_get_ruler_y (GtkDatabox * box);

   void gtk_databox_set_scale_type_x (GtkDatabox * box,
          GtkDataboxScaleType scale_type);
   void gtk_databox_set_scale_type_y (GtkDatabox * box,
          GtkDataboxScaleType scale_type);
   GtkDataboxScaleType gtk_databox_get_scale_type_x (GtkDatabox * box);
   GtkDataboxScaleType gtk_databox_get_scale_type_y (GtkDatabox * box);

   void gtk_databox_set_enable_selection (GtkDatabox * box, gboolean enable);
   void gtk_databox_set_enable_zoom (GtkDatabox * box, gboolean enable);

   gboolean gtk_databox_get_enable_selection (GtkDatabox * box);
   gboolean gtk_databox_get_enable_zoom (GtkDatabox * box);

   void gtk_databox_zoom_to_selection (GtkDatabox * box);
   void gtk_databox_zoom_out (GtkDatabox * box);
   void gtk_databox_zoom_home (GtkDatabox * box);

   gint16 gtk_databox_value_to_pixel_x (GtkDatabox * box, gfloat value);
   gint16 gtk_databox_value_to_pixel_y (GtkDatabox * box, gfloat value);
   gfloat gtk_databox_pixel_to_value_x (GtkDatabox * box, gint16 pixel);
   gfloat gtk_databox_pixel_to_value_y (GtkDatabox * box, gint16 pixel);
   void gtk_databox_values_to_pixels (GtkDatabox * box,
          guint len,
          const gfloat * values_x,
          const gfloat * values_y,
          GdkPoint * pixels);

   void gtk_databox_create_box_with_scrollbars_and_rulers (GtkWidget **
          p_box,
          GtkWidget **
          p_table,
          gboolean scrollbar_x,
          gboolean scrollbar_y,
          gboolean ruler_x,
          gboolean ruler_y);


   GdkPixmap* gtk_databox_get_backing_pixmap(GtkDatabox * box);

G_END_DECLS
# 34 "gui.c" 2
# 1 "/usr/local/include/gtkdatabox_points.h" 1 3
# 33 "/usr/local/include/gtkdatabox_points.h" 3
# 1 "/usr/local/include/gtkdatabox_xyc_graph.h" 1 3
# 37 "/usr/local/include/gtkdatabox_xyc_graph.h" 3
G_BEGIN_DECLS
# 61 "/usr/local/include/gtkdatabox_xyc_graph.h" 3
   typedef struct _GtkDataboxXYCGraph GtkDataboxXYCGraph;

   typedef struct _GtkDataboxXYCGraphClass GtkDataboxXYCGraphClass;
# 72 "/usr/local/include/gtkdatabox_xyc_graph.h" 3
   typedef struct _GtkDataboxXYCGraphPrivate GtkDataboxXYCGraphPrivate;

   struct _GtkDataboxXYCGraph
   {

      GtkDataboxGraph parent;

      GtkDataboxXYCGraphPrivate *priv;
   };

   struct _GtkDataboxXYCGraphClass
   {
      GtkDataboxGraphClass parent_class;
   };

   GType gtk_databox_xyc_graph_get_type (void);

   guint gtk_databox_xyc_graph_get_length (GtkDataboxXYCGraph * xyc_graph);
   gfloat *gtk_databox_xyc_graph_get_X (GtkDataboxXYCGraph * xyc_graph);
   gfloat *gtk_databox_xyc_graph_get_Y (GtkDataboxXYCGraph * xyc_graph);

G_END_DECLS
# 34 "/usr/local/include/gtkdatabox_points.h" 2 3

G_BEGIN_DECLS
# 59 "/usr/local/include/gtkdatabox_points.h" 3
   typedef struct _GtkDataboxPoints GtkDataboxPoints;

   typedef struct _GtkDataboxPointsClass GtkDataboxPointsClass;
# 70 "/usr/local/include/gtkdatabox_points.h" 3
   typedef struct _GtkDataboxPointsPrivate GtkDataboxPointsPrivate;

   struct _GtkDataboxPoints
   {

      GtkDataboxXYCGraph parent;

      GtkDataboxPointsPrivate *priv;
   };

   struct _GtkDataboxPointsClass
   {
      GtkDataboxXYCGraphClass parent_class;
   };

   GType gtk_databox_points_get_type (void);

   GtkDataboxGraph *gtk_databox_points_new (guint len, gfloat * X, gfloat * Y,
         GdkColor * color, gint size);

G_END_DECLS
# 35 "gui.c" 2
# 1 "/usr/local/include/gtkdatabox_lines.h" 1 3
# 35 "/usr/local/include/gtkdatabox_lines.h" 3
G_BEGIN_DECLS
# 57 "/usr/local/include/gtkdatabox_lines.h" 3
   typedef struct _GtkDataboxLines GtkDataboxLines;

   typedef struct _GtkDataboxLinesClass GtkDataboxLinesClass;
# 69 "/usr/local/include/gtkdatabox_lines.h" 3
   typedef struct _GtkDataboxLinesPrivate GtkDataboxLinesPrivate;

   struct _GtkDataboxLines
   {

      GtkDataboxXYCGraph parent;

      GtkDataboxLinesPrivate *priv;
   };

   struct _GtkDataboxLinesClass
   {
      GtkDataboxXYCGraphClass parent_class;
   };

   GType gtk_databox_lines_get_type (void);

   GtkDataboxGraph *gtk_databox_lines_new (guint len, gfloat * X, gfloat * Y,
        GdkColor * color, guint size);

G_END_DECLS
# 36 "gui.c" 2


# 1 "/usr/local/include/gtkdatabox_grid.h" 1 3
# 36 "/usr/local/include/gtkdatabox_grid.h" 3
G_BEGIN_DECLS
# 60 "/usr/local/include/gtkdatabox_grid.h" 3
   typedef struct _GtkDataboxGrid GtkDataboxGrid;

   typedef struct _GtkDataboxGridClass GtkDataboxGridClass;
# 71 "/usr/local/include/gtkdatabox_grid.h" 3
   typedef struct _GtkDataboxGridPrivate GtkDataboxGridPrivate;

   struct _GtkDataboxGrid
   {
      GtkDataboxGraph parent;

      GtkDataboxGridPrivate *priv;
   };

   struct _GtkDataboxGridClass
   {
      GtkDataboxGraphClass parent_class;
   };

   GType gtk_databox_grid_get_type (void);

   GtkDataboxGraph *gtk_databox_grid_new (gint hlines, gint vlines,
       GdkColor * color, guint size);

   void gtk_databox_grid_set_hlines (GtkDataboxGrid * grid, gint hlines);
   gint gtk_databox_grid_get_hlines (GtkDataboxGrid * grid);

   void gtk_databox_grid_set_vlines (GtkDataboxGrid * grid, gint vlines);
   gint gtk_databox_grid_get_vlines (GtkDataboxGrid * grid);

G_END_DECLS
# 39 "gui.c" 2

# 1 "/usr/include/math.h" 1 3 4
# 30 "/usr/include/math.h" 3 4




# 1 "/usr/include/bits/huge_val.h" 1 3 4
# 35 "/usr/include/math.h" 2 3 4
# 47 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathdef.h" 1 3 4
# 48 "/usr/include/math.h" 2 3 4
# 71 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls.h" 1 3 4
# 53 "/usr/include/bits/mathcalls.h" 3 4


extern double acos (double __x) ; extern double __acos (double __x) ;

extern double asin (double __x) ; extern double __asin (double __x) ;

extern double atan (double __x) ; extern double __atan (double __x) ;

extern double atan2 (double __y, double __x) ; extern double __atan2 (double __y, double __x) ;


extern double cos (double __x) ; extern double __cos (double __x) ;

extern double sin (double __x) ; extern double __sin (double __x) ;

extern double tan (double __x) ; extern double __tan (double __x) ;




extern double cosh (double __x) ; extern double __cosh (double __x) ;

extern double sinh (double __x) ; extern double __sinh (double __x) ;

extern double tanh (double __x) ; extern double __tanh (double __x) ;

# 87 "/usr/include/bits/mathcalls.h" 3 4


extern double acosh (double __x) ; extern double __acosh (double __x) ;

extern double asinh (double __x) ; extern double __asinh (double __x) ;

extern double atanh (double __x) ; extern double __atanh (double __x) ;







extern double exp (double __x) ; extern double __exp (double __x) ;


extern double frexp (double __x, int *__exponent) ; extern double __frexp (double __x, int *__exponent) ;


extern double ldexp (double __x, int __exponent) ; extern double __ldexp (double __x, int __exponent) ;


extern double log (double __x) ; extern double __log (double __x) ;


extern double log10 (double __x) ; extern double __log10 (double __x) ;


extern double modf (double __x, double *__iptr) ; extern double __modf (double __x, double *__iptr) ;

# 127 "/usr/include/bits/mathcalls.h" 3 4


extern double expm1 (double __x) ; extern double __expm1 (double __x) ;


extern double log1p (double __x) ; extern double __log1p (double __x) ;


extern double logb (double __x) ; extern double __logb (double __x) ;

# 152 "/usr/include/bits/mathcalls.h" 3 4


extern double pow (double __x, double __y) ; extern double __pow (double __x, double __y) ;


extern double sqrt (double __x) ; extern double __sqrt (double __x) ;





extern double hypot (double __x, double __y) ; extern double __hypot (double __x, double __y) ;






extern double cbrt (double __x) ; extern double __cbrt (double __x) ;








extern double ceil (double __x) ; extern double __ceil (double __x) ;


extern double fabs (double __x) ; extern double __fabs (double __x) ;


extern double floor (double __x) ; extern double __floor (double __x) ;


extern double fmod (double __x, double __y) ; extern double __fmod (double __x, double __y) ;




extern int __isinf (double __value) ;


extern int __finite (double __value) ;





extern int isinf (double __value) ;


extern int finite (double __value) ;


extern double drem (double __x, double __y) ; extern double __drem (double __x, double __y) ;



extern double significand (double __x) ; extern double __significand (double __x) ;





extern double copysign (double __x, double __y) ; extern double __copysign (double __x, double __y) ;

# 231 "/usr/include/bits/mathcalls.h" 3 4
extern int __isnan (double __value) ;



extern int isnan (double __value) ;


extern double j0 (double) ; extern double __j0 (double) ;
extern double j1 (double) ; extern double __j1 (double) ;
extern double jn (int, double) ; extern double __jn (int, double) ;
extern double y0 (double) ; extern double __y0 (double) ;
extern double y1 (double) ; extern double __y1 (double) ;
extern double yn (int, double) ; extern double __yn (int, double) ;






extern double erf (double) ; extern double __erf (double) ;
extern double erfc (double) ; extern double __erfc (double) ;
extern double lgamma (double) ; extern double __lgamma (double) ;

# 265 "/usr/include/bits/mathcalls.h" 3 4
extern double gamma (double) ; extern double __gamma (double) ;






extern double lgamma_r (double, int *__signgamp) ; extern double __lgamma_r (double, int *__signgamp) ;







extern double rint (double __x) ; extern double __rint (double __x) ;


extern double nextafter (double __x, double __y) ; extern double __nextafter (double __x, double __y) ;





extern double remainder (double __x, double __y) ; extern double __remainder (double __x, double __y) ;



extern double scalbn (double __x, int __n) ; extern double __scalbn (double __x, int __n) ;



extern int ilogb (double __x) ; extern int __ilogb (double __x) ;
# 359 "/usr/include/bits/mathcalls.h" 3 4





extern double scalb (double __x, double __n) ; extern double __scalb (double __x, double __n) ;
# 72 "/usr/include/math.h" 2 3 4
# 94 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls.h" 1 3 4
# 53 "/usr/include/bits/mathcalls.h" 3 4


extern float acosf (float __x) ; extern float __acosf (float __x) ;

extern float asinf (float __x) ; extern float __asinf (float __x) ;

extern float atanf (float __x) ; extern float __atanf (float __x) ;

extern float atan2f (float __y, float __x) ; extern float __atan2f (float __y, float __x) ;


extern float cosf (float __x) ; extern float __cosf (float __x) ;

extern float sinf (float __x) ; extern float __sinf (float __x) ;

extern float tanf (float __x) ; extern float __tanf (float __x) ;




extern float coshf (float __x) ; extern float __coshf (float __x) ;

extern float sinhf (float __x) ; extern float __sinhf (float __x) ;

extern float tanhf (float __x) ; extern float __tanhf (float __x) ;

# 87 "/usr/include/bits/mathcalls.h" 3 4


extern float acoshf (float __x) ; extern float __acoshf (float __x) ;

extern float asinhf (float __x) ; extern float __asinhf (float __x) ;

extern float atanhf (float __x) ; extern float __atanhf (float __x) ;







extern float expf (float __x) ; extern float __expf (float __x) ;


extern float frexpf (float __x, int *__exponent) ; extern float __frexpf (float __x, int *__exponent) ;


extern float ldexpf (float __x, int __exponent) ; extern float __ldexpf (float __x, int __exponent) ;


extern float logf (float __x) ; extern float __logf (float __x) ;


extern float log10f (float __x) ; extern float __log10f (float __x) ;


extern float modff (float __x, float *__iptr) ; extern float __modff (float __x, float *__iptr) ;

# 127 "/usr/include/bits/mathcalls.h" 3 4


extern float expm1f (float __x) ; extern float __expm1f (float __x) ;


extern float log1pf (float __x) ; extern float __log1pf (float __x) ;


extern float logbf (float __x) ; extern float __logbf (float __x) ;

# 152 "/usr/include/bits/mathcalls.h" 3 4


extern float powf (float __x, float __y) ; extern float __powf (float __x, float __y) ;


extern float sqrtf (float __x) ; extern float __sqrtf (float __x) ;





extern float hypotf (float __x, float __y) ; extern float __hypotf (float __x, float __y) ;






extern float cbrtf (float __x) ; extern float __cbrtf (float __x) ;








extern float ceilf (float __x) ; extern float __ceilf (float __x) ;


extern float fabsf (float __x) ; extern float __fabsf (float __x) ;


extern float floorf (float __x) ; extern float __floorf (float __x) ;


extern float fmodf (float __x, float __y) ; extern float __fmodf (float __x, float __y) ;




extern int __isinff (float __value) ;


extern int __finitef (float __value) ;





extern int isinff (float __value) ;


extern int finitef (float __value) ;


extern float dremf (float __x, float __y) ; extern float __dremf (float __x, float __y) ;



extern float significandf (float __x) ; extern float __significandf (float __x) ;





extern float copysignf (float __x, float __y) ; extern float __copysignf (float __x, float __y) ;

# 231 "/usr/include/bits/mathcalls.h" 3 4
extern int __isnanf (float __value) ;



extern int isnanf (float __value) ;


extern float j0f (float) ; extern float __j0f (float) ;
extern float j1f (float) ; extern float __j1f (float) ;
extern float jnf (int, float) ; extern float __jnf (int, float) ;
extern float y0f (float) ; extern float __y0f (float) ;
extern float y1f (float) ; extern float __y1f (float) ;
extern float ynf (int, float) ; extern float __ynf (int, float) ;






extern float erff (float) ; extern float __erff (float) ;
extern float erfcf (float) ; extern float __erfcf (float) ;
extern float lgammaf (float) ; extern float __lgammaf (float) ;

# 265 "/usr/include/bits/mathcalls.h" 3 4
extern float gammaf (float) ; extern float __gammaf (float) ;






extern float lgammaf_r (float, int *__signgamp) ; extern float __lgammaf_r (float, int *__signgamp) ;







extern float rintf (float __x) ; extern float __rintf (float __x) ;


extern float nextafterf (float __x, float __y) ; extern float __nextafterf (float __x, float __y) ;





extern float remainderf (float __x, float __y) ; extern float __remainderf (float __x, float __y) ;



extern float scalbnf (float __x, int __n) ; extern float __scalbnf (float __x, int __n) ;



extern int ilogbf (float __x) ; extern int __ilogbf (float __x) ;
# 359 "/usr/include/bits/mathcalls.h" 3 4





extern float scalbf (float __x, float __n) ; extern float __scalbf (float __x, float __n) ;
# 95 "/usr/include/math.h" 2 3 4
# 141 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls.h" 1 3 4
# 53 "/usr/include/bits/mathcalls.h" 3 4


extern long double acosl (long double __x) ; extern long double __acosl (long double __x) ;

extern long double asinl (long double __x) ; extern long double __asinl (long double __x) ;

extern long double atanl (long double __x) ; extern long double __atanl (long double __x) ;

extern long double atan2l (long double __y, long double __x) ; extern long double __atan2l (long double __y, long double __x) ;


extern long double cosl (long double __x) ; extern long double __cosl (long double __x) ;

extern long double sinl (long double __x) ; extern long double __sinl (long double __x) ;

extern long double tanl (long double __x) ; extern long double __tanl (long double __x) ;




extern long double coshl (long double __x) ; extern long double __coshl (long double __x) ;

extern long double sinhl (long double __x) ; extern long double __sinhl (long double __x) ;

extern long double tanhl (long double __x) ; extern long double __tanhl (long double __x) ;

# 87 "/usr/include/bits/mathcalls.h" 3 4


extern long double acoshl (long double __x) ; extern long double __acoshl (long double __x) ;

extern long double asinhl (long double __x) ; extern long double __asinhl (long double __x) ;

extern long double atanhl (long double __x) ; extern long double __atanhl (long double __x) ;







extern long double expl (long double __x) ; extern long double __expl (long double __x) ;


extern long double frexpl (long double __x, int *__exponent) ; extern long double __frexpl (long double __x, int *__exponent) ;


extern long double ldexpl (long double __x, int __exponent) ; extern long double __ldexpl (long double __x, int __exponent) ;


extern long double logl (long double __x) ; extern long double __logl (long double __x) ;


extern long double log10l (long double __x) ; extern long double __log10l (long double __x) ;


extern long double modfl (long double __x, long double *__iptr) ; extern long double __modfl (long double __x, long double *__iptr) ;

# 127 "/usr/include/bits/mathcalls.h" 3 4


extern long double expm1l (long double __x) ; extern long double __expm1l (long double __x) ;


extern long double log1pl (long double __x) ; extern long double __log1pl (long double __x) ;


extern long double logbl (long double __x) ; extern long double __logbl (long double __x) ;

# 152 "/usr/include/bits/mathcalls.h" 3 4


extern long double powl (long double __x, long double __y) ; extern long double __powl (long double __x, long double __y) ;


extern long double sqrtl (long double __x) ; extern long double __sqrtl (long double __x) ;





extern long double hypotl (long double __x, long double __y) ; extern long double __hypotl (long double __x, long double __y) ;






extern long double cbrtl (long double __x) ; extern long double __cbrtl (long double __x) ;








extern long double ceill (long double __x) ; extern long double __ceill (long double __x) ;


extern long double fabsl (long double __x) ; extern long double __fabsl (long double __x) ;


extern long double floorl (long double __x) ; extern long double __floorl (long double __x) ;


extern long double fmodl (long double __x, long double __y) ; extern long double __fmodl (long double __x, long double __y) ;




extern int __isinfl (long double __value) ;


extern int __finitel (long double __value) ;





extern int isinfl (long double __value) ;


extern int finitel (long double __value) ;


extern long double dreml (long double __x, long double __y) ; extern long double __dreml (long double __x, long double __y) ;



extern long double significandl (long double __x) ; extern long double __significandl (long double __x) ;





extern long double copysignl (long double __x, long double __y) ; extern long double __copysignl (long double __x, long double __y) ;

# 231 "/usr/include/bits/mathcalls.h" 3 4
extern int __isnanl (long double __value) ;



extern int isnanl (long double __value) ;


extern long double j0l (long double) ; extern long double __j0l (long double) ;
extern long double j1l (long double) ; extern long double __j1l (long double) ;
extern long double jnl (int, long double) ; extern long double __jnl (int, long double) ;
extern long double y0l (long double) ; extern long double __y0l (long double) ;
extern long double y1l (long double) ; extern long double __y1l (long double) ;
extern long double ynl (int, long double) ; extern long double __ynl (int, long double) ;






extern long double erfl (long double) ; extern long double __erfl (long double) ;
extern long double erfcl (long double) ; extern long double __erfcl (long double) ;
extern long double lgammal (long double) ; extern long double __lgammal (long double) ;

# 265 "/usr/include/bits/mathcalls.h" 3 4
extern long double gammal (long double) ; extern long double __gammal (long double) ;






extern long double lgammal_r (long double, int *__signgamp) ; extern long double __lgammal_r (long double, int *__signgamp) ;







extern long double rintl (long double __x) ; extern long double __rintl (long double __x) ;


extern long double nextafterl (long double __x, long double __y) ; extern long double __nextafterl (long double __x, long double __y) ;





extern long double remainderl (long double __x, long double __y) ; extern long double __remainderl (long double __x, long double __y) ;



extern long double scalbnl (long double __x, int __n) ; extern long double __scalbnl (long double __x, int __n) ;



extern int ilogbl (long double __x) ; extern int __ilogbl (long double __x) ;
# 359 "/usr/include/bits/mathcalls.h" 3 4





extern long double scalbl (long double __x, long double __n) ; extern long double __scalbl (long double __x, long double __n) ;
# 142 "/usr/include/math.h" 2 3 4
# 157 "/usr/include/math.h" 3 4
extern int signgam;
# 284 "/usr/include/math.h" 3 4
typedef enum
{
  _IEEE_ = -1,
  _SVID_,
  _XOPEN_,
  _POSIX_,
  _ISOC_
} _LIB_VERSION_TYPE;




extern _LIB_VERSION_TYPE _LIB_VERSION;
# 309 "/usr/include/math.h" 3 4
struct exception

  {
    int type;
    char *name;
    double arg1;
    double arg2;
    double retval;
  };




extern int matherr (struct exception *__exc);
# 465 "/usr/include/math.h" 3 4

# 41 "gui.c" 2
# 1 "/usr/include/errno.h" 1 3 4
# 32 "/usr/include/errno.h" 3 4




# 1 "/usr/include/bits/errno.h" 1 3 4
# 25 "/usr/include/bits/errno.h" 3 4
# 1 "/usr/include/linux/errno.h" 1 3 4



# 1 "/usr/include/asm/errno.h" 1 3 4
# 1 "/usr/include/asm-generic/errno.h" 1 3 4



# 1 "/usr/include/asm-generic/errno-base.h" 1 3 4
# 5 "/usr/include/asm-generic/errno.h" 2 3 4
# 1 "/usr/include/asm/errno.h" 2 3 4
# 5 "/usr/include/linux/errno.h" 2 3 4
# 26 "/usr/include/bits/errno.h" 2 3 4
# 43 "/usr/include/bits/errno.h" 3 4
extern int *__errno_location (void) ;
# 37 "/usr/include/errno.h" 2 3 4
# 59 "/usr/include/errno.h" 3 4

# 42 "gui.c" 2
# 1 "/usr/include/string.h" 1 3 4
# 28 "/usr/include/string.h" 3 4





# 1 "/usr/lib/gcc/x86_64-linux-gnu/4.3.2/include/stddef.h" 1 3 4
# 34 "/usr/include/string.h" 2 3 4




extern void *memcpy (void * __dest,
       const void * __src, size_t __n)
     ;


extern void *memmove (void *__dest, const void *__src, size_t __n)
     ;






extern void *memccpy (void * __dest, const void * __src,
        int __c, size_t __n)
     ;





extern void *memset (void *__s, int __c, size_t __n) ;


extern int memcmp (const void *__s1, const void *__s2, size_t __n)
     ;


extern void *memchr (const void *__s, int __c, size_t __n)
      ;

# 82 "/usr/include/string.h" 3 4


extern char *strcpy (char * __dest, const char * __src)
     ;

extern char *strncpy (char * __dest,
        const char * __src, size_t __n)
     ;


extern char *strcat (char * __dest, const char * __src)
     ;

extern char *strncat (char * __dest, const char * __src,
        size_t __n) ;


extern int strcmp (const char *__s1, const char *__s2)
     ;

extern int strncmp (const char *__s1, const char *__s2, size_t __n)
     ;


extern int strcoll (const char *__s1, const char *__s2)
     ;

extern size_t strxfrm (char * __dest,
         const char * __src, size_t __n)
     ;

# 130 "/usr/include/string.h" 3 4
extern char *strdup (const char *__s)
     ;
# 165 "/usr/include/string.h" 3 4


extern char *strchr (const char *__s, int __c)
     ;

extern char *strrchr (const char *__s, int __c)
     ;

# 181 "/usr/include/string.h" 3 4



extern size_t strcspn (const char *__s, const char *__reject)
     ;


extern size_t strspn (const char *__s, const char *__accept)
     ;

extern char *strpbrk (const char *__s, const char *__accept)
     ;

extern char *strstr (const char *__haystack, const char *__needle)
     ;



extern char *strtok (char * __s, const char * __delim)
     ;




extern char *__strtok_r (char * __s,
    const char * __delim,
    char ** __save_ptr)
     ;

extern char *strtok_r (char * __s, const char * __delim,
         char ** __save_ptr)
     ;
# 240 "/usr/include/string.h" 3 4


extern size_t strlen (const char *__s)
     ;

# 254 "/usr/include/string.h" 3 4


extern char *strerror (int __errnum) ;

# 270 "/usr/include/string.h" 3 4
extern int strerror_r (int __errnum, char *__buf, size_t __buflen) __asm__ ("" "__xpg_strerror_r") ;
# 294 "/usr/include/string.h" 3 4
extern void __bzero (void *__s, size_t __n) ;



extern void bcopy (const void *__src, void *__dest, size_t __n)
     ;


extern void bzero (void *__s, size_t __n) ;


extern int bcmp (const void *__s1, const void *__s2, size_t __n)
     ;


extern char *index (const char *__s, int __c)
     ;


extern char *rindex (const char *__s, int __c)
     ;



extern int ffs (int __i) ;
# 331 "/usr/include/string.h" 3 4
extern int strcasecmp (const char *__s1, const char *__s2)
     ;


extern int strncasecmp (const char *__s1, const char *__s2, size_t __n)
     ;
# 354 "/usr/include/string.h" 3 4
extern char *strsep (char ** __stringp,
       const char * __delim)
     ;
# 432 "/usr/include/string.h" 3 4

# 43 "gui.c" 2
# 1 "gui.h" 1
# 23 "gui.h"
# 1 "main.h" 1
# 27 "main.h"
# 1 "/usr/include/fftw.h" 1 3 4
# 28 "/usr/include/fftw.h" 3 4
# 1 "/usr/include/stdlib.h" 1 3 4
# 33 "/usr/include/stdlib.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/4.3.2/include/stddef.h" 1 3 4
# 326 "/usr/lib/gcc/x86_64-linux-gnu/4.3.2/include/stddef.h" 3 4
typedef int wchar_t;
# 34 "/usr/include/stdlib.h" 2 3 4


# 96 "/usr/include/stdlib.h" 3 4


typedef struct
  {
    int quot;
    int rem;
  } div_t;



typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;



# 140 "/usr/include/stdlib.h" 3 4
extern size_t __ctype_get_mb_cur_max (void) ;




extern double atof (const char *__nptr)
     ;

extern int atoi (const char *__nptr)
     ;

extern long int atol (const char *__nptr)
     ;





 extern long long int atoll (const char *__nptr)
     ;





extern double strtod (const char * __nptr,
        char ** __endptr)
     ;

# 182 "/usr/include/stdlib.h" 3 4


extern long int strtol (const char * __nptr,
   char ** __endptr, int __base)
     ;

extern unsigned long int strtoul (const char * __nptr,
      char ** __endptr, int __base)
     ;





extern long long int strtoq (const char * __nptr,
        char ** __endptr, int __base)
     ;


extern unsigned long long int strtouq (const char * __nptr,
           char ** __endptr, int __base)
     ;






extern long long int strtoll (const char * __nptr,
         char ** __endptr, int __base)
     ;


extern unsigned long long int strtoull (const char * __nptr,
     char ** __endptr, int __base)
     ;

# 311 "/usr/include/stdlib.h" 3 4
extern char *l64a (long int __n) ;


extern long int a64l (const char *__s)
     ;




# 1 "/usr/include/sys/types.h" 1 3 4
# 29 "/usr/include/sys/types.h" 3 4






typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;




typedef __loff_t loff_t;



typedef __ino_t ino_t;
# 62 "/usr/include/sys/types.h" 3 4
typedef __dev_t dev_t;




typedef __gid_t gid_t;




typedef __mode_t mode_t;




typedef __nlink_t nlink_t;




typedef __uid_t uid_t;





typedef __off_t off_t;
# 100 "/usr/include/sys/types.h" 3 4
typedef __pid_t pid_t;




typedef __id_t id_t;




typedef __ssize_t ssize_t;





typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;





typedef __key_t key_t;
# 133 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/time.h" 1 3 4
# 75 "/usr/include/time.h" 3 4


typedef __time_t time_t;



# 93 "/usr/include/time.h" 3 4
typedef __clockid_t clockid_t;
# 105 "/usr/include/time.h" 3 4
typedef __timer_t timer_t;
# 134 "/usr/include/sys/types.h" 2 3 4
# 147 "/usr/include/sys/types.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/4.3.2/include/stddef.h" 1 3 4
# 148 "/usr/include/sys/types.h" 2 3 4



typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
# 195 "/usr/include/sys/types.h" 3 4
typedef int int8_t ;
typedef int int16_t ;
typedef int int32_t ;
typedef int int64_t ;


typedef unsigned int u_int8_t ;
typedef unsigned int u_int16_t ;
typedef unsigned int u_int32_t ;
typedef unsigned int u_int64_t ;

typedef int register_t ;
# 217 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/endian.h" 1 3 4
# 37 "/usr/include/endian.h" 3 4
# 1 "/usr/include/bits/endian.h" 1 3 4
# 38 "/usr/include/endian.h" 2 3 4
# 218 "/usr/include/sys/types.h" 2 3 4


# 1 "/usr/include/sys/select.h" 1 3 4
# 31 "/usr/include/sys/select.h" 3 4
# 1 "/usr/include/bits/select.h" 1 3 4
# 32 "/usr/include/sys/select.h" 2 3 4


# 1 "/usr/include/bits/sigset.h" 1 3 4
# 24 "/usr/include/bits/sigset.h" 3 4
typedef int __sig_atomic_t;




typedef struct
  {
    unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
  } __sigset_t;
# 35 "/usr/include/sys/select.h" 2 3 4



typedef __sigset_t sigset_t;





# 1 "/usr/include/time.h" 1 3 4
# 121 "/usr/include/time.h" 3 4
struct timespec
  {
    __time_t tv_sec;
    long int tv_nsec;
  };
# 45 "/usr/include/sys/select.h" 2 3 4

# 1 "/usr/include/bits/time.h" 1 3 4
# 69 "/usr/include/bits/time.h" 3 4
struct timeval
  {
    __time_t tv_sec;
    __suseconds_t tv_usec;
  };
# 47 "/usr/include/sys/select.h" 2 3 4


typedef __suseconds_t suseconds_t;





typedef long int __fd_mask;
# 67 "/usr/include/sys/select.h" 3 4
typedef struct
  {






    __fd_mask __fds_bits[1024 / (8 * sizeof (__fd_mask))];


  } fd_set;






typedef __fd_mask fd_mask;
# 99 "/usr/include/sys/select.h" 3 4

# 109 "/usr/include/sys/select.h" 3 4
extern int select (int __nfds, fd_set * __readfds,
     fd_set * __writefds,
     fd_set * __exceptfds,
     struct timeval * __timeout);
# 121 "/usr/include/sys/select.h" 3 4
extern int pselect (int __nfds, fd_set * __readfds,
      fd_set * __writefds,
      fd_set * __exceptfds,
      const struct timespec * __timeout,
      const __sigset_t * __sigmask);



# 221 "/usr/include/sys/types.h" 2 3 4


# 1 "/usr/include/sys/sysmacros.h" 1 3 4
# 30 "/usr/include/sys/sysmacros.h" 3 4

extern unsigned int gnu_dev_major (unsigned long long int __dev)
     ;

extern unsigned int gnu_dev_minor (unsigned long long int __dev)
     ;

extern unsigned long long int gnu_dev_makedev (unsigned int __major,
            unsigned int __minor)
     ;
# 224 "/usr/include/sys/types.h" 2 3 4
# 235 "/usr/include/sys/types.h" 3 4
typedef __blkcnt_t blkcnt_t;



typedef __fsblkcnt_t fsblkcnt_t;



typedef __fsfilcnt_t fsfilcnt_t;
# 270 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/bits/pthreadtypes.h" 1 3 4
# 23 "/usr/include/bits/pthreadtypes.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 24 "/usr/include/bits/pthreadtypes.h" 2 3 4
# 50 "/usr/include/bits/pthreadtypes.h" 3 4
typedef unsigned long int pthread_t;


typedef union
{
  char __size[56];
  long int __align;
} pthread_attr_t;



typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;
# 76 "/usr/include/bits/pthreadtypes.h" 3 4
typedef union
{
  struct __pthread_mutex_s
  {
    int __lock;
    unsigned int __count;
    int __owner;

    unsigned int __nusers;



    int __kind;

    int __spins;
    __pthread_list_t __list;
# 101 "/usr/include/bits/pthreadtypes.h" 3 4
  } __data;
  char __size[40];
  long int __align;
} pthread_mutex_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_mutexattr_t;




typedef union
{
  struct
  {
    int __lock;
    unsigned int __futex;
    unsigned long long int __total_seq;
    unsigned long long int __wakeup_seq;
    unsigned long long int __woken_seq;
    void *__mutex;
    unsigned int __nwaiters;
    unsigned int __broadcast_seq;
  } __data;
  char __size[48];
  long long int __align;
} pthread_cond_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_condattr_t;



typedef unsigned int pthread_key_t;



typedef int pthread_once_t;





typedef union
{

  struct
  {
    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;
    int __writer;
    int __shared;
    unsigned long int __pad1;
    unsigned long int __pad2;


    unsigned int __flags;
  } __data;
# 187 "/usr/include/bits/pthreadtypes.h" 3 4
  char __size[56];
  long int __align;
} pthread_rwlock_t;

typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;





typedef volatile int pthread_spinlock_t;




typedef union
{
  char __size[32];
  long int __align;
} pthread_barrier_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;
# 271 "/usr/include/sys/types.h" 2 3 4



# 321 "/usr/include/stdlib.h" 2 3 4






extern long int random (void) ;


extern void srandom (unsigned int __seed) ;





extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen) ;



extern char *setstate (char *__statebuf) ;







struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };

extern int random_r (struct random_data * __buf,
       int32_t * __result) ;

extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     ;

extern int initstate_r (unsigned int __seed, char * __statebuf,
   size_t __statelen,
   struct random_data * __buf)
     ;

extern int setstate_r (char * __statebuf,
         struct random_data * __buf)
     ;






extern int rand (void) ;

extern void srand (unsigned int __seed) ;




extern int rand_r (unsigned int *__seed) ;







extern double drand48 (void) ;
extern double erand48 (unsigned short int __xsubi[3]) ;


extern long int lrand48 (void) ;
extern long int nrand48 (unsigned short int __xsubi[3])
     ;


extern long int mrand48 (void) ;
extern long int jrand48 (unsigned short int __xsubi[3])
     ;


extern void srand48 (long int __seedval) ;
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     ;
extern void lcong48 (unsigned short int __param[7]) ;





struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    unsigned long long int __a;
  };


extern int drand48_r (struct drand48_data * __buffer,
        double * __result) ;
extern int erand48_r (unsigned short int __xsubi[3],
        struct drand48_data * __buffer,
        double * __result) ;


extern int lrand48_r (struct drand48_data * __buffer,
        long int * __result)
     ;
extern int nrand48_r (unsigned short int __xsubi[3],
        struct drand48_data * __buffer,
        long int * __result)
     ;


extern int mrand48_r (struct drand48_data * __buffer,
        long int * __result)
     ;
extern int jrand48_r (unsigned short int __xsubi[3],
        struct drand48_data * __buffer,
        long int * __result)
     ;


extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     ;

extern int seed48_r (unsigned short int __seed16v[3],
       struct drand48_data *__buffer) ;

extern int lcong48_r (unsigned short int __param[7],
        struct drand48_data *__buffer)
     ;









extern void *malloc (size_t __size) ;

extern void *calloc (size_t __nmemb, size_t __size)
     ;










extern void *realloc (void *__ptr, size_t __size)
     ;

extern void free (void *__ptr) ;




extern void cfree (void *__ptr) ;



# 1 "/usr/include/alloca.h" 1 3 4
# 25 "/usr/include/alloca.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/4.3.2/include/stddef.h" 1 3 4
# 26 "/usr/include/alloca.h" 2 3 4







extern void *alloca (size_t __size) ;






# 498 "/usr/include/stdlib.h" 2 3 4




extern void *valloc (size_t __size) ;




extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     ;




extern void abort (void) ;



extern int atexit (void (*__func) (void)) ;





extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     ;






extern void exit (int __status) ;

# 543 "/usr/include/stdlib.h" 3 4


extern char *getenv (const char *__name) ;




extern char *__secure_getenv (const char *__name)
     ;





extern int putenv (char *__string) ;





extern int setenv (const char *__name, const char *__value, int __replace)
     ;


extern int unsetenv (const char *__name) ;






extern int clearenv (void) ;
# 583 "/usr/include/stdlib.h" 3 4
extern char *mktemp (char *__template) ;
# 594 "/usr/include/stdlib.h" 3 4
extern int mkstemp (char *__template) ;
# 614 "/usr/include/stdlib.h" 3 4
extern char *mkdtemp (char *__template) ;
# 640 "/usr/include/stdlib.h" 3 4





extern int system (const char *__command) ;

# 662 "/usr/include/stdlib.h" 3 4
extern char *realpath (const char * __name,
         char * __resolved) ;






typedef int (*__compar_fn_t) (const void *, const void *);
# 680 "/usr/include/stdlib.h" 3 4



extern void *bsearch (const void *__key, const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
     ;



extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) ;
# 699 "/usr/include/stdlib.h" 3 4
extern int abs (int __x) ;
extern long int labs (long int __x) ;












extern div_t div (int __numer, int __denom)
     ;
extern ldiv_t ldiv (long int __numer, long int __denom)
     ;

# 735 "/usr/include/stdlib.h" 3 4
extern char *ecvt (double __value, int __ndigit, int * __decpt,
     int * __sign) ;




extern char *fcvt (double __value, int __ndigit, int * __decpt,
     int * __sign) ;




extern char *gcvt (double __value, int __ndigit, char *__buf)
     ;




extern char *qecvt (long double __value, int __ndigit,
      int * __decpt, int * __sign)
     ;
extern char *qfcvt (long double __value, int __ndigit,
      int * __decpt, int * __sign)
     ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
     ;




extern int ecvt_r (double __value, int __ndigit, int * __decpt,
     int * __sign, char * __buf,
     size_t __len) ;
extern int fcvt_r (double __value, int __ndigit, int * __decpt,
     int * __sign, char * __buf,
     size_t __len) ;

extern int qecvt_r (long double __value, int __ndigit,
      int * __decpt, int * __sign,
      char * __buf, size_t __len)
     ;
extern int qfcvt_r (long double __value, int __ndigit,
      int * __decpt, int * __sign,
      char * __buf, size_t __len)
     ;







extern int mblen (const char *__s, size_t __n) ;


extern int mbtowc (wchar_t * __pwc,
     const char * __s, size_t __n) ;


extern int wctomb (char *__s, wchar_t __wchar) ;



extern size_t mbstowcs (wchar_t * __pwcs,
   const char * __s, size_t __n) ;

extern size_t wcstombs (char * __s,
   const wchar_t * __pwcs, size_t __n)
     ;








extern int rpmatch (const char *__response) ;
# 840 "/usr/include/stdlib.h" 3 4
extern int posix_openpt (int __oflag) ;
# 875 "/usr/include/stdlib.h" 3 4
extern int getloadavg (double __loadavg[], int __nelem)
     ;
# 891 "/usr/include/stdlib.h" 3 4

# 29 "/usr/include/fftw.h" 2 3 4
# 46 "/usr/include/fftw.h" 3 4
typedef double fftw_real;





typedef struct {
     fftw_real re, im;
} fftw_complex;




typedef enum {
     FFTW_FORWARD = -1, FFTW_BACKWARD = 1
} fftw_direction;


typedef fftw_complex FFTW_COMPLEX;
typedef fftw_real FFTW_REAL;
# 81 "/usr/include/fftw.h" 3 4
typedef enum {
     FFTW_SUCCESS = 0, FFTW_FAILURE = -1
} fftw_status;




typedef void (fftw_notw_codelet)
     (const fftw_complex *, fftw_complex *, int, int);
typedef void (fftw_twiddle_codelet)
     (fftw_complex *, const fftw_complex *, int,
      int, int);
typedef void (fftw_generic_codelet)
     (fftw_complex *, const fftw_complex *, int,
      int, int, int);
typedef void (fftw_real2hc_codelet)
     (const fftw_real *, fftw_real *, fftw_real *,
      int, int, int);
typedef void (fftw_hc2real_codelet)
     (const fftw_real *, const fftw_real *,
      fftw_real *, int, int, int);
typedef void (fftw_hc2hc_codelet)
     (fftw_real *, const fftw_complex *,
      int, int, int);
typedef void (fftw_rgeneric_codelet)
     (fftw_real *, const fftw_complex *, int,
      int, int, int);
# 116 "/usr/include/fftw.h" 3 4
enum fftw_node_type {
     FFTW_NOTW, FFTW_TWIDDLE, FFTW_GENERIC, FFTW_RADER,
     FFTW_REAL2HC, FFTW_HC2REAL, FFTW_HC2HC, FFTW_RGENERIC
};


typedef struct {
     const char *name;
     void (*codelet) ();
     int size;
     fftw_direction dir;
     enum fftw_node_type type;
     int signature;
     int ntwiddle;
     const int *twiddle_order;




} fftw_codelet_desc;
# 151 "/usr/include/fftw.h" 3 4
extern const char * fftw_version;
# 166 "/usr/include/fftw.h" 3 4
typedef struct fftw_twiddle_struct {
     int n;
     const fftw_codelet_desc *cdesc;
     fftw_complex *twarray;
     struct fftw_twiddle_struct *next;
     int refcnt;
} fftw_twiddle;

typedef struct fftw_rader_data_struct {
     struct fftw_plan_struct *plan;
     fftw_complex *omega;
     int g, ginv;
     int p, flags, refcount;
     struct fftw_rader_data_struct *next;
     fftw_codelet_desc *cdesc;
} fftw_rader_data;

typedef void (fftw_rader_codelet)
     (fftw_complex *, const fftw_complex *, int,
      int, int, fftw_rader_data *);


typedef struct fftw_plan_node_struct {
     enum fftw_node_type type;

     union {

   struct {
        int size;
        fftw_notw_codelet *codelet;
        const fftw_codelet_desc *codelet_desc;
   } notw;


   struct {
        int size;
        fftw_twiddle_codelet *codelet;
        fftw_twiddle *tw;
        struct fftw_plan_node_struct *recurse;
        const fftw_codelet_desc *codelet_desc;
   } twiddle;


   struct {
        int size;
        fftw_generic_codelet *codelet;
        fftw_twiddle *tw;
        struct fftw_plan_node_struct *recurse;
   } generic;


   struct {
        int size;
        fftw_rader_codelet *codelet;
        fftw_rader_data *rader_data;
        fftw_twiddle *tw;
        struct fftw_plan_node_struct *recurse;
   } rader;


   struct {
        int size;
        fftw_real2hc_codelet *codelet;
        const fftw_codelet_desc *codelet_desc;
   } real2hc;


   struct {
        int size;
        fftw_hc2real_codelet *codelet;
        const fftw_codelet_desc *codelet_desc;
   } hc2real;


   struct {
        int size;
        fftw_direction dir;
        fftw_hc2hc_codelet *codelet;
        fftw_twiddle *tw;
        struct fftw_plan_node_struct *recurse;
        const fftw_codelet_desc *codelet_desc;
   } hc2hc;


   struct {
        int size;
        fftw_direction dir;
        fftw_rgeneric_codelet *codelet;
        fftw_twiddle *tw;
        struct fftw_plan_node_struct *recurse;
   } rgeneric;
     } nodeu;

     int refcnt;
} fftw_plan_node;

typedef enum {
     FFTW_NORMAL_RECURSE = 0,
     FFTW_VECTOR_RECURSE = 1
} fftw_recurse_kind;

struct fftw_plan_struct {
     int n;
     int refcnt;
     fftw_direction dir;
     int flags;
     int wisdom_signature;
     enum fftw_node_type wisdom_type;
     struct fftw_plan_struct *next;
     fftw_plan_node *root;
     double cost;
     fftw_recurse_kind recurse_kind;
     int vector_size;
};

typedef struct fftw_plan_struct *fftw_plan;
# 301 "/usr/include/fftw.h" 3 4
extern fftw_plan fftw_create_plan_specific(int n, fftw_direction dir,
        int flags,
        fftw_complex *in, int istride,
      fftw_complex *out, int ostride);

extern fftw_plan fftw_create_plan(int n, fftw_direction dir, int flags);
extern void fftw_print_plan(fftw_plan plan);
extern void fftw_destroy_plan(fftw_plan plan);
extern void fftw(fftw_plan plan, int howmany, fftw_complex *in, int istride,
   int idist, fftw_complex *out, int ostride, int odist);
extern void fftw_one(fftw_plan plan, fftw_complex *in, fftw_complex *out);
extern void fftw_die(const char *s);
extern void *fftw_malloc(size_t n);
extern void fftw_free(void *p);
extern void fftw_check_memory_leaks(void);
extern void fftw_print_max_memory_usage(void);

typedef void *(*fftw_malloc_type_function) (size_t n);
typedef void (*fftw_free_type_function) (void *p);
typedef void (*fftw_die_type_function) (const char *errString);
extern fftw_malloc_type_function fftw_malloc_hook;
extern fftw_free_type_function fftw_free_hook;
extern fftw_die_type_function fftw_die_hook;

extern size_t fftw_sizeof_fftw_real(void);







extern void fftw_forget_wisdom(void);
extern void fftw_export_wisdom(void (*emitter) (char c, void *), void *data);
extern fftw_status fftw_import_wisdom(int (*g) (void *), void *data);
extern void fftw_export_wisdom_to_file(FILE *output_file);
extern fftw_status fftw_import_wisdom_from_file(FILE *input_file);
extern char *fftw_export_wisdom_to_string(void);
extern fftw_status fftw_import_wisdom_from_string(const char *input_string);






extern void fftw_fprint_plan(FILE *f, fftw_plan plan);




typedef struct {
     int is_in_place;

     int rank;



     int *n;



     fftw_direction dir;

     int *n_before;


     int *n_after;

     fftw_plan *plans;

     int nbuffers, nwork;
     fftw_complex *work;




} fftwnd_data;

typedef fftwnd_data *fftwnd_plan;


extern fftwnd_plan fftw2d_create_plan(int nx, int ny, fftw_direction dir,
          int flags);
extern fftwnd_plan fftw3d_create_plan(int nx, int ny, int nz,
          fftw_direction dir, int flags);
extern fftwnd_plan fftwnd_create_plan(int rank, const int *n,
          fftw_direction dir,
          int flags);

extern fftwnd_plan fftw2d_create_plan_specific(int nx, int ny,
            fftw_direction dir,
            int flags,
        fftw_complex *in, int istride,
      fftw_complex *out, int ostride);
extern fftwnd_plan fftw3d_create_plan_specific(int nx, int ny, int nz,
        fftw_direction dir, int flags,
        fftw_complex *in, int istride,
      fftw_complex *out, int ostride);
extern fftwnd_plan fftwnd_create_plan_specific(int rank, const int *n,
            fftw_direction dir,
            int flags,
        fftw_complex *in, int istride,
      fftw_complex *out, int ostride);


extern void fftwnd_destroy_plan(fftwnd_plan plan);


extern void fftwnd_fprint_plan(FILE *f, fftwnd_plan p);
extern void fftwnd_print_plan(fftwnd_plan p);



extern void fftwnd(fftwnd_plan plan, int howmany,
     fftw_complex *in, int istride, int idist,
     fftw_complex *out, int ostride, int odist);
extern void fftwnd_one(fftwnd_plan p, fftw_complex *in, fftw_complex *out);
# 28 "main.h" 2






struct dat
{
   double k;
};

struct FFT_Frame
{
   fftw_plan plan;
   fftw_plan reverse_plan;
   short * prewin_buffer_data_1;
   short * prewin_buffer_data_2;
   short * buffer_data_1;
   short * buffer_data_2;
   double * fft_returned_1;
   double * fft_returned_2;
   double * rfft_returned_1;
   float volume_pink;
   char pink_muted;

   short * delay;
   int delay_size;
   char find_delay;
   char find_impulse;
};
static gint
MyGTKFunction (struct FFT_Frame * frame_data);
# 24 "gui.h" 2
# 38 "gui.h"
gboolean gui_idle_func (struct FFT_Frame * data);

gboolean create_gui (struct FFT_Frame * data);
# 44 "gui.c" 2
# 1 "testfft.h" 1
# 24 "testfft.h"
# 1 "main.h" 1
# 25 "testfft.h" 2
# 39 "testfft.h"
struct AUDIO_SESSION
{
   fftw_plan plan;
   short * buffer_data;
   double * fft_returned;
};

int fft_capture(struct FFT_Frame * session);

int impulse_capture(struct FFT_Frame * session);
# 45 "gui.c" 2
# 1 "config.h" 1
# 46 "gui.c" 2




static GdkPixmap *measured_pixmap = ((void *)0);
static GdkPixmap *reference_pixmap = ((void *)0);
static GtkWidget *measured_draw;
static GtkWidget *reference_draw;

static GtkDataboxGraph **graph;
static GtkDataboxGraph *graph_impulse;
static GtkWidget *box;
static GtkWidget *impulse_box;
static GtkWidget *about_me_window = ((void *)0);
static GtkWidget *about_ok = ((void *)0);
static GtkWidget *delay_window = ((void *)0);
static GtkWidget *impulse_window = ((void *)0);
static GtkWidget *volume_pink_gui = ((void *)0);
static GtkWidget *pinknoise_button = ((void *)0);
static GtkWidget *transfer_function_toggle = ((void *)0);
static GtkWidget *buffer_button[5] = { ((void *)0), ((void *)0), ((void *)0), ((void *)0), ((void *)0) };
static GtkWidget *buffer_menu[5] = { ((void *)0), ((void *)0), ((void *)0), ((void *)0), ((void *)0) };
static gfloat volume_pink_value = 0;
static gfloat *guiX = ((void *)0);
static gfloat *guiY = ((void *)0);
static gfloat *gui_impulse_Y = ((void *)0);
static gfloat *gui_impulse_X = ((void *)0);
static gfloat guiYBuf[5][8192/2];
static gfloat guiYBufAvgHold[8192/2];
static char* save_name = ((void *)0);
static char * home_string, *file_path1, *file_path2;

static char pinknoise_muted = 0;
static char find_delay = 0;
static char update_delay = 0;
static char buffer[5] = {2, 2, 2, 2, 2};
static gfloat avg_gain = 0;
static int buffer_last_clicked;
static GtkWidget *bkg_dialog;

static GtkWidget *cb;
static GtkWidget *save_now;
static GtkWidget *save_as;
static GtkWidget *open_menuitem;

static gint avg_index = 0;
static gchar tf = 1;
static gfloat avgY[8192/2][32];

static gint gui_idle = 0;
static gfloat gui_frequency = 3. * G_PI / 2.;
static GtkWidget *gui_label = ((void *)0);
static GtkWidget *gui_db_label = ((void *)0);
static GtkWidget *gui_status_delay_label = ((void *)0);
static GtkWidget *gui_sb_label = ((void *)0);
static GtkWidget *gui_sb = ((void *)0);
static GtkWidget *open_dialog = ((void *)0);
static GtkWidget *save_as_dialog = ((void *)0);
static guint gui_counter = 0;

static GdkColor background_color;
static GdkColor grid_color;
static GdkColor trace_transfer_color;
static GdkColor trace_impulse_color;
static GdkColor line_color[5] = {

      {0, 16384 ,16384 ,65535 },
      {0, 0 ,65535 ,0 },
      {0, 65535 ,0 ,0 },
      {0, 65535 ,16384 ,65535 },
      {0, 65535 ,65535 ,65535 }
   };
# 161 "gui.c"
gboolean
gui_idle_func (struct FFT_Frame *data)
{
   gfloat tmp[8192/2];
   gint smoothing;
   gint index;
   gint i;
   gint j, k;
   gint max;
   gfloat temp, max_x, min_x, max_y, min_y, tmp_spin;
   gchar * label = ((void *)0);
   GdkColor myColor1 = { 0, 0x3333, 0x3333, 0x3333 };
   GdkColor myColor2 = { 0, 0x3333, 0x3333, 0x3333 };
   GdkGC *gc1 = ((void *)0);
   GdkGC *gc2 = ((void *)0);

   if (!(G_TYPE_CHECK_INSTANCE_TYPE ((box), (gtk_databox_get_type ()))))
   {
      fprintf(stderr, "Box not a gtk_databox\n");
      return FALSE;
   }
   gc1 = gdk_gc_new(measured_draw->window);
   gc2 = gdk_gc_new(reference_draw->window);

   data->pink_muted = pinknoise_muted;

   data->volume_pink = volume_pink_value;
   avg_index++;
   if (avg_index == 32) avg_index = 0;
   min_y = 0.0;
   max_y = 0.0;

   if (data->find_impulse == 2)
   {

      for (i = 0; i < 8192; i++)
      {
         index = i;
         temp = (gfloat)data->rfft_returned_1[index] / 32767.0;
         gui_impulse_Y[i] = temp;

         if (temp > max_y)
            max_y = temp;
         if (temp < min_y)
            min_y = temp;
      }
   }
   else
   {
      for (i = 0; i < 8192/2; i++)
      {
         index = i;
         if (tf)
            avgY[i][avg_index] = (0.0 + 20.0 * log10((gfloat)data->fft_returned_1[index] / (gfloat)data->fft_returned_2[index]));

         else
            avgY[i][avg_index] = (0.0 + 20.0 * log10((gfloat)data->fft_returned_1[index]));


         tmp[i] = 0;
         for (k = 0; k < 32; k++)
         {
            tmp[i] += avgY[i][k];
         }
         tmp[i] /= 32;


      }
   }

   for (i = 0; i < 8192/2; i++)
   {
      smoothing = (int)pow(10, (((float)i) / ((float)(8192 / 4)) + 1.0));
      smoothing = smoothing > 0 ? smoothing : 0;


      guiY[i] = tmp[i];
      for (j = 1; j <= smoothing; j++)
      {
         guiY[i] += tmp[(i-j)>=0?(i-j):0];
         guiY[i] += tmp[(i+j)<8192/2?(i+j):(8192/2 -1)];
      }
      guiY[i] /= (smoothing * 2.0 + 1.0);
   }
   guiY[0] = tmp[3];
   guiY[1] = tmp[3];
   guiY[2] = tmp[4];
   guiY[8192/2 -1] = tmp[8192/2 -1];
   guiY[8192/2 -2] = tmp[8192/2 -2];

   if (data->find_impulse == 2)
   {
      min_x = 0.0;
      max_x = ((gfloat) 8192) / 44100/2;
      gtk_databox_set_total_limits ((G_TYPE_CHECK_INSTANCE_CAST ((impulse_box), (gtk_databox_get_type ()), GtkDatabox)), min_x, max_x, max_y, min_y);

      gtk_widget_queue_draw(GTK_WIDGET (impulse_box));
      data->find_impulse = 0;
   }
   if (data->find_delay == 1)
   {
      label = g_strdup_printf ( "<b>Finding Delay.....</b>" );
      gtk_label_set_markup (GTK_LABEL (gui_sb_label), label);
      g_free((gpointer)label);
   }

   if (data->find_delay == 2)
   {
      label = g_strdup_printf ( "<b> Found:  %g secs </b>", (float) data->delay_size * (1.0 / (float)44100) );
      gtk_label_set_markup (GTK_LABEL (gui_sb_label), label);
      g_free((gpointer)label);
      data->find_delay = 0;
   }
   if (update_delay)
   {
      tmp_spin = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON (gui_sb));
      data->delay_size = (int) (((gfloat)tmp_spin) * (gfloat) 44100);
      update_delay = 0;
      gtk_widget_hide_all (delay_window);
   }
   label = g_strdup_printf ( "Current Delay %g msecs", (float) data->delay_size * (1.0 / (float)44100) * 1000.0 );
   gtk_label_set_text (GTK_LABEL (gui_status_delay_label), label);
   g_free((gpointer)label);



   max = 0;
   for (k = 8192 - 2000; k < 8192; k++)
   {
      if (max < data->buffer_data_1[k])
         max = data->buffer_data_1[k];
   }

   if (max > 20000)
   {
      myColor1.red = 0xFFFF;
      myColor1.green = 0x3333;
      myColor1.blue = 0x3333;
   }
   else if (max > 5000)
   {
      myColor1.red = 0xCCCC;
      myColor1.green = 0xFFFF;
      myColor1.blue = 0x3333;
   }
   else if (max > 1000)
   {
      myColor1.red = 0x3333;
      myColor1.green = 0xDDDD;
      myColor1.blue = 0x3333;
   }
   else if (max > 40)
   {
      myColor1.red = 0x3333;
      myColor1.green = 0x8888;
      myColor1.blue = 0x3333;
   }

   gdk_gc_set_rgb_fg_color (gc1, &myColor1);
   gdk_draw_rectangle (measured_pixmap, gc1, TRUE, 7, 7, 16, 16);
   gdk_draw_drawable (measured_draw->window, measured_draw->style->fg_gc[GTK_WIDGET_STATE (measured_draw)], measured_pixmap, 5, 5, 5, 5, 20, 20);

   max = 0;
   for (k = 8192 - 2000; k < 8192; k++)
   {
      if (max < data->buffer_data_2[k])
         max = data->buffer_data_2[k];
   }

   if (max > 20000)
   {
      myColor2.red = 0xFFFF;
      myColor2.green = 0x3333;
      myColor2.blue = 0x3333;
   }
   else if (max > 5000)
   {
      myColor2.red = 0xCCCC;
      myColor2.green = 0xFFFF;
      myColor2.blue = 0x3333;
   }
   else if (max > 1000)
   {
      myColor2.red = 0x3333;
      myColor2.green = 0xDDDD;
      myColor2.blue = 0x3333;
   }
   else if (max > 40)
   {
      myColor2.red = 0x3333;
      myColor2.green = 0x8888;
      myColor2.blue = 0x3333;
   }
   gdk_gc_set_rgb_fg_color (gc2, &myColor2);



   gdk_draw_rectangle (reference_pixmap, gc2, TRUE, 7, 7, 16, 16);
   gdk_draw_drawable (reference_draw->window, reference_draw->style->fg_gc[GTK_WIDGET_STATE (reference_draw)], reference_pixmap, 5, 5, 5, 5, 20, 20);

   gtk_widget_queue_draw(GTK_WIDGET (box));
   g_object_unref(gc1);
   g_object_unref(gc2);
   return TRUE;
}

static void
delay_custom_cb(GtkWidget *widget)
{
   update_delay = 1;
}
static void
pinknoise_mute(GtkWidget *widget)
{
   pinknoise_muted ^= 1;
}
static void
volume_gui(GtkWidget *widget)
{
   volume_pink_value = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON (volume_pink_gui));
}
static void
delay_keep_cb(GtkWidget *widget)
{
   gtk_widget_hide_all (delay_window);
}
static void
about_ok_cb(GtkWidget *widget)
{
   gtk_widget_hide_all (about_me_window);
}
static void
about_me_cb(GtkWidget *widget)
{
   gtk_widget_show_all (about_me_window);
   gtk_window_present (about_me_window);
}

static void
transfer_fxn_cb(GtkWidget *widget)
{
   tf = (tf == 0);
}

static void
transfer_function_toggled_cb(GtkWidget *widget)
{

   gtk_toggle_button_set_active(transfer_function_toggle, !gtk_toggle_button_get_active(transfer_function_toggle));
}


static void
capture_cb(GtkWidget *widget, GtkWidget *box)
{
   int i, k, write_output;
   float avg_avg = 0;
   FILE *file_handle;
   gint tmp_array[1];

   if (buffer[buffer_last_clicked] == 1)
   {
      if (buffer_last_clicked == 5 - 1)
      {
         for (k = 0; k < 8192/2; k++)
         {
            guiYBuf[5 -1][k] = 0.0;
            for (i = 0; i < 5 - 1; i++)
               guiYBuf[5 -1][k] += guiYBuf[i][k];
            guiYBuf[5 -1][k] /= 4.0;
            avg_avg += guiYBuf[5 -1][k] * (1.0 / ((float) 8192/2));

         }


         for (k = 0; k < 8192/2; k++)
         {
            guiYBufAvgHold[k] = 0.0 - guiYBuf[5 -1][k] + (avg_avg * 2);
            guiYBuf[5 -1][k] = avg_gain + guiYBufAvgHold[k];

         }

      }
      else
         for (k = 0; k < 8192/2; k++)
            guiYBuf[buffer_last_clicked][k] = guiY[k];
   }
   write_output = mkdir(file_path1, 0770);
   if ( ((write_output == -1) && ((*__errno_location ()) == 17)) || (write_output == 0) )
      write_output = 1;
   if ( write_output == 1)
   {
      file_handle = fopen(file_path2, "wb");
      if (file_handle == ((void *)0))
      {
         write_output = 0;
         fprintf(stderr, "Could not open file %s, permissions issue?\n", file_path2);
      }
   }
   if (write_output == 1)
   {
      tmp_array[0] = 8192/2;
      fprintf(stderr, "Writing %d elements per buffer to %s\n", tmp_array[0], file_path2);
      fwrite (tmp_array, sizeof(gint), 1, file_handle );
      for (i = 0; i < 5; i++)
         fwrite (guiYBuf[i], sizeof(gfloat), 8192/2, file_handle );
      fclose(file_handle);
   }
}


static void gain_cb( GtkWidget *widget, GtkSpinButton *spin )
{
   int k;
   avg_gain = gtk_spin_button_get_value_as_float (spin);
   for (k = 0; k < 8192/2; k++)
      guiYBuf[5 - 1][k] = avg_gain + guiYBufAvgHold[k];
}

static void
buffer_button_cb(GtkWidget *widget, gpointer p)
{
   GtkWidget *bufferwid;
   GtkWidget *bufferwid_m;
   gint i;
   i = GPOINTER_TO_INT(p);
   bufferwid = buffer_button[i];
   bufferwid_m = buffer_menu[i];
   if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (bufferwid)))
   {
      if (buffer[i] != 1)
      {
         gtk_databox_graph_add ((G_TYPE_CHECK_INSTANCE_CAST ((box), (gtk_databox_get_type ()), GtkDatabox)), graph[i+1]);
         buffer[i] = 1;
         gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(bufferwid_m), TRUE);
      }
   }
   else
   {
      if (buffer[i] == 1)
      {
         gtk_databox_graph_remove ((G_TYPE_CHECK_INSTANCE_CAST ((box), (gtk_databox_get_type ()), GtkDatabox)), graph[i+1]);
         buffer[i] = 0;
         gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(bufferwid_m), FALSE);
      }
   }
   buffer_last_clicked = i;
}

static void
buffer_menu_cb(GtkWidget *widget, gpointer p)
{
   GtkWidget *bufferwid;
   GtkWidget *bufferwid_m;
   gint i;
   i = GPOINTER_TO_INT(p);
   bufferwid = buffer_button[i];
   bufferwid_m = buffer_menu[i];

   if (gtk_check_menu_item_get_active (GTK_CHECK_MENU_ITEM (bufferwid_m)))
   {
      if (buffer[i] != 1)
      {
         gtk_databox_graph_add ((G_TYPE_CHECK_INSTANCE_CAST ((box), (gtk_databox_get_type ()), GtkDatabox)), graph[i+1]);
         buffer[i] = 1;
         gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (bufferwid), TRUE);
      }
   }
   else
   {
      if (buffer[i] == 1)
      {
         gtk_databox_graph_remove ((G_TYPE_CHECK_INSTANCE_CAST ((box), (gtk_databox_get_type ()), GtkDatabox)), graph[i+1]);
         buffer[i] = 0;
         gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (bufferwid), FALSE);
      }
   }
   buffer_last_clicked = i;
}

static void
impulse_hide(GtkWidget *widget, struct FFT_Frame * data)
{

   printf("Delete event\n");
   gtk_widget_hide_all (impulse_window);
}

static void
delay_hide(GtkWidget *widget, struct FFT_Frame * data)
{

   gtk_widget_hide_all (delay_window);
}

static void
cleanup_gui(GtkWidget *widget, struct FFT_Frame * data)
{
   gtk_widget_destroy (GTK_WIDGET(open_dialog));
   gtk_widget_destroy (GTK_WIDGET(save_as_dialog));

   gtk_main_quit();
   printf("GUI is done with cleanup\n");
}

void
open_file(char *fn)
{
   int k;
   FILE *file_handle;
   gint read_plot_pts[1];
      printf("%s is being opened\n", fn );
      file_handle = fopen( fn, "rb");
      if (file_handle != ((void *)0))
      {
         fread (read_plot_pts, sizeof(gint), 1, file_handle );
         if (read_plot_pts[0] == 8192/2)
         {
            for (k = 0; k < 5; k++)
               fread (guiYBuf[k], sizeof(gfloat), 8192/2, file_handle );
            save_name = fn;
         }
         else
            fprintf (stderr, "PLOT_PTS is different from PLOT_PTS last captured size, N has been changed from N=%d * 2 since your last capture.\n", read_plot_pts );
      }
      else
         fprintf (stderr, "Couldn't open file %s for reading\n", save_name);
      fclose(file_handle);
}

static void
open_cb(GtkWidget *widget, char *data)
{

   GtkFileFilter *file_filter= ((void *)0);
   gint result;

   if (open_dialog != ((void *)0))
   {
      gtk_window_present (open_dialog);
      return(0);
   }

   open_dialog = gtk_file_chooser_dialog_new ("Open Capture Buffers From", GTK_WINDOW(bkg_dialog), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, ((void *)0));
   if(save_name)
      gtk_file_chooser_select_filename(GTK_FILE_CHOOSER(open_dialog),save_name);
   else
      gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(open_dialog),home_string);
   file_filter = gtk_file_filter_new ();
   gtk_file_filter_add_pattern (file_filter, "*.brp");
   gtk_file_filter_set_name(file_filter, "BRP-PACU files");
   gtk_file_chooser_set_filter (GTK_FILE_CHOOSER(open_dialog), GTK_FILE_FILTER(file_filter));

   gtk_widget_set_sensitive(save_as, 0);
   gtk_widget_set_sensitive(save_now, 0);
   result = gtk_dialog_run (GTK_DIALOG (open_dialog));
   switch (result)
   {
   case GTK_RESPONSE_ACCEPT:
      open_file(gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(open_dialog)));
      break;
   default:
      break;
   }
   gtk_widget_destroy (open_dialog);
   gtk_widget_set_sensitive(save_as, 1);
   gtk_widget_set_sensitive(save_now, 1);
   open_dialog = ((void *)0);
   return(0);
}

static void
save_file(char* fn)
{
   int k;
   gint tmp_array[1];
   FILE *file_handle;
   printf("%s is being saved\n", fn);




   file_handle = fopen(fn, "wb");
   if (file_handle != ((void *)0))
   {
      tmp_array[0] = 8192/2;
      fwrite (tmp_array, sizeof(gint), 1, file_handle );
      for (k = 0; k < 5; k++)
         fwrite (guiYBuf[k], sizeof(gfloat), 8192/2, file_handle );
      save_name = fn;
      fclose(file_handle);
   }
   else
      fprintf (stderr, "Couldn't open file %s for writing.  Usually this is a permissions issue\n", save_name);

}

static void
save_as_cb(GtkWidget *widget, char *data)
{

   int k;
   gint result;
   GtkFileFilter *file_filter= ((void *)0);

   if (save_as_dialog != ((void *)0))
   {
      gtk_window_present (save_as_dialog);
      return(0);
   }

   save_as_dialog = gtk_file_chooser_dialog_new ("Save Capture Buffers As (*.brp recommended)", GTK_WINDOW(bkg_dialog), GTK_FILE_CHOOSER_ACTION_SAVE, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_SAVE_AS, GTK_RESPONSE_ACCEPT, ((void *)0));

   if(!gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(save_as_dialog),save_name))
      gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(save_as_dialog),home_string);
   gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(save_as_dialog),
       save_name==((void *)0)?"Untitled.brp":strrchr(save_name,'/')+1);

   file_filter = gtk_file_filter_new ();
   gtk_file_filter_add_pattern (file_filter, "*.brp");
   gtk_file_filter_set_name(file_filter, "BRP-PACU files");
   gtk_file_chooser_set_filter (GTK_FILE_CHOOSER(save_as_dialog), GTK_FILE_FILTER(file_filter));

   gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (save_as_dialog), TRUE);

   gtk_widget_set_sensitive(open_menuitem, 0);
   result = gtk_dialog_run (GTK_DIALOG (save_as_dialog));
   switch (result)
   {
   case GTK_RESPONSE_ACCEPT:
      save_file(gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(save_as_dialog)));
      break;
   default:
      break;
   }
   gtk_widget_destroy (save_as_dialog);
   save_as_dialog = ((void *)0);
   gtk_widget_set_sensitive(open_menuitem, 1);
   return(0);
}

static void
save_now_cb(GtkWidget *widget, char *data)
{
   if (save_name == ((void *)0))
   {
      save_as_cb(widget, data);
   }
   else
      save_file(save_name);
}


static void
impulse_cb(GtkWidget *widget, struct FFT_Frame * data)
{
   gtk_widget_show_all(GTK_DIALOG(impulse_window));
   gtk_widget_show_all(GTK_DIALOG(impulse_window));
   data->find_impulse = 1;
   data->find_delay = 1;
}


static void
delay_cb(GtkWidget *widget, struct FFT_Frame * data)
{
   gtk_widget_show_all(GTK_DIALOG(delay_window));
   gtk_window_present (delay_window);

   data->find_delay = 1;
}

static void
resize_default_cb(GtkWidget *widget, GtkWidget *box )
{
   gfloat min_x, min_y, max_x, max_y;
   min_x = 30.0;
   max_x = (gfloat) 44100/2;
   min_y = -100.0;
   max_y = 100.0;
   gtk_databox_set_total_limits ((G_TYPE_CHECK_INSTANCE_CAST ((box), (gtk_databox_get_type ()), GtkDatabox)), min_x, max_x, max_y, min_y);

   gtk_widget_queue_draw(GTK_WIDGET (box));

}

static void
resize_cb(GtkWidget *widget, GtkWidget *box )
{
   gint k;
   gfloat min_x, min_y, max_x, max_y, tempY;
   min_x = 30.0;
   max_x = (gfloat) 44100/2;
   max_y = -100.0;
   min_y = 100.0;
   for (k = min_x * (gfloat)(float) ((float) 44100)/( ((float)8192)/1.0) + 10; k < 8192/2 - 10; k++)
   {
      tempY = guiY[k];
      max_y = (max_y > tempY) ? max_y : tempY;
      min_y = (min_y < tempY) ? min_y : tempY;
   }
   gtk_databox_set_total_limits ((G_TYPE_CHECK_INSTANCE_CAST ((box), (gtk_databox_get_type ()), GtkDatabox)), min_x, max_x, max_y + 10, min_y - 10);

   gtk_widget_queue_draw(GTK_WIDGET (box));

}


static gint
show_motion_notify_cb(GtkWidget *widget, GdkEventMotion *event)
{
   gfloat x;
   gfloat y;
   GtkDatabox *box_coords = (G_TYPE_CHECK_INSTANCE_CAST ((widget), (gtk_databox_get_type ()), GtkDatabox));

   x = gtk_databox_pixel_to_value_x (box_coords, event->x);
   y = gtk_databox_pixel_to_value_y (box_coords, event->y);
   gchar *label;


   label = g_strdup_printf ( "%g Hz", x);
   gtk_label_set_text (GTK_LABEL (gui_label), label);
   g_free((gpointer)label);
   label = g_strdup_printf ( "%g dB", (y) );
   gtk_label_set_text (GTK_LABEL (gui_db_label), label);
   g_free((gpointer)label);
   return FALSE;
}




static gboolean configure_event_measured( GtkWidget *widget,
      GdkEventConfigure *event )
{

   GdkGC *gc = ((void *)0);
   gc = gdk_gc_new(measured_draw->window);

   GdkColor myColor = { 0, 0x8888, 0x8888, 0x8888 };
   gdk_gc_set_rgb_fg_color (gc, &myColor);
   if (measured_pixmap)
      g_object_unref (measured_pixmap);

   measured_pixmap = gdk_pixmap_new (measured_draw->window, widget->allocation.width,
                                     widget->allocation.height, -1);
   gdk_draw_rectangle (measured_pixmap, gc, TRUE, 0, 0, widget->allocation.width,
                       widget->allocation.height);

   myColor.red = 0x3333;
   myColor.green = 0x3333;
   myColor.blue = 0x3333;
   gdk_gc_set_rgb_fg_color (gc, &myColor);

   gdk_draw_rectangle (measured_pixmap, gc, TRUE, 7, 7, 16, 16);
   printf("config\n");
   g_object_unref(gc);
   return TRUE;
}
static gboolean configure_event_reference( GtkWidget *widget,
      GdkEventConfigure *event )
{

   GdkGC *gc = ((void *)0);
   gc = gdk_gc_new(reference_draw->window);

   GdkColor myColor = { 0, 0x8888, 0x8888, 0x8888 };
   gdk_gc_set_rgb_fg_color (gc, &myColor);
   if (reference_pixmap)
      g_object_unref (reference_pixmap);

   reference_pixmap = gdk_pixmap_new (reference_draw->window, widget->allocation.width,
                                      widget->allocation.height, -1);
   gdk_draw_rectangle (reference_pixmap, gc, TRUE, 0, 0, widget->allocation.width,
                       widget->allocation.height);

   myColor.red = 0x3333;
   myColor.green = 0x3333;
   myColor.blue = 0x3333;
   gdk_gc_set_rgb_fg_color (gc, &myColor);

   gdk_draw_rectangle (reference_pixmap, gc, TRUE, 7, 7, 16, 16);
   printf("config\n");
   g_object_unref(gc);
   return TRUE;
}

gboolean
create_gui (struct FFT_Frame * data)
{
   GtkWidget *window = ((void *)0);
   GtkWidget *box_container;
   GtkWidget *box_container_impulse;

   GtkWidget *table;
   GtkWidget *table_impulse;
   GtkWidget *separator;

   GladeXML *xml = ((void *)0);
   GtkDataboxGrid *my_grid;

   FILE * file_handle;
   gint read_plot_pts[1];

   char tmp_string[] = "BRP-PACU vxx.xx.xx ";
   graph = g_new0 (GtkDataboxGraph *, 10);
   graph_impulse = g_new0 (GtkDataboxGraph, 1);
   gint k;
   gint i;
   gfloat min_x, max_x, min_y, max_y;

   min_x = 30.0;
   max_x = (gfloat) 44100/2;
   min_y = -100.0;
   max_y = 100.0;
# 890 "gui.c"
   xml = glade_xml_new ("gui.glade", ((void *)0), ((void *)0));
   if (!xml)
   {
      xml = glade_xml_new (DATADIR"/BRP_PACU/gui.glade", ((void *)0), ((void *)0));
      if (!xml)
      {
         fprintf(stderr, "Couldn't find glade file\n");
         return(FALSE);
      }
   }

   window = glade_xml_get_widget (xml, "window1");
   bkg_dialog = glade_xml_get_widget (xml, "bkg_dialog");
   about_me_window = glade_xml_get_widget (xml, "about_me_window");
   about_ok = glade_xml_get_widget (xml, "about_ok");
   delay_window = glade_xml_get_widget (xml, "delay1");
   impulse_window = glade_xml_get_widget (xml, "impulse_window");
   box_container = glade_xml_get_widget (xml, "vbox1");
   gui_label = glade_xml_get_widget (xml, "label3");
   gui_sb_label = glade_xml_get_widget (xml, "delay_label");
   gui_sb = glade_xml_get_widget (xml, "spinbutton1");
   gui_db_label = glade_xml_get_widget (xml, "label4");
   save_as = glade_xml_get_widget (xml, "save_as");
   save_now = glade_xml_get_widget (xml, "save_now");
   open_menuitem = glade_xml_get_widget (xml, "open");
   box_container_impulse = glade_xml_get_widget (xml, "vbox_impulse");
   measured_draw = glade_xml_get_widget(xml, "Measured_Draw");
   reference_draw = glade_xml_get_widget(xml, "Reference_Draw");
   gui_status_delay_label = glade_xml_get_widget (xml, "delay_status_label");
   volume_pink_gui = glade_xml_get_widget (xml, "volumebutton1");
   pinknoise_button = glade_xml_get_widget (xml, "pinknoise_button");
   transfer_function_toggle = glade_xml_get_widget (xml, "TransferFxn");
   buffer_button[0] = glade_xml_get_widget (xml, "buff0");
   buffer_button[1] = glade_xml_get_widget (xml, "buff1");
   buffer_button[2] = glade_xml_get_widget (xml, "buff2");
   buffer_button[3] = glade_xml_get_widget (xml, "buff3");
   buffer_button[4] = glade_xml_get_widget (xml, "buffAvg");
   buffer_menu[0] = glade_xml_get_widget (xml, "buff0_m");
   buffer_menu[1] = glade_xml_get_widget (xml, "buff1_m");
   buffer_menu[2] = glade_xml_get_widget (xml, "buff2_m");
   buffer_menu[3] = glade_xml_get_widget (xml, "buff3_m");
   buffer_menu[4] = glade_xml_get_widget (xml, "buffAvg_m");
   g_signal_connect (G_OBJECT (glade_xml_get_widget (xml, "pinknoise_button")), "clicked", G_CALLBACK (pinknoise_mute), ((void *)0));

   g_signal_connect (G_OBJECT (glade_xml_get_widget (xml, "volumebutton1")), "value-changed", G_CALLBACK (volume_gui), ((void *)0));


   g_signal_connect (G_OBJECT (glade_xml_get_widget (xml, "quit_ap")), "activate", G_CALLBACK (cleanup_gui), ((void *)0));
   g_signal_connect (G_OBJECT (glade_xml_get_widget (xml, "save_as")), "activate", G_CALLBACK (save_as_cb), ((void *)0));
   g_signal_connect (G_OBJECT (glade_xml_get_widget (xml, "save_now")), "activate", G_CALLBACK (save_now_cb), ((void *)0));
   g_signal_connect (G_OBJECT (glade_xml_get_widget (xml, "open")), "activate", G_CALLBACK (open_cb), ((void *)0));
   g_signal_connect (G_OBJECT (glade_xml_get_widget (xml, "about_me")), "activate", G_CALLBACK (about_me_cb), ((void *)0));
   g_signal_connect (G_OBJECT (about_me_window), "delete_event", G_CALLBACK (about_ok_cb), ((void *)0));
   g_signal_connect (G_OBJECT (glade_xml_get_widget (xml, "about_ok")), "clicked", G_CALLBACK (about_ok_cb), ((void *)0));
   g_signal_connect (G_OBJECT (transfer_function_toggle), "toggled", G_CALLBACK (transfer_fxn_cb), ((void *)0));
   g_signal_connect (G_OBJECT (glade_xml_get_widget (xml, "transfer_fxn")), "activate", G_CALLBACK (transfer_function_toggled_cb), ((void *)0));
   g_signal_connect (GTK_BUTTON (glade_xml_get_widget (xml, "find_delay")), "clicked", G_CALLBACK (delay_cb), data);
   g_signal_connect (G_OBJECT (glade_xml_get_widget (xml, "find_delay_m")), "activate", G_CALLBACK (delay_cb), data);
   g_signal_connect (GTK_OBJECT (window), "destroy", G_CALLBACK (cleanup_gui), ((void *)0));
   g_signal_connect (GTK_OBJECT (window), "delete_event", G_CALLBACK (cleanup_gui), ((void *)0));
   g_signal_connect (GTK_OBJECT (delay_window), "delete_event", G_CALLBACK (delay_hide), ((void *)0));
   g_signal_connect (G_OBJECT (glade_xml_get_widget(xml, "delay_keep_button")), "clicked", G_CALLBACK (delay_keep_cb), ((void *)0));
   g_signal_connect (G_OBJECT (glade_xml_get_widget (xml, "impulse_response")), "activate", G_CALLBACK (impulse_cb), data);
   g_signal_connect (GTK_OBJECT (impulse_window), "delete_event", G_CALLBACK (impulse_hide), ((void *)0));

   g_signal_connect (G_OBJECT (glade_xml_get_widget (xml, "delay_custom_button")), "clicked", G_CALLBACK (delay_custom_cb), ((void *)0));

   gui_frequency = 0;
   gtk_widget_set_size_request (window, 1200, 650);

   sprintf(tmp_string, "BRP-PACU v%s", "2.0.7");
   gtk_window_set_title (GTK_WINDOW (window), tmp_string);
   gtk_container_set_border_width (GTK_CONTAINER (window), 0);


   gtk_widget_set_size_request (impulse_window, 900, 500);

   sprintf(tmp_string, "BRP-PACU Impulse");
   gtk_window_set_title (GTK_WINDOW (impulse_window), tmp_string);
   gtk_container_set_border_width (GTK_CONTAINER (impulse_window), 0);


   separator = gtk_hseparator_new ();
   gtk_box_pack_start (GTK_BOX (box_container), separator, FALSE, FALSE, 0);
   gtk_label_set_text (GTK_LABEL (gui_label), "0");

   gui_idle = 0;
   gui_frequency = 3. * G_PI / 2.;
   gui_counter = 0;


   gtk_databox_create_box_with_scrollbars_and_rulers (&box, &table,
         TRUE, TRUE,
         TRUE, TRUE);

   gtk_databox_create_box_with_scrollbars_and_rulers (&impulse_box, &table_impulse,
         TRUE, TRUE,
         TRUE, TRUE);

   gtk_databox_set_total_limits ((G_TYPE_CHECK_INSTANCE_CAST ((box), (gtk_databox_get_type ()), GtkDatabox)), min_x, max_x, max_y,
                                 min_y);

   min_x = 30.0;
   max_x = (gfloat) 44100/2;
   min_y = -100.0;
   max_y = 100.0;
   gtk_databox_set_total_limits ((G_TYPE_CHECK_INSTANCE_CAST ((impulse_box), (gtk_databox_get_type ()), GtkDatabox)), min_x, max_x, max_y,
                                 min_y);


   gtk_databox_set_scale_type_x ((G_TYPE_CHECK_INSTANCE_CAST ((box), (gtk_databox_get_type ()), GtkDatabox)), GTK_DATABOX_SCALE_LOG);
   gtk_databox_set_scale_type_y ((G_TYPE_CHECK_INSTANCE_CAST ((box), (gtk_databox_get_type ()), GtkDatabox)), GTK_DATABOX_SCALE_LINEAR);




   g_signal_connect (G_OBJECT (box), "motion_notify_event", G_CALLBACK (show_motion_notify_cb), ((void *)0));


   gtk_box_pack_start (GTK_BOX (box_container), table, TRUE, TRUE, 0);
   gtk_box_pack_start (GTK_BOX (box_container_impulse), table_impulse, TRUE, TRUE, 0);

   background_color.red = 8192;
   background_color.green = 8192;
   background_color.blue = 8192;

   gtk_widget_modify_bg (box, GTK_STATE_NORMAL, &background_color);

   guiX = g_new0 (gfloat, 8192/2);
   guiY = g_new0 (gfloat, 8192/2);
   gui_impulse_Y = g_new0 (gfloat, 8192);
   gui_impulse_X = g_new0 (gfloat, 8192);

   for (i = 0; i < 8192/2; i++)
   {
      gui_impulse_Y[i] = .01;
      gui_impulse_X[i] = ((gfloat)i) / ((gfloat)44100);
   }
   for (i = 0; i < 8192/2; i++)
   {
      guiX[i] = ((gfloat)i) * (gfloat)(float) ((float) 44100)/( ((float)8192)/1.0);
      for (k = 0; k < 32; k++)
         avgY[i][k] = .01;
      guiY[i] = .01;
      for (k = 0; k < 5; k++)
         guiYBuf[k][i] = 0.0;
      guiYBufAvgHold[i] = 0.0;

   }
   trace_transfer_color.red = 16384;
   trace_transfer_color.green = 65535;
   trace_transfer_color.blue = 16384;

   graph[0] = gtk_databox_lines_new (8192/2, guiX, guiY,
                                     &trace_transfer_color, 1);
   gtk_databox_graph_add ((G_TYPE_CHECK_INSTANCE_CAST ((box), (gtk_databox_get_type ()), GtkDatabox)), graph[0]);
   for (i = 0; i < 5; i++)
      graph[i+1] = gtk_databox_lines_new (8192/2, guiX, guiYBuf[i],
                                     &line_color[i], 1);
   grid_color.red = 65535;
   grid_color.green = 65535;
   grid_color.blue = 16384;
   my_grid = gtk_databox_grid_new (19, 21.5, &grid_color, 1);
   gtk_databox_graph_add ((G_TYPE_CHECK_INSTANCE_CAST ((box), (gtk_databox_get_type ()), GtkDatabox)), my_grid);

   trace_impulse_color.red = 16384;
   trace_impulse_color.green = 16384;
   trace_impulse_color.blue = 65535;
   graph_impulse = gtk_databox_lines_new (8192/2, gui_impulse_X, gui_impulse_Y,
                                          &trace_impulse_color, 1);
   gtk_databox_graph_add ((G_TYPE_CHECK_INSTANCE_CAST ((impulse_box), (gtk_databox_get_type ()), GtkDatabox)), graph_impulse);

   buffer_button[0] = glade_xml_get_widget (xml, "buff1");
   buffer_button[1] = glade_xml_get_widget (xml, "buff2");
   buffer_button[2] = glade_xml_get_widget (xml, "buff3");
   buffer_button[3] = glade_xml_get_widget (xml, "buff4");
   buffer_button[4] = glade_xml_get_widget (xml, "buffAvg");
   buffer_menu[0] = glade_xml_get_widget (xml, "buffer_1");
   buffer_menu[1] = glade_xml_get_widget (xml, "buffer_2");
   buffer_menu[2] = glade_xml_get_widget (xml, "buffer_3");
   buffer_menu[3] = glade_xml_get_widget (xml, "buffer_4");
   buffer_menu[4] = glade_xml_get_widget (xml, "bufferAvg");

   g_signal_connect (G_OBJECT (glade_xml_get_widget (xml, "auto_resize")), "clicked", G_CALLBACK (resize_cb), (gpointer) box);
   g_signal_connect (G_OBJECT (glade_xml_get_widget (xml, "resize_default")), "clicked", G_CALLBACK (resize_default_cb), (gpointer) box);
   g_signal_connect (G_OBJECT (glade_xml_get_widget (xml, "auto_resize_m")), "activate", G_CALLBACK (resize_cb), (gpointer) box);
   g_signal_connect (G_OBJECT (glade_xml_get_widget (xml, "resize_default_m")), "activate", G_CALLBACK (resize_default_cb), (gpointer) box);
   for (i = 0; i < 5; i++)
   {
      g_signal_connect (G_OBJECT (buffer_button[i]), "clicked", G_CALLBACK (buffer_button_cb), GINT_TO_POINTER((gint) i));
      g_signal_connect (G_OBJECT (buffer_menu[i]), "activate", G_CALLBACK (buffer_menu_cb), GINT_TO_POINTER((gint) i));
   }
   g_signal_connect (G_OBJECT (glade_xml_get_widget (xml, "capt")), "clicked", G_CALLBACK (capture_cb), (gpointer) box);
   g_signal_connect (G_OBJECT (glade_xml_get_widget (xml, "capt_m")), "activate", G_CALLBACK (capture_cb), (gpointer) box);
   g_signal_connect (G_OBJECT (glade_xml_get_widget (xml, "gain1")), "value-changed", G_CALLBACK (gain_cb), (G_OBJECT (glade_xml_get_widget (xml, "gain1")) ));



   g_signal_connect (G_OBJECT (reference_draw), "configure_event",
                     G_CALLBACK (configure_event_reference), ((void *)0));
   g_signal_connect (G_OBJECT (measured_draw), "configure_event",
                     G_CALLBACK (configure_event_measured), ((void *)0));

   volume_pink_value = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON (volume_pink_gui));
   gtk_widget_show_all (window);



   home_string = getenv ("HOME");
   file_path1 = malloc(sizeof(home_string) + 30);
   file_path2 = malloc(sizeof(home_string) + 50);




   sprintf(file_path1, "%s/.BRP_PACU", home_string);

   sprintf(file_path2, "%s/buff_store.brp", file_path1 );
   if ((file_handle = fopen(file_path2, "rb")) <= 0)
      fprintf(stderr, "\n\nNo BRP_PACU initialization file yet\nAre you running BRP_PACU for the 1st time?\nIf so, a file will be created for you on your next capture\n\n");
   else
   {
      fread (read_plot_pts, sizeof(gint), 1, file_handle );
      if (read_plot_pts[0] == 8192/2)
      {
         for (i = 0; i < 5; i++)
            fread (guiYBuf[i], sizeof(gfloat), 8192/2, file_handle );
      }
      else
         fprintf (stderr, "PLOT_PTS is different from PLOT_PTS saved size, this is because you have changed N since your last capture.  Please change it back to %d * 2. Otherwise making a new capture should overwrite the old file\n", read_plot_pts );
      fclose(file_handle);
   }
# 1161 "gui.c"
   g_object_unref (G_OBJECT(xml));
   return(TRUE);

}
