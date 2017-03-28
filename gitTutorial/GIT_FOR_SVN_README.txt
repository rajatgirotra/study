Come here if you already know about git. If you dont please read README.txt first

We assume you have a subversion repository at: svn://192.168.150.157/back-office/components/product_master/server

Step 1:
-----

Creating a local repository from the remote svn repository. This can be done in two ways.

1) git clone -s --username=rgirotra svn://192.168.150.157/back-office/components/product_master/server .
   This -s option tells git that the subversion repository has a standard layout. i.e trunk/, branches/ and tags/. If you subversion layout
   is not standard using the -T<trunk_subdir> -b<branches_subdir> -t<tags_subdir> options. this command can be very slow because it will fetch
   the entire subversion history. So you can use the -r<arg> (--revision<arg>) option to specify, lets say the last 100 commits.

2) the second way is to use 
   "git init -s --username=rgirotra svn://192.168.150.157/back-office/components/product_master/server ." followed by "git svn fetch".
   Here also, you can use the -r<arg> option with "git init" as with "git clone". So you can say that git clone does both init and fetch.

Step 2:
------

Once you have initialised your local repository, you have the complete commit history and all branches, tags etc. You can view thes using
"git branch -a", just like you do in git.

Step 3:
------

This step is optional, although good to do. We call it repacking. I dont know exactly, but git does some form of repacking data into
convenient packs to reduce the load on mirror systems, backup engines and disk storage. For this, please do:

"git repack -d"

Step 4
------

It is never advised to make changes on the HEAD. Always create a branch and work on that branch and then later merge your changes into HEAD.
Creating a branch is straight forward just like in git.

    "git checkout -b new_feature"

Step 5
------
Once you have made all changes. use "git add" and "git commit" to commit on your branch. and then later merge it with master branch.
   "git checkout master"
   "git merge --squash new_feature"

You can also make sure you keep your branch up to date with the latest changes in remote svn repository. For that you can do:
   "git checkout master"
   "git svn rebase"
   "git merge --squash --no-commit new_feature"
   "git commit -m "Message""

What is --squash?? Sometimes, you may make a lot of commits in your feature branch that you want represented as one commit in 
the main branch. This is exactly what squash does.


Step 6
------

Once your changes are in your master branch, you are ready to push them to svn. But be sure, that your repository is up to date.
For this use the "git svn rebase" command. This will rebase the master branch to the subversion trunk. Next, you need to commit your
changes to svn.

Step 7:
------

git svn dcommit --dry-run ## Check that it will commit to proper svn branch.






While working on Cygwin I did, 
git svn init --stdlayout --username=rgirotra svn://192.168.150.157/back-office/libraries/utility/business_model business_model-git,
but I ran into problems, which I fixed using this:

Git svn – Can’t locate Term/ReadKey.pm in @INC
perl -MCPAN -e shell
install Term::ReadKey
exit
perl -MCPAN -e shellinstall Term::ReadKeyexit

