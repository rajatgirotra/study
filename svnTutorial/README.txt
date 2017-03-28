Subversion uses URLs to identify versioned files and directories in Subversion repositories.
These URLs use the standard syntax, allowing for server names and port numbers to be specified as part of the URL:
Eg:
$ svn checkout http://svn.example.com:9834/repos

If the repository is local, you should use the file:// access method.
eg:
$ svn checkout file:///var/svn/repos
or
$ svn checkout file://localhost/var/svn/repos

Note that if your repository is on a windows platform, and your working drive is different from your repository drive, then
you must use either if the following two syntax.

C:\> svn checkout file:///X:/var/svn/repos
C:\> svn checkout -"file:///X|/var/svn/repos"
Note that in the second type the URL is quoted so that the "|" symbol is not interpreted as a pipe.

A subversion client will automatically encode your URL just like a web-browser does. For eg: if your URL has spaces or special characters
then SVN translated them accordingly. You only need to ensure to keep ur URL in quotes.

$ svn checkout -"http://host/path with space/project/españa" gets translated to
$ svn checkout http://host/path%20with%20space/project/espa%C3%B1a

From subversion 1.6 onwards, you can use the special caret symbol (^) in place of the repository root. But only if you are in a directory which 
has a working copy of the repository file. This way SVN is able to read the repository path from svn metadata.
Eg:

$ svn list ^/tags/bigsandwich/

Repository access URL types

file:/// 	Direct repository access (on local disk)
http:// 	Access via WebDAV protocol to Subversion-aware Apache server
https:// 	Same as http://, but with SSL encryption.
svn:// 		Access via custom protocol to an svnserve server
svn+ssh:// 	Same as svn://, but through an SSH tunnel.



Global Revision Numbers
Unlike most version control systems, Subversion's revision numbers apply to entire trees, not individual files.
Each revision number selects an entire tree, a particular state of the repository after some committed change.
Another way to think about it is that revision N represents the state of the repository filesystem after the Nth
commit. When Subversion users talk about revision 5 of foo.c, they really mean foo.c as it appears in
revision 5.Notice that in general, revisions N and M of a file do not necessarily differ! Many other version
control systems use per-file revision numbers, so this concept may seem unusual at first.

It's important to note that working copies do not always correspond to any single revision in the repository; they may
contain files from several different revisions. For example, suppose you check out a working copy from a repository
whose most recent revision is 4:

calc/Makefile:4
integer.c:4
button.c:4

At the moment, this working directory corresponds exactly to revision 4 in the repository. However, suppose you
make a change to button.c, and commit that change. Assuming no other commits have taken place, your commit
will create revision 5 of the repository, and your working copy will now look like this:

calc/Makefile:4
integer.c:4
button.c:5

Suppose that, at this point, Sally commits a change to integer.c, creating revision 6. If you use svn update to
bring your working copy up to date, it will look like this:

calc/Makefile:6
integer.c:6
button.c:6

Sally's change to integer.c will appear in your working copy, and your change will still be present in button.c.
In this example, the text of Makefile is identical in revisions 4, 5, and 6, but Subversion will mark your working
copy of Makefile with revision 6 to indicate that it is still current. So, after you do a clean update at the top of your
working copy, it will generally correspond to exactly one revision in the repository.


COMMANDS
--------
  Help
  ----
	$ svn help
	$ svn help <subcommand>



While Subversion's flexibility allows you to lay out your repository in any way that you choose, we recommend that you create a trunk directory to hold
the main line of development, a branches directory to contain branch copies, and a tags directory to contain tag copies. For example:

Subversion repository creation is an incredibly simple task. The svnadmin utility that comes with Subversion provides a subcommand (svnadmin create)
for doing just that.

$ # Create a repository
$ svnadmin create -/var/svn/repos

This creates a new repository in the directory /var/svn/repos, and with the default filesystem data store. Prior to Subversion 1.2, the default was to
use Berkeley DB; the default is now FSFS. You can explicitly choose the filesystem type using the --fs-type argument,
which accepts as a parameter either fsfs or bdb.

Rajat.Girotra@IONDELWS111 /cygdrive/d/Study/SVN
$ svnadmin.exe create --fs-type fsfs -/var/svn/repos

The path argument to svnadmin is just a regular filesystem path and not a URL like the svn client program uses when referring to repositories. Both svnadmin and
svnlook are considered server-side utilities; they are used on the machine where the repository resides to examine or modify aspects of the repository,
and are in fact unable to perform tasks across a network. A common mistake made by Subversion newcomers is trying to pass URLs (even "local" file:// ones)
to these two programs.

Rajat.Girotra@IONDELWS111 /cygdrive/d/Study/SVN
$ svn mkdir file:///var/svn/repos/trunk -m "Creating trunk directory"

Committed revision 1.

Rajat.Girotra@IONDELWS111 /cygdrive/d/Study/SVN
$ svn mkdir file:///var/svn/repos/tags -m "Creating tags directory"

Committed revision 2.

Rajat.Girotra@IONDELWS111 /cygdrive/d/Study/SVN
$ svn mkdir file:///var/svn/repos/branches -m "Creating branches directory"

Committed revision 3.

Rajat.Girotra@IONDELWS111 /cygdrive/d/Study/SVN
$ svn list file:///var/svn/repos/
branches/
tags/
trunk/


  Checkout
  --------
	$ svn checkout http://svn.collab.net/repos/svn/trunk
	
Although the preceding example checks out the trunk directory, you can just as easily check out any deep
subdirectory of a repository by specifying the subdirectory in the checkout URL:
	$ svn checkout \
			http://svn.collab.net/repos/svn/trunk/subversion/tests/cmdline/
			


Every directory in a working copy contains an administrative area; a subdirectory named .svn. Usually,
directory listing commands won't show this subdirectory, but it is nevertheless an important directory.
Whatever you do, don't delete or change anything in the administrative area! Subversion depends on it to
manage your working copy.

If you accidentally remove the .svn subdirectory, the easiest way to fix the problem is to remove the entire
containing directory (a normal system deletion, not svn delete), then run svn update from a parent
directory. The Subversion client will download the directory you've deleted, with a new .svn area as well.


While you can certainly check out a working copy with the URL of the repository as the only argument, you can also
specify a directory after your repository URL. This places your working copy in the new directory that you name.
For example:
$ svn checkout file:///var/svn/newrepo/some/project mytree

That will place your working copy in a directory named mytree instead of a directory named trunk as we did previously.
The directory mytree will be created if it doesn't already exist

   Update
   ------
Use svn update to bring your working copy into sync with the latest revision in the repository:
Eg:
$ svn update
U foo.c
U bar.c
Updated to revision 2.


   svn add foo
   -----------
	Schedule file, directory, or symbolic link foo to be added to the repository. When you next commit, foo will
	become a child of its parent directory. Note that if foo is a directory, everything underneath foo will be
	scheduled for addition. If you want only to add foo itself, pass the --depth empty option.
	
  svn delete foo
  --------------
	Schedule file, directory, or symbolic link foo to be deleted from the repository. If foo is a file or link, it is
 	immediately deleted from your working copy. If foo is a directory, it is not deleted, but Subversion schedules
	it for deletion. When you commit your changes, foo will be entirely removed from your working copy and the
	repository.
	
  svn copy foo bar
  ---------------
        Create a new item bar as a duplicate of foo and automatically schedule bar for addition. When bar is added to
        the repository on the next commit, its copy history is recorded (as having originally come from foo). svn copy
        does not create intermediate directories unless you pass the --parents option.
        
  svn move foo bar
  ----------------
       This command is exactly the same as running svn copy foo bar; svn delete foo. That is, bar
       is scheduled for addition as a copy of foo, and foo is scheduled for removal. svn move does not create
       intermediate directories unless you pass the --parents option.

  svn mkdir blort
  --------------
       This command is exactly the same as running mkdir blort; svn add blort. That is, a new directory
       named blort is created and scheduled for addition.

  svn status, svn diff, and svn revert
  ------------------------------------
You can use the commands svn status, svn diff, and svn revert without any network access even if your
repository is across the network. This makes it easy to manage your changes-in-progress when you are
somewhere without a network connection, such as traveling on an airplane, riding a commuter train, or
hacking on the beach.

Subversion does this by keeping private caches of pristine versions of each versioned file inside the .svn
administrative areas. This allows Subversion to report and revert local modifications to those files without
network access. This cache (called the "text-base") also allows Subversion to send the user's local modifications
during a commit to the server as a compressed delta (or "difference") against the pristine version. Having this
cache is a tremendous benefit even if you have a fast Internet connection, it's much faster to send only a file's
changes rather than the whole file to the server.

svn status
----------
?	 scratch.c	 	# file is not under version control
A	 stuff/loot/bloo.h 	# file is scheduled for addition
C	 stuff/loot/lump.c 	# file has textual conflicts from an update
D	 stuff/fish.c 		# file is scheduled for deletion
M	 bar.c 			# the content in bar.c has local modifications

svn status also has a --verbose (-v) option, which will show you the status of every item in your working copy,
even if it has not been changed:
$ svn status --v
M	 44	 23	 sally	 README
	 44	 30	 sally	 INSTALL
M	 44	 20	 harry	 bar.c
	 44	 18	 ira	 stuff
	 44	 35	 harry	 stuff/trout.c
D	 44	 19	 ira	 stuff/fish.c
	 44	 21	 sally	 stuff/things
A	 0	 -?	 -?	 stuff/things/bloo.h
	 44	 36	 harry	 stuff/things/gloo.c

This is the "long form" output of svn status. The letters in the first column mean the same as before, but the second
column shows the working revision of the item. The third and fourth columns show the revision in which the item
last changed, and who changed it.

None of the prior invocations to svn status contact the repository instead, they compare the metadata in the .svn
directory with the working copy. Finally, there is the --show-updates (-u) option, which contacts the repository
and adds information about things that are out of date:

$ svn status --u --v
M	 *	 44	 23	 sally	 README
M	 	 44	 20	 harry	 bar.c
	 *	 44	 35	 harry	 stuff/trout.c
D		 44	 19	 ira	 stuff/fish.c
A		 0	 -?	 -?	 stuff/things/bloo.h
Status against revision: 46

Notice the two asterisks: if you were to run svn update at this point, you would receive changes to README and
trout.c. This tells you some very useful information you'll need to update and get the server changes on README
before you commit, or the repository will reject your commit for being out of date (more on this subject later).

So for you best option is to always use "svn status -uv"

svn diff also prints filename and offset information useful to the patch program, so you can generate patches by redirecting the diff output to a file:

$ svn diff > patchfile
or
$ svn diff -x -uw -x --ignore-eol-style > patchfile
w for ignoring white spaces and u for displaying unified output (ie. 3 lines before and 3 lines after will be shown).
--ignore-eol-style ignore diff because of windows and linux line endings.

You could, for example, email the patch file to another developer for review or testing prior to a commit.

$ svn diff --r 2:3 rules.txt  --> For diffing revision 2 and revision 3 of rules.txt
or
$ svn diff -c3 rules.txt  --> For diffing revision 2 and revision 3 of rules.txt

Subversion uses its internal diff engine, which produces unified diff format, by default. If you want diff output in a
different format, specify an external diff program using --diff-cmd and pass any flags you'd like to it using the --
extensions (-x) option. For example, to see local differences in file foo.c in context output format while ignoring
case differences, you might run

$ svn diff --diff-cmd /usr/bin/diff --extensions '-i' foo.c.

note that svn revert can undo any scheduled operations for example, you might decide that you don't want to add a new file after all:
	$ svn status foo
	? foo

	$ svn add foo
	A foo

	$ svn revert foo
	Reverted -'foo'
	
	$ svn status foo
	? foo
	

When there are conflicts and you try to merge using svn update, you can get stuck at the following:

Rajat.Girotra@IONDELWS111 /cygdrive/d/Study/SVN/mytree
$ svn up
Conflict discovered in 'foo.c'.
Select: (p) postpone, (df) diff-full, (e) edit,
        (mc) mine-conflict, (tc) theirs-conflict,
        (s) show all options: p
C    foo.c
Updated to revision 4.
Summary of conflicts:
  Text conflicts: 1

If you postpone to manually remove conflict by hand, three new files are created by svn.

Rajat.Girotra@IONDELWS111 /cygdrive/d/Study/SVN/mytree
$ ls -ltr foo.c*
-rw-r--r--+ 1 Rajat.Girotra Domain Users  25 Apr 15 13:27 foo.c.r4  --> the revision on which you made your changes
-rw-r--r--+ 1 Rajat.Girotra Domain Users  25 Apr 15 13:27 foo.c.r5  --> the revision which currently exists in repos.
-rw-r--r--+ 1 Rajat.Girotra Domain Users 164 Apr 15 13:27 foo.c.mine --> your changes
-rw-r--r--+ 1 Rajat.Girotra Domain Users 204 Apr 15 13:27 foo.c   --> merged file with conflicts.

svn will not allow you to commit foo.c unless you remove the conflicts. There are two ways:

1] You manually delete all three files created by svn
2] use the svn resolve command
   
Rajat.Girotra@IONDELWS111 /cygdrive/d/Study/SVN/mytree
$ svn resolve --accept working foo.c
	Resolved conflicted state of 'foo.c'

Rajat.Girotra@IONDELWS111 /cygdrive/d/Study/SVN/mytree
$ ls -ltr foo.c*
    -rw-r--r--+ 1 Rajat.Girotra Domain Users 204 Apr 15 13:27 foo.c
      
Rajat.Girotra@IONDELWS111 /cygdrive/d/Study/SVN/mytree
$ svn status -uv
M                5        5 Rajat.Girotra foo.c
                 5        1 Rajat.Girotra bar.c
                 5        1 Rajat.Girotra subdir/quux.h
                 5        1 Rajat.Girotra subdir
                 5        5 Rajat.Girotra .
Status against revision:      5

Rajat.Girotra@IONDELWS111 /cygdrive/d/Study/SVN/mytree
$ svn commit -m "make foo.c sane" foo.c
Sending        foo.c
Transmitting file data .
Committed revision 6.


LOG
---
$ svn log <file or directory name>
Eg:
   $ svn log foo.c

   $ svn log -r 1:3 foo.c  --> to see logs from revision 1 to 3 in chronological order.
   $ svn log -r 3:1 foo.c  --> to see logs from revision 1 to 3 in reverse order.
   
SVN LIST and SVN CAT
--------------------
Using svn cat and svn list, you can view various revisions of files and directories without changing the working
revision of your working copy. In fact, you don't even need a working copy to use either one.

eg:
Rajat.Girotra@IONDELWS111 /cygdrive/d/Study/SVN
$ svn cat -r5 file:///var/svn/newrepos/some/project/foo.c
foo.d
#include <stdio.h>

$ svn cat --r 2 rules.txt > rules.txt.v2


The svn list command shows you what files are in a repository directory without actually downloading the files to your local machine:
	$ svn list http://svn.collab.net/repos/svn
	README
	branches/
	clients/
	tags/
	trunk/

If you want a more detailed listing, pass the --verbose (-v) flag to get output like this:
	$ svn list -v http://svn.collab.net/repos/svn
	20620 harry 1084 Jul 13 2006 README
	23339 harry Feb 04 01:40 branches/
	21282 sally Aug 27 09:41 developer-resources/
	23198 harry Jan 23 17:17 tags/
	23351 sally Feb 05 13:26 trunk/

The columns tell you the revision at which the file or directory was last modified, the user who modified it, the size
if it is a file, the date it was last modified, and the item's name.	


$ svn checkout -r 1729 # Checks out a new working copy at r1729
$ svn update -r 1729   # Updates an existing working copy to r1729

Export
------

Sometimes you want to build a release and package up all your data; but not the .svn directories.
For that you can use the svn export command.

$ svn export http://svn.example.com/svn/repos1 # Exports latest revision
$ svn export http://svn.example.com/svn/repos1 --r 1729 # Exports revision 1729

Good Thing
----------

Let say you want to delete a working copy. You can quickly do an svn status and check if there are any unversioned file and if they are of any relevance.
Else you can delete the working copy.

svn status -vu | grep "^\?"


SV Properties : Just a key value pair, Can be assigned to individual files or to the complete revision as a whole
-------------
svn propset <propetyName> <propertyValue>  <FileName> : Eg - svn propset Copyright '2014. All rights reverved' abcd.cpp
svn propset --revprop -r <revionNo/Date/or HEAD/BASE/COMMITED/PREV> - to apply a property to a complete revision.
-R flag can be used for recursively setting the property.

svn proplist -v <fileName>
svn propget Copyright README.txt --> To get a property whose name you know. Otherwise use proplist
svn propedit <propertyName> <FileName>  -->> This will launch an editor with the current propety value and you can save the new value.
svn propdel <propertyName> <fileName>
Very very trivial actually.

svn defined properties begin with "svn:" prefix. Eg: "svn:ignore", "svn:executable", "svn:externals" etc etc.
Now svn automatically tries to set a no. of properties itself when u first add a file to svn.

Eg: If you add a.out, then svn adds an "svn:executable" propety automatically. Also it tries to set  the mime-type property.
[1020 03:25:41 Fri Sep 27 rgirotra@mylpadeci12 test]$ svn commit -m "a.cpp and a.out"
Adding         a.cpp
Adding  (bin)  a.out
Transmitting file data ..
Committed revision 12.
[1021 03:25:57 Fri Sep 27 rgirotra@mylpadeci12 test]$ svn proplist -v a.out
Properties on 'a.out':
  svn:executable
    *
  svn:mime-type
    application/octet-stream

Subversion also provides a feature via its runtime configuration system where you can create a mapping file which contains filename patterns and the corresponding property names and values.
When any new file is added to svn, it will automatically use this file to see if it matches any pattern and will attach the property to that file automatically.
For eg: for any new *.jpg, it can attach  the property svn:mime-type to image/jpeg. For any *.cpp, svn:eol-style to native and svn:keywords set to Id etc..

users can configure a new mime-types-file runtime configuration parameter, which identifies the location of a MIME types mapping file. Subversion will consult this mapping
file to determine the MIME type of newly added and imported files.

SVN USES THE svn:mime-type property to check if a file is a contextual one or non-contextual. If this property is not present, it will assume its a human readable file.
Linux does not know how to handle windows text files (ending with CRLF characters, so it assumes that CR is a regular character) which usually gets rendered as ^M.
Similarly, windows doesnt know how to handle linux text files (which end in LF) and concatenates the whole text as one giant line as it is not able to find the CRLF character sequence.

Ok to avoid seeing the ugly diff reports caused because of different EOL styles for Windows and Linux, always the svn:eol-style to native. This way svn will always store the file in svn with
Linux line endings but when it will checkout it will change it to your native OS's EOL format. Also diff reports will look sane.
Probably a good option to include this property in the mime configuration file so that it gets associated with new files automatically.


SVN IGNORE LIST
----------------

There are two ways to tell svn to ignore files which you dont want to see in "svn status"  etc.. One is to use the "global-ignores" parameter from the svn configuration area.
The default "global-ignores" is: *.o *.lo *.la #*# .*.rej *.rej .*~ *~ .#* .DS_Store.

The other way is to set the "svn:ignore" property on a directory. This is just a whitespace separated list of filename patterns that will be ignored.
When i tried, it was not a whitespace separated list for me but rather a new pattern on every line.

?
Matches any single character
*
Matches any string of characters, including the empty string
[
Begins a character class definition terminated by ], used for matching a subset of characters


SVN LOCKING
-----------

svn also has a locking mechanism where you can lock a file so that no one else can check it in. This is usually required for non textual files where there is no merging tool available.
Eg png, jpeg, mpeg, bin files. So basically you want to avoid clashing commits

A lock can be acquired by the svn lock command

svn lock banana.jpg -m "Need to make a quick tweak".  svn creates a unqiue token (called lock token) and stores it in your working copy's metadata. This means that the file
can be unlocked only by that working copy and not from a different working copy even if the user is the same. This means that lock is associated with a working copy rather than
a user. The lock is released automatically when you do a commit (or by svn unlock command). This is to ensure no one holds on to a lock for a long time. You can override this behavior by specifying 
a --no-unlock option to svn commit.

[1101 06:48:50 Fri Sep 27 rgirotra@mylpadeci12 test]$ svn lock a.cpp -m "Making a quick tweak"
'a.cpp' locked by user 'rgirotra'.

To check on which file is locked and who own it. run either "svn status -uv" or "svn info fileName"
[1102 07:20:50 Fri Sep 27 rgirotra@mylpadeci12 test]$ svn status
     K  a.cpp  --> K means this working copy is acquiring a lock on a.cpp
	 
[1114 07:22:52 Fri Sep 27 rgirotra@mylpadeci12 test]$ svn info file:///devshared/home/rgirotra/local/svn/repos/test/trunk/a.cpp
Path: a.cpp
Name: a.cpp
URL: file:///devshared/home/rgirotra/local/svn/repos/test/trunk/a.cpp
Repository Root: file:///devshared/home/rgirotra/local/svn/repos/test
Repository UUID: 03920cf6-08ee-4dac-842a-bebe71d5c3ef
Revision: 15
Node Kind: file
Last Changed Author: rgirotra
Last Changed Rev: 15
Last Changed Date: 2013-09-27 06:47:04 +0000 (Fri, 27 Sep 2013)
Lock Token: opaquelocktoken:db86ca25-3b7e-45e1-836d-b753849c53df
Lock Owner: rgirotra
Lock Created: 2013-09-27 07:20:50 +0000 (Fri, 27 Sep 2013)
Lock Comment (1 line):
Making a quick tweak

svn unlock --unforce <URL> --->> Note use the --force option and the URL

Better still - use
svn lock --unforce fileName --->> Will break the lock and lock it again in your working copy.

Instead of K, now it will show a B(Broken) in the original lockers working directory.
 
Users and administrators alike are encouraged to attach the svn:needs-lock property to any file that cannot be contextually merged.
This is the primary technique for encouraging good locking habits and preventing wasted effort.


SVN EXTERNALS
-------------

Another great property. You can use this property to create a working copy which checkouts different subdirectories from different locations in the repository
or from different repositories altogether. This property has a multine value so always use svn propedit svn:externals <DirectoryName> instead of svn propset.
The format of svn externals is also shown below (its same as for svn checkout: i.e. revision no followed by URL followed by local system path)

$ svn propget svn:externals calc
-rHEAD   http://svn.example.com/repos/sounds   third-party/sounds
-r148    http://svn.example.com/skinproj       third-party/skins
-r21     http://svn.example.com/skin-maker     third-party/skins/toolkit


Branching and Merging
---------------------

Creating a branch is simple. Always create a branch using URL. Also in svn creating branches is very cheap and constant time operation
so create as many branches as you like. Also a branch is nothing but a link to the soure branch. No copies of files is done etc.
So very cheap and fast. There is actually no concept of branch in svn. It just nows that it has created a new directory which carries
some extra historical information.

svn copy -m "Creating a branch for ebbs" file:///devshared/home/rgirotra/local/svn/repos/test/trunk \
                                         file:///devshared/home/rgirotra/local/svn/repos/test/branches/ebbs
										 
Simplest Merge command
----------------------

svn merge  file:///devshared/home/rgirotra/local/svn/repos/test/trunk 

To bring all changes from trunk into your local branch. svn remembers when it had created this branch, so it
will know what all to merge. Also it sets the svn:mergeinfo property which is some important metadata used by
svn. We should never touch it. Eg of svn:mergeinfo next. This property is used when you again bring changes from trunk
into your branch. SO svn will remember what it had merged last time and where to continue from.

Property changes on: .
___________________________________________________________________
Added: svn:mergeinfo
   Merged /trunk:r17-20

You can always revert a merge using svn revert -R . (ie recursive starting from the top directory).
So if you are working on a branch, you should keep bringing in changes from trunk to make sure you do not drift too much apart
that later on it becomes near impossible to merge without major conflicts.


Also when you are done working on your changes, you'll want to merge your changes into trunk, so that everyone has it
and can use the new feature you have developed.So basically now you want to merge your changes into trunk. For that
go to a trunk working directory and make sure it is clean. Then simply use "svn merge" but with the "--reintegrate" option.
which will carefully merge your branch changes into trunk. Eg:

svn merge  --reintegrate file:///devshared/home/rgirotra/local/svn/repos/test/branches/b1

Once you reintegrate your changes from branch into trunk, that branch is no longer usable. svn cannot correctly further merge
change into that branch from trunk or vice-versa. So you'll have to create a new branch from trunk and work on that.

svn delete -m "Comment" <branchURL>

Instead of using "svn proplist -v ." to view the what changes have been brought into this branch. use the "svn mergeinfo" command instead.
The "svn mergeinfo" command takes a URL as the first parameter which is the branch from which the changes will be coming into your branch,
which is the optional second parameter.

cd ebbsBranch
svn mergeinfo ^/trunk  -->> will tell you what revisions are already present in ebbsBranch from trunk

svn mergeinfo ^/trunk --show-revs eligible  -->> Show what changes will come into this branch from trunk.

In svn merge, you can also pass a --dry-run option to see what changes will come.

Reverting a change in repository
--------------------------------
In svn think of every revision as a changeset. When you use "svn merge", svn calculates which all revisions(ie changsets)
should be applied to your working copy. Similarly you can use svn merge to uncommit a changeset. For example, you are using
trunk and you realise that version 303 should not have been checked in as it is completely wrong. You can ask svn to complete remove
that change for you using svn merge

svn merge -c -303 ^/trunk
svn commit -m "Removing changes done in 303"


Resurrecting Deleted files
-------------------------
You can resurrect deleted files/directories using "svn merge -c -[URL@REV]" or
"svn copy URL@REV WCPATH" command. The advantage of svn copy is that it maintains history of the file.


	