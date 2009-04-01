#!/bin/bash

## cd  to PROJECT directory
git init
git config user.name "Brian R Phelps"
git config user.email "electronjunkie@users.sourceforge.net"

git add .
git commit

git remote add origin ssh://electronjunkie@brp-pacu.git.sourceforge.net/gitroot/brp-pacu
git config branch.master.remote origin
git config branch.master.merge refs/heads/master

git push origin master

## Note: The use of "origin master" prevents Git from complaining that the remote server has no branches in common with your local repository (which is true at the start when the remote repository is completely empty), and "master" is the default branch in Git.

## After the first push, you will be able to use the simpler "git push" to push the master branch to our "origin" server. 

## ----------------------------------------------------------------------

## Cloning can be done by
# git clone git://brp-pacu.git.sourceforge.net/gitroot/brp-pacu

# If you have a sf account and git write access then this should work:
# git config user.name "YOUR NAME"
# git config user.email "SF_USERNAME@users.sourceforge.net"
# git remote rm origin
# git remote add origin ssh://SF_USERNAME@brp-pacu.git.sourceforge.net/gitroot/brp-pacu

## Now updates can be done by:

# git status ## to show whats changed
# git add <files_listed_in_status>
# git commit
# git push
