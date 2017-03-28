prompt> git --version

Git is very different from other version control systems in the sense that it is distributed. Normally, all VCS are centralised.
You have one centralised repository which everyone uses to checkout and commit changes to.

But in Git, each developer has at least two repositories. You have a private repository to which you commit your changes very frequently.
There is a public repository to which you push your changes when you want to share them with other members on the team.

There are ideally two ways in which you can use this distributed GIT model. One is that every one has a private repository to which they can commit their
changes. Once they are done, they can commit the changes to one centralised public repository. If someone on the team has already shared their changes 
to the same file that your are sharing, you'll get an error. You will need to get an upto date version of the file and merge your changes with it before
you share (push) them again.

The other model is a totally distributed one in which every developer has its own public repository. In this case, everone has to pull changes from
everyone else's public repository to get an upto date version of code. When you want to share your changes you push them to your own public repository 
and people can pull from there.

Commits in GIT
--------------

Since there is no centralised repository, there is no notion of assigning revision numbers. Each commit is actually assigned a COMMIT ID which is
SHA-1 hash based. The hash is depends on the code, what came before it, who made the commit, when the commit was made and other metadata.

Configuration
-------------

git requires some configuration when you first start using it. Configuration can be global (valid for all repositories being used my a user), or local to
a repository. Global configs are stored in the ~/.gitconfig file. Local configurations are stored in the /path/to/repository/.git/config file. You
can make changes to these files directly but I recommend you use the "git config" command.

First you must tell your name and email address to git as that is used to make up hash for the commit id.

prompt> git config --global user.name "Rajat Girotra"
prompt> git config --global user.email "r.girotra@iontrading.com"
prompt> git config --global color.ui auto
prompt> git config --global alias.st status   # make `git st` work
prompt> git config -l                         # list all configuration options

For local configs

Set the Git user for a specific repository.
prompt> cd /path/to/repository
prompt> git config user.name "Rajat Girotra"
prompt> git config user.email "r.girotra@iontrading.com"



Git launches an editor whenever you need to create a commit message, edit patches, and do a few other tasks.
Git doesn’t require you to set the core.editor value, though. It tries to figure out what editor to use by checking the following values, in order:
1) GIT_EDITOR environment variable;
2) core.editor configuration value;
3) VISUAL environment variable;
4) EDITOR environment variable;
5) and, finally, plain vi.

The value is the command-line script to launch your editor. In Windows, this is a bit tricky, but there’s an excellent thread on Stack Overflow
that can help you get started.

Creating a GIT repository
-------------------------

You know already that there are at least two repositories in GIT, public and private. We are talking about creating a pivate repository here.
We use the "git init" command to create an empty repository. "git init" actually creates a .git folder and initialises an empty repository in your
current working directory. If you already have code you want to add to your repository, you can go to your code directory and create a repository there
using "git init" followed by "git add" and "git commit". Eg:

prompt> mkdir /work/widgets
prompt> cd /work/widgets
prompt> git init
Initialized empty Git repository in /work/widgets/.git/

Create a repository in an existing directory, and add all files from that directory.
prompt> cd /work/existing-widget
prompt> git init
Initialized empty Git repository in /work/existing-widget/.git/

prompt> git add .
prompt> git commit -m "initial commit"

[master (root-commit) 6e477fa] initial commit
101 files changed, 4083 insertions(+), 0 deletions(-)
create mode 100644 AUTHORS
... and 100 more files ...

GIT CLONE COMMAND
-----------------

This command is used to clone an existing remote repository with which you will talk to pull and push data. So you can now
create a local repository in two ways

1] Use git clone command. By default, the repository you clone from will be given a name as "origin". Run
    "git remote -v" to confirm this. Also cloning will create a local master branch which will be a tracking branch to track changes
	 to the remote master branch; given a remote master branch exists.
2] Use "git init" to initialise an empty local repository, followed by "git remote add" to add a remote repository
and followed by "git fetch" to pull changes.

You can use the --depth parameter with "git clone" to only fetch some commits as fetching all branches/tags/commits can take 
some time initially.



GIT STATUS
-----------
This is a beautiful command that tells you the status of files in your repository. The output has 3 sections
1) Files that are not tracked by git presently and about which it knows nothing about. They appear in red at the end of the section
2) Files that contain local changes (ie modified locally) but have not been staged for commit. These also appear in red.
3) Files with changes and which are staged for commit. These appear in red.

GIT STAGING
-----------
For staging files for commit you use the "git add" command.

svn add will move a file to the staging area. There are multiple options that "git add" can take

1) -A or -all : This will add files (which are changes and which git is not tracking at this moment) to the staging area,
                except those which are in the excludes list.
2) -u : This will only add files to the staging area which are changed.
3) -p : This takes you into patch mode and you can selectively choose which portions of the file you want to stage for commits.
4) -e : Similar to above, but this opens an editor and shows you the diffs and you can choose which ones you want to stage.


GIT COMMIT
----------

Use "git commit -m "Log Message" to commit a file. You can also use the -a switch to commit all files (which are changed and tracked,
and which are new and untracked) with using "git add" earlier.


GIT IGNORE
----------

Often there are files/directories that you want to ignore in your repository. You dont want these to show up in your "git status"
command and destract you. Also you dont want to commit these files either. You can create a file ".gitignore" and place the filename/directoryname
which you want git to ignore. the rules will apply to all files and sub-directories in which the .gitignore file is placed. So good to put it in the 
top level directory of your repository. It is like any other file that you can track in the repository.

In case you dont want to put .gitignore itself in your repository, you have two options.

1) You put all these details in the .git/info/exclude file inside your .git folder.
2) You can also create a global ignore file which will be valid for all repositories used by this user.
   prompt>  git config --global core.excludesfile ~/.gitignore
   
GIT UNDOING
-----------

Suppose you have modified some files and added some new files which you have staged. But now you dont want to commit them but unstage them.
You can use the following commands:

prompt>  git reset HEAD -- pom.xml  : This means that you want to remove the modified file pom.xml from the staging area.
         the "--" means that you are done passing options to git and what follows is the name of the file/path.
prompt> git rm --cached abc.txt  : This means that you want to remove the new added file abc.txt from the staging area.
prompt> git rm --cached \*.o  : Remove all object files accidently added to index (ie staging area). Note the "\" is required as GIT performs it owns filename expansion.
Very Simple:

If you make a local change to file "abc" but havent staged it yet, user "git checkout abc" to discard it.
If you have staged it, use "git reset HEAD abc" to unstage it, followed by "git checkout"
If you have commited it already, user "git revert".

GIT MOVING
----------

You can also use "git mv" command to move files and directories around. See you dont need "git add" in this case.

prompt> git mv README.md README.rst
prompt> git commit -m "Changed README from Markdown to ReSTructured text"

prompt> git mv README.rst docs/
prompt> git commit -m "Moved README into docs/ directory"

GIT REMOVE
----------
To stop git from tracking files, you can remove them using git rm. To remove a directory and all files under it, use -r option. (recursive)
Use "git commit" after git remove.

prompt>  git rm -- "xyz.txt"
prompt> git commit -m "Removing xyz.txt"


"git rm" actually stages the file for deletion. If you want to prevent it from being deleted, use 
1) git reset HEAD -- <filename> followed by
2) git checkout -- /path/to/file

Also if you try to remove a new file which has local modifications, git will warn you about it.



BRANCHES AND TAGS
-----------------

In GIT, each Branch is actually a file in the repository which contains the latest commit that you have made to that branch.
So you can say that branches in Git are pointers to a specific commit in your repository’s history. Since each commit
knows about its parent (or parents), Git can reconstruct what’s in a branch by looking at the latest commit in that branch
and walking the history backward to find all the ancestors. This simplified approach to branches makes them quick to create,
rename, merge, and even delete

You can use tags to mark milestones in your project, such as releases. Tags are similar to branches, except they are read-only.
Once you create a tag, you can’t change it.

Branches and tags are not shared by default. Like commits, you’re given the ability to decide which branches and tags to share with
other developers and when.

Merging Branches
---------------

There are three ways in which branches can be merged.

1) Fast-Forward Merge - When the branch which is being merged in is merged into a branch from which it was created and there
   has been no commit on the original branch since this new branch was created. this is the simplest type. GIT has to do nothing
   here except just fast-forwarding the branch pointer to a new location.
   
2) Recursive merge - Used when both branches have commits that are not on the other branch.

3) The third way is rebasing. I'll come to it later.


Creating Branches
-----------------

You create a branch using "git branch <branchName>" giving the branchName as the parameter. This uses your current location
in the repository as the location to create the branch from.

You can also create branches starting at points in the history of the repository by provding an optional second argument which
is the commitId, or brancg name or tag name to create a branch at that point.

Once you create a branch you also need to switch to that branch. You do this using "git checkout" command.
Another good way is to use "git checkout -b <branchName>" which does both : branch creation and checking out.

Create a new branch from current place in the repository.
prompt> git branch <new branch name>
... example ...
prompt> git branch new

Create a new branch from another branch, tag, or commit.
prompt> git branch <new branch name> <starting point>
... example ...
prompt> git branch newer 99a0de8

Check out a different branch, tag, and so on.
prompt> git checkout <branch>
... example ...
prompt> git checkout newer
Switched to branch 'newer'

Create a branch and check it out at the same time.
prompt> git checkout -b <new branch> [<starting point>]
... example ...
prompt> git checkout -b newest 64648c9
Switched to branch 'newest'

Create a branch with or without tracking.
Using a remote branch as your <starting point implies that --track is on.
Use --no-track to turn it off.
prompt> git branch --track <new branch> [<starting point>]
prompt> git branch --no-track <new branch> [<starting point>]
prompt> git checkout --track <starting point> //Same as above but a shortcut. Local branch name will be same as remote branch name

Viewing Branches
----------------

You can view the branches using

"git branch" -- will display on your local repository branches. Use "git branch -a" to view all branches (local and remote) or
"git branch -r" to view remote branches.

The current branch will be displayed with an asterik and will be in green color. The remote branches will be in red color.
You can also check which branches have been merged into your current branch using

"git branch --merged" or check which branches have not been merged using
"git branch --no-merged"

View all branches that contain a particular commit.
prompt> git branch --contains <commit id>



Merging Branches
----------------

You use the "git merge" command to merge branches. For example: lets say you have created a branch new and you want to merge it
in the main line "master" branch. Then you say:

prompt> git checkout master (You must be in the master branch)
prompt> git merge --log new

This will merge and commit every changed file in new back to master given that there are no collisions. If you dont want
to commit, use the --no-commit option. You can also merge all changes in a single merge commit. This helps you to easily
remove a feature later on using just a single reverse commit. For this, specify the --no-ff no fast forward) option. 

prompt> git merge -m "My Single Merge Commit" --no-ff new


Rebasing Branches
-----------------

This is slightly complex to understand but is very useful command. There is no counterpart of this command in SVN, CVS etc
Basically it takes a series of commits and then replays those commits on top of another commit. It takes a parameter which
can be a branch, a tag, or a commit id on top of which you will do the rebasing. For example, let say you have created a
branch "new" and made some changes on it. Meanwhile, someone also made some changes in the master branch. So instead 
of merging them, you can replay all the changes done in the master branch since the new branch was created on top of the 
new branch. Make sure you give this command when you are in the master branch.

So you are actually changing the history of commits. Since you are rebasing on top of another commits all the commit id's on 
the master branch will change. But this has a neat side-effect of giving you a clean linear history instead of a merged view
which can be complex to understand. Just like with merge, conflicts can also arise in rebasing but there are always ways to 
get over those. REMEMBER THAT GIT REBASE REQUIRES A CLEAN WORKING COPY WITHOUT ANY LOCAL MODIFICATIONS.

There’s a simple rule of thumb with git rebase: use it as much as you want on local commits. Once you’ve shared changes with
another developer, the headache is generally not worth the trouble.

prompt> git branch
* master
  new
prompt> git rebase new  (Using new as the base, replay all changes made to master branch on top of latest commit in new).
Matlab... take out all commits from master and store them separately.. then apply them one by one on top of new...
When all commits from master are applied on top of new, the master branch will be ahead of new.. and

It works by going to the common ancestor of the two branches (the one you’re on
and the one you’re rebasing onto), getting the diff introduced by each commit of the branch you’re on (in this case master),
saving those diffs to temporary files, resetting the current branch to the same commit as the branch you are rebasing onto,
and finally applying each change in turn.


prompt> git checkout new
prompt> git merge master will just be a simple fast forward merge..
i.e git rebase new will bring all changes in branch new in master.

Which you normally dont want to do.. instead only in the end when you want to merge everything from your feature branch back to master
prompt> git checkout new
prompt> git rebase master // this is what you should do on a daily basis on your feature branch to bring all changes from the world into
                              your branch.
							  
prompt> git rebase master new //same as above just a short cut of the two above commands.



prompt> git rebase --continue (continue rebasing after manually fixing a conflict)
prompt> git rebase --skip (Skip a conflict for now)
prompt> git rebase --abort (Abort)
prompt> git reset ORIG_HEAD (Go back to the pre-rebasing state).


Deleting Branches
---------------

prompt> git branch -d <branchName>

In git a branch is just a pointer to a single commit. You can just tag your release and then delete that branch. In future
if you need it again you can always recreate it using the tag. Git warns you of you delete a branch which hasn't been merged.
Use the -D option to delete unmerged branches.


Tagging
-------
A tag is just a pointer to a commit. Use "git tag" to create tags

prompt> git tag (List all the available tags)
prompt> git tag v1.0 (Tag the latest commit as v1.0).


REMOTE REPOSITORIES
-------------------

Let us now see how to deal with remote repositories.
1] Remote repositories are often just called remotes.
2] You can do two things with remote repositories : fetching code or pushing commits
3] Pulling data from code is same as feteching but additionally it also merges your changes with your local ones.
4] Git treats remote repositories just like branches. So on your system, you'll have a set of remote branches along
with your local branches.
5] You cannot commit any change into remote branch. The only is to push data into a remote repository.
6] Remote branches are references to the state of branches on your remote repositories.

For now, we'll assume that we already have remote repositories (one or more) setup. Later on I'll show you how to setup
remote repositories.


Adding & Removing remotes
-------------------------

Let see how to add remotes.

prompt> git remote add <repository-name> <repository-url>

repositoryURL could be a path to another directory, or a path over the network for which Git can use the git protocol (with
or without ssh) or over HTTP/HTTPS. By default the repository-name is known as "origin". 

prompt> git remote rm <repositoryName>

Feteching
---------

Use "git fetch" to fetch branches from your remote. by default git will always fetch from the origin repository if you dont
provide a remote.

prompt> git fetch (By default, fetch all branches from origin).
prompt> git fetch tswicegood (Fetch all branches from tswicegood).
prompt> git fetch tswicegood master:/remotes/tswicegood/master (Fetch the master branch in tswicegood remote repository into
                                    /remotes/tswicegood/master in your local repository).
prompt> git fetch --multiple remote1 remote2 remote3  (Fetch all branches from multiple repositories)
prompt> git fetch -all (Fetch all branches from all remotes).


Pulling
-------

"git pull" does a "git fetch" and also merges the changes with your local branch.

prompt> git pull [remote [branch-Name] ] 
    eg: git pull tswicegood master

prompt> git pull remote <remoteBranchName>:<localBranchName>
    eg: git pull origin development:team-dev
    
prompt> git pull --rebase [remote [branchName]]
   eg: git pull --rebase origin master   (Do a rebase instead of pulling)


Pushing i.e checking into remote repository
-------------------------------------------
Done using "git push". By default "git push" will push your local branch changes to the same branch in the origin repository.

prompt> git push   (used to push the local tracking branch changes into the origin remote repository).

prompt> git push <remote> <branchName>
    eg: git push origin master
    eg: git push tswicegood development
    

Tracking branches
-----------------

Git sets up tracking branches for you whenever you create a local branch from a remote branch. Adding a repository after
you start working locally, though, doesn’t give Git a chance to do that setup. You can add this by removing the local branch
and re-creating it from the remote branch.

prompt> git checkout origin/master
prompt> git branch -d master
Deleted branch master (was d7c8880).
prompt> git checkout -b master
Switched to a new branch 'master'

Tracking branches are local branches that have a direct relationship to a remote branch. If you’re on a tracking branch and
type git push, Git automatically knows which server and branch to push to. Also, running git pull while on one of these
branches fetches all the remote references and then automatically merges in the corresponding remote branch.

When you clone a repository, it generally automatically creates a master branch that tracks origin/master. That’s why git push
and git pull work out of the box with no other arguments. 


Bare Repositories
-----------------

Normally a git repository has both metadata (the .git/ repository) and a working tree. But for remote repositories from which
data is to be pulled and pushed, we create them as bare repositories. i.e without a working tree.

A bare repository works just like a normal repository, except it doesn’t have a copy of the working tree. All of the files that
are present in the .git/ of your normal repository are present in the directory where your bare repository lives.

By convention, bare repositories should end in .git. For example, call your bare repository widget.git if its name is widget.
To share your repository, place it somewhere that other people can access it. This could be a network file system, on a
directory with proper read permissions on a remote server, or even on an HTTP server.You can also make it accessible via the
git daemon so it is accessible via the git protocol.

There are many 3rd party git hosting websites like GitHub, Gitorious, Gitosis etc.

Setting up a remote repository:

prompt> ssh git@example.com
prompt> mkdir my_project.git
prompt> cd my_project.git
prompt> git init --bare
prompt> git-update-server-info # If planning to serve via HTTP
prompt> exit

On local machine:

prompt> cd my_project
prompt> git init
prompt> git add *
prompt> git commit -m "My initial commit message"
prompt> git remote add origin git@example.com:my_project.git
prompt> git push -u origin master

Conflicts
----------
/**
 * The main Margin Gateway component class.
<<<<<<< HEAD
 * @version $Id: MarginGateway.java 599 2012-07-30 06:37:24Z garora $    //These are your local changes.
=======
 * @version $Id: MarginGateway.java 599 2012-07-30 06:37:24Z rgirotra $  //These are the changes on the branch that you are merging in.
>>>>>>> eda241a51f45aa45c46accab5929bed25bddf2ba

You can find conflicts within a file by looking for <<<<<<<—seven lesser than signs—with a commit such as HEAD. The original code—the code
inside the branch you’re merging into—is located between the 7 < and ========. The new code is between that marker and >>>>>>>, followed by
the name of branch (or commit ID, tag, and so on) you were merging in.

Once you’ve resolved the conflict, call git add to stage the new changes and then git commit to commit it. You can also abort a conflict
at any time before you commit the changes by resetting your working tree to ORIG_HEAD

Apart from using git merge, you can also use "git mergetool" command. This command provides a list of available GUI merging tools it supports.
like Beyond Compare, WinMerge, gvimdiff etc. These executables must be in your path. Also git mergetool will automatically stage the commits for 
you, so you dont have to use "git add" command and only use "git commit" command. You can also set the default merge tool like this.

prompt> git config --global merge.tool "gvimdiff"

Hiding/Stashing your changes
----------------------------

Some git operations require that you a have a clean working copy without any modifications. In such cases, you can temporarily hide your changes
using the "git stash" command. You can think of stashing as commiting your local changes and then moving back one commit. When stashing multiple times,
you actually create a stack of your stashes, where the latest stash is call stash@0, the one before that is called stash@1 and so on...

Commands:
   prompt> git stash save [message]   //to create a new stash
   prompt> git stash apply   //to apply the top most stash (stash@0) to your branch).
   prompt> git stash pop     //same as above but it also removes the stash from the stack of stashes. This one is used more often
   prompt> git stash drop <stashName> //to drop an individual stash
   prompt> git stash clear //to drop all stashes
   prompt> git stash list //list all stashes
   prompt> git stash branch [<stash name>] //to create a branch from a stash. Used in cases when "git stash apply/pop" does not apply cleanly.
   prompt> git stash show  //to view the files changes in this stash.
   

Cherry-pick
-----------

You sometimes need to grab one commit from another branch and merge it into your local branch, such as a bug fix that needs to be backported.
You can grab commits one at a time using git cherry-pick. Cherry-picking a commit from another takes that single commit and commits it to your
local branch. It’s pretty straightforward and appears extremely useful in a lot of situations. Cherry-picked commits have different commit IDs
than the original commit they came from because their parent changed—remember that a commit ID is based partially on where it exists in the history,
and changing the parent changes the commit ID. A good rule of thumb is to cherry-pick commits only when a merge is not an option.

You must specify the commit that you want to cherry-pick.You can do this with either a commit ID, a branch name, a tag, or some relative reference to
any of these. Keep in mind that using a branch name or tag means that the latest commit that those reference is cherry-picked in, not the entire history.
Normally git cherry-pick automatically creates a new commit as soon as it is done.You can change this behavior with two different options.

1] Use --edit (or -e) to launch the editor and change the commit message before committing the cherry-picked revision. This allows you to edit
the commit message but not the actual commit.

2] You can use --no-commit (or -n) to tell Git to stop as soon as the change has been merged and staged.You can use this to cherry-pick several
commits and then commit them into your local branch as one commit. Remember to start with the oldest commit first when cherry-picking more than one
commit; otherwise, you might end up trying to make a change that isn’t possible or having conflicts because it is in the wrong order.

prompt> git cherry-pick <someCommitID or someBranchName or someTagName>
prompt> git cherry-pick --edit release_1.0
prompt> git cherry-pick --no-commit release_1.0

I am skipping the topic about Moving Branches and Controlling Replaying of Commits for now. You can return to it when needed.


Logs
-----
By default, log shows the commit id, the author, the committer, the date and log message. Logs in git should be of two parts.

1] A one liner explaination of the feature/bug - also called the SUBJECT of the log message.
2] A more detailed explanation (paragraph) about the commit. Be as verbose as possible including any odd preferences you have taken.

prompt> git log //default log details shown.
prompt> git log --oneline //show only first 7 characters of the commit id and the subject of the log message, you can view more commits in one page.
prompt> git log -N //show only the last N commits
prompt> git log -p //also show the actual diff between commits.
prompt> git log HEAD^^^^^..HEAD // Show the last five commits. Each caret sign means go back one commit.
prompt> git log HEAD~10..HEAD //Show the last ten commits.
prompt> git log -1 -p HEAD  //this will show the changes in the last commit on the HEAD.
prompt> git log -stat -2  // Show an abbreviated summary of changes.
prompt> git log --prety=[<format>] //use to format the log output. There are many predefined formats defined.
prompt> git log --prety=format:"%h - %an, %ar : %s" //use to format the log output. There are many predefined formats defined.

Some Option Description of Output
%H Commit hash
%h Abbreviated commit hash
%T Tree hash
%t Abbreviated tree hash
%P Parent hashes
%p Abbreviated parent hashes
%an Author name
%ae Author e-mail
%ad Author date (format respects the date= option)
%ar Author date, relative
%cn Committer name
%ce Committer email
%cd Committer date
%cr Committer date, relative
%s Subject

Many different types of filters are also available.

prompt> git log -- some/path/   //Will show log of files in the given path
prompt> git log -- some_file   //will show log of the given file only.

View the commits in the last week.
You can use many kinds of times with --since or --after. Here are a few variations of looking at the last week of commits:
prompt> git log --since="1 week"
... or ...
prompt> git log --after="7 days"
... or ...
prompt> git log --since="168 hours"   //View the commits prior to the last week.
prompt> git log --before="1 week"
... or ...
prompt> git log --until="7 days"
... or ...
prompt> git log --before="168 hours" //View the log entries by a single committer.

prompt> git log --author="some user" 

View the log entries containing a regular expression.
prompt> git log --grep="some [Rr]eg[Ee]x"
... or ...
prompt> git log --grep="some regex" --regexp-ignore-case
... or ...
prompt> git log --grep="some regex" -i

Viewing Diffs
--------------

prompt> git diff //when called with no arguments; shows the differences between the local working copy and the staging area.
prompt> git diff --staged //Shows the difference between the staging area and the repository.
prompt> git diff HEAD //to view the difference between the working copy and the latest commit in the repository.
prompt> git diff <CommitID> // same as above.
prompt> git diff 423d021 1e85ac3 //to view the difference between two commits that are far apart.
prompt> git diff -- path/  //to prevent too much of a diff by limiting it to a path.




Some quick tips
----------------

So, you just want to revert one file back to its original state:
	git checkout <file>

One problem with this is that you may have is that a file and branch named the same. Since the checkout command is used for 
both reverting files and swapping out to a different branch, you’ll need to use this syntax.

	git checkout -- <file>


If you want to throw out all of the changes you’ve been working on, there’s two ways to do that.
	git checkout -f
	git reset --HARD

export PS1='\[\033[01;32m\]\u@\h\[\033[01;34m\] \w\[\033[01;33m\]$(__git_ps1)\[\033[01;34m\] \$\[\033[00m\] '

If a file is in a conflict state: "git diff" will show you the difference between the two versions of the files.
Also you can use the command "git ls-file -u" command to see the files in conflict. Each file in conflict actually appears
three times. Use the following "git show" command to see the various versions of the file.

prompt> git ls-file -u
prompt> git show :1:README

To view a file on another branch,use the git show command.
prompt> git show <branchName>:<fileName>

To view the list of files that changes in a commit, use the git show command:
prompt> git show --pretty="format:" --name-only <commitID>


Sometimes when trying to resolve a merge, you may want to keep one file instead of the other. You don’t need to open 
up the files and fix the potentially hundreds of conflicts, you just want to choose the one you want
and be done with it. 
So, the scenario is: you’re in the middle of a merge, and you want to keep one file or the other.
$ git merge master     
  Auto-merged _layouts/default.html
  CONFLICT (content): Merge conflict in _layouts/default.html
  Auto-merged index.html
  CONFLICT (content): Merge conflict in index.html
  Automatic merge failed; fix conflicts and then commit the result.

There’s two unmerged files here. According to the git checkout manpage, there’s a --theirs and --ours options on the command.
The former will keep the version of the file that you merged in, and the other will keep the original one we had.
The following commands will keep the original file for index.html, and then use the merged in file only for _layouts/default.html.

git checkout --ours index.html
git checkout --theirs _layouts/default.html


Amend
-----

You can also amend the last commit you have made. 

prompt> git commit -m "Initial commit"
prompt> git add add_forgotten_file
prompt> git commit --amend 

You can change the commit message also. 


HEAD Pointer
------------

It is simply a pointer to the current branch.
It is simply a pointer to the current branch.

Merging
-------

prompt> git checkout master
prompt> git merge hotfix //ie bring all changes done on hotfix branch into the master branch.


Deleting a remote branch
------------------------
You know the syntax for creating a new remote branch from your local branch.
You say:
prompt> git push [remoteName] [localBranch]:[remoteBranch] //Ie. take the local branch and make a remote branch.

Now when you omit the [localBranch], you are basically saying that take nothing and make it a remote branch.. i.e
delete the remote branch.

prompt> git push [remoteName] :[branchName]