C-x C-f : find file
C-x C-v : open another file
C-x i : Insert another file.
M-> : Go to end of file.
M-< : Go to beginning of file.
C-x C-s : Save
C-x C-w : SaveAs
C-h : help
C-h ? : Help with options
C-h t : Start tutorial
C-h k : tell me more about what this (k) key combination does.
C-h f : tell me moew about what this (f) function does.
M-x version: Display emacs version.
C-g: Quit typing command in minibuffer.

Paragraph writing:
For paragraph writing, you can use either refill-mode or auto-fill-mode
However, never use both modes  together. I suggest you use auto-fill-mode

M-x auto-fill-mode: Toggle mode on or off.
Remember auto-fill-mode does not reformat a paragraph. For that go back to
any line in the paragraph and type 

M-q : fill-paragraph. It will automatically be reformated.

C-x u : undo command

Cursor movenment

C-f: forward
C-b: back
C-p: previous
C-n: next
M-f: forward by word
M-b: backwards by word
C-a: go to beginnig of line
C-e: go to end of line
M-a: go to beginning of sentence
M-e: go to end of sentence
M-{: go to beginning of paragraph
M-}: go to end of paragraphA

C-q C-l : C-q is quoted insert. It means you want to literally insert a C-l control character is the file
rather than Emacs interpreting it as a command key. Try it out..!!

C-v : scroll up in file
M-v: scroll down in file
M-x goto-line Enter n : goto line n in the file.
M-x goto-char Enter n : goto char n in the file

Repeating commands
Use either M-n (like M-10 to repeat 10 times), or use C-u to repeat 4 times.
C-u C-u will repeat 16 times and so on.
So
C-u C-u C-u C-n will take u 4*4*4 = 64 lines down.

C-l will scroll so that the current line becomes the middle line in the window. Is convenient many times.


Deleting:
C-d will delete the character under the cursor.
M-d will delete the complete word whose character is under the cursor.
M-<backspace> (called M-DEL) : will delete the word before the cursor
C-k will delete the entire line starting from the cursor. So go to first character in the line and then use C-k
All of the above deletions go into a kill ring and can be pasted using
C-y

C-s : incremental search
C-r : Same as above but in reverse direction

 

C-x b followed by buffer name. If buffer name is a new buffer, open an empty buffer. Otherwise open the file in the buffer.
C-x C-b – open buffer list. Note how closely C-x C-b and C-x b commands are.
in GUI you can click the Ctrl+left mouse button. this will bring up the GUI screen(called emacs buffer pop menu) where you can select any open buffer by major mode

You can also use C-x --> (forward arrow) or C-x <-- (backward arrow) to cycle thru the open buffers

C-x k - to kill the currently displayed buffer
M-x kill-some-buffers, will ask interactively, if it wants to kill a buffer.

To create a new window
C-x 2 - This will create a new window with the same buffer as the current window, split horizontally.
Repeat the above command to create more windows
C-x 3 splits it vertically.
Let say you want to open a file in another window. The commands for doing something in another windows are similar to normal commands
with a "4" in them. The below command will as for a filename and open it in a new window.
C-x 4 f

Similarly to select an open buffer in a new window, do
C-x 4 b

Also C-M-v scrolls up the other window. If multiple windows are open,
i dont yet which one will it scroll. 
use C-M-S-v to scroll in the other direction.

Use
C-x o : to move from one window to another. Right now i dont think there is a way to move to a specific window directly
so we will have to type C-x o repeatedly.

To close a single window, type
C-x 0 : ie C-x zero in that window. It will only close the window. All buffers and unsaved changes remain.
to close all windows except the one you are working in, type 
C-x 1

If multiple windows in the same emacs frame becomes too small. you can work with frames also instead.
All frames you open will have the same buffer list across all frames. Commands are very similar to the window commands.

To open a new frame, do

C-x 5 2: will open a new frame with the same buffer as the current one
C-x 5 f: will open a file in a new frame.
C-x 5 b: will open an already existing buffer in a new frame.
C-x 5 0: will kill the frame.
C-x 5 o: to switch between frames.
C-x 5 1: will kill all frames except the current one. If you see commands for windows and frames are very similar.
C-M-v: will scroll up the other window or frame. I dont know how emacs select which one to scroll.
C-M-S-v: will scroll down
C-z: to minimize a frame.

C-x s : save-all buffers. Interactive command. Enter y,n,!(to save all),.(to save the current buffer only),q(to quit),C-r(to visit file before saving)

M-x rename-buffer: to rename a buffer. Remember only buffer name changes, not the filenmae associated with this buffer.
If you have more than one buffers with the same name, emacs will name them like "abc", abc<1>, abc<2> etc. However there is a better way
in which u can tell emacs to display the parent directory for buffers with the same name. The option is "Use directory names in buffer names" in Options menu.

C-x C-q : toggle read mode of a buffer. If you open a read only file, then the buffer will be read only.
          If you still want to edit it, use C-x C-q to toggle read only mode and save a copy of the file elsewhwre using C-X C-w

Using the buffer list:
C-x C-b brings up the buffer list window. C-x o will take you to it. Use C-n and C-p to navigate to different columns. Everything in buffer list is done using
a single character. If you are on any line in the buffer list
1) d or k: will mark the buffer for deletion.
2) u: will undo
3) s: will mark it for saving
4) %: will toggles read-only mode
5)~(ie tilde): will tell emacs that the buffer is unmodified so dont auto-save it.
6) 1: to open the buffer in the complete window.
7) f: to open the buffer in the same BufferList window
8) o: to open the buffer in any other randon window, not the BufferList
9) m : to mark multiple buffers.
10) v: All the marked buffers will be opened in different windows, split horizontally.
11) q: quit the bufferList
Use x ie (execute) after doing d, u or s. % and ~ get applied immediately.

Resizing windows: You can grow or shrink a window
C-x ^ : will grow it taller
C-x }: will widen it
M-x shrink-window: will shrink its height
C-x {: will shrink it width.
C-x - : will shrink window to its buffer. Only possible if buffer is smaller than the window
C-x +: will make all windows equal size.

To compare two files, you can use Ediff. We'll learn more about Ediff later.

Bookmarks are a way to mark a location in a file. All bookmarks are stored by user in their home directory in a file
called .emacs.bmk
When you restart emacs, you can quickly jump to any of ur bookmarks which takes you straight to that file and location.
Create a bookmark with
C-x r m: The bookmark will be set at the current cursor location. Emacs will ask u for a bookmark name. An existing bookmark name
will be overwritten by a new one.
Jump to a bookmark using
C-x r b <BookmarkName> --> Use tab if the bookmark name does not come up.
To open the "Bookmark List": use
C-x r l : will open the bookmarks and lets u play with it, just like u play with one character commands in buffer list
M-x bookmark-rename
M-x bookmark-delete
In Bookmark list u can do
1) Enter, f : to jump immediately to that bookmark
2) d: to mark for deletion
3) r: to rename
4) m: to mark multiple bookmarks for opening
5) v: will open the selected bookmarks in different windows
6) s: to mark for saving
7) u: to undo
8) o: to open the bookmark in a new window
9) e: to add an annotation to your bookmark. Any descroptive string which you might think will be useful.
10)A: will display all annotations
11) q: exit bookmark buffer.

Emacs Shell mode
M-!  : emacs will ask a command to run in the shell and display the output in a "Shell Command Output" buffer
M-| : emacs will run thr shell command on a selected region
C-u M-!: slight variation. If prefixed with C-u, the shell output is written to the current buffer, instead of "Shell Command Output"

To enter into emacs shell mode, type:
M-s shell : this will bring up you command prompt.
You can now run commands and output will be produced in the shell buffer itself. If the out is cluttering your
buffer, use
C-x C-o: which flushes ur last command output.
Also since C-c is a frequently used command in emacs itself, if you want to interrupt the shell command using Control C. You have to do:
C-c C-c : ie Control C twice. Similarly for
C-c C-z : will stop the current command.
C-c C-d etc etc.
The run previous commands, do M-p (for previous) and M-n(for next).
Use tab for completion just like you do in a normal unix shell.

Ok now sometimes the shell output can be very large that its scrolls your buffer and you are not able
to view the first line of the output. emacs provides a way out
C-c C-r : will take you to the first line of the last output
C-c C-e : will take you to the last line of the last output.
Also emacs groups outputs into groups. A group is a command and its output.
C-c C-p : will take u to previous commands and their outputs
C-c C-n : will take u to next commands and their outputs.

If you want to open multiple shells, first use:
M-x rename-uniquely : which will rename ur current shell. Then use M-x shell Enter to create more
shell buffers.

Ok, when you type into emacs shell, even passwords appear in plain text.
So add the following hook to ur .emacs file. Whenever, emacs will see a password prompt, it will ask u for the text
in the minibuffer and then send it to console.
(add-hook 'comint-output-filter-functions
           'comint-watch-for-password-prompt)

Emacs directory editing
1) Start emacs with a directory argument
2) or C-x C-f and specify a directory path
3) C-x d
4) C-x 4 d opens dired in new window.
The mode line says "Dired by name" meaning entries are sorted by name.
Press s to toggle between entries by name and by date.

Most of the single character commands in the "Buffer List" and the "Bookmark Buffer" are similar.
1) v : to view a file in the same window. Pressing Enter will scroll thru the file. Pressing s will do search. Pressing q qill return/close file.
2) d : mark for deletion
3) x : execute
4) f : open the file in buffer for editing
5) # : will mark all auto-save files for deletion
6) ~ : will mark all backup files for deletion
7) D: will delete immediately
8) C : will copy and ask u where to store
9) R : rename file or move file
10) m : to mark a file
11) %l or %u: when marked will rename file to upper case or lower case.
12) t : will mark all umarked files and folders and unmark all marked files and folders.
13) Z : will automatically compress the file under the cursor. so a.txt becomes a.txt.gz
        emacs understands gzip compression only.
14) to create a tar file, mark all files and folder u are intersted in and press !
    This will bring u into shell prompt where you can say tar-cvzf abc.tar.gz *
    which will do the tar.
15) By default, emacs should enable editing gz files also just by opening them and editing them. However, if it is not
supported. enter this into .emacs
(auto-compress-mode   1)
16) Comparing files: mark one file. Take the curor to the other file. and press =, emacs will open the diff.
17) g : to refresh the dired buffer.
18) M-Del(backspace) Enter: will remove all marks from dired.
19) **, */, *@ - will mark executables, directories and symbolic links automatically.
20) %m: emacs asks for regexp to match files to be marked.
21) %g: emacs asks for regexp to match files which contain that regexp.
22) + : create a subdirectory., use + and R to together to create directories and move files in that folder
23) A: emacs asks for a regexp to search in the marked files. Use M-, to see all of the files in which regexp is found.
24) i : will insert the subdirectory deatils in the same buffer. So the dired buffer will have two directory listsing. Parent and its subdirectory.
25) P : to the print a file. emacs puts the printing command "lpr" in the minibuffer and you can edit it as you like before printing.

M-x print-buffer
M-x print-region
M-x lpr-buffer
M-x lpr-region

M-x man Enter <command> Enter to read man pages in emacs itself.

M-x calendar
q for quitting it.

C-t: To SwAP TWO LETTERS.
M-t: to swap two words
C-x C-t: To Swap Two Lines.

M-c : capitalize the first alphabet of the next word
Meta - c: (Alt+hypen+c, same as above but with hypen): capitalize the first alphabet of the previous word.
M-u : capitalize the whole word
Meta - u: capitalize the previous word
M-l : lowercase the next word
Meta -l: lowercase the previous word.

Overwrite Mode: Simialar to pressing R and typing to erase text under the cursor
Press Insert to enter this mode. or use
M-x ov to toggle Overwrite mode.

Also get used to C-_ for undoing instead of C-x u

M-x recover-file : To recover from an auto-save file (#file#)
Also look at variable auto-save-interval to change this later to suit your needs.


C-s : incremental search forward
C-r : incremental search backward
C-s Enter : NON incremental search forward
C-r Enter : NON incremental search backward
M-s w : incremental word search forward
M-s w Enter: NON incremental word search forward

C-s C-w : search the word under the cursor (word starts from cursor position)
C-s C-y : search text in the kill ring
C-s C-y (then M-p or M-n) : to search for previous entries in the kill ring

M-x replace-string : will replace all occurrences of string1 with string2 starting from the cursor position. So use M-< first to
                                 go to beginning of file.

C-x Esc Esc (followed by M-p or M-n) : repeat previous commands

M-% : query replace is in progress
Query options:
y : replace and move on
n : no and move on
. : only replace this one and quit
, : replace this one and wait dont move on.
! : replace all and dont ask
q : quit
Do C-r: suspend query replace.. do what you want
C-M-c : restart query replace where you left off.
In fact, M-x recursive-edit puts you in that mode from within any command. Use C-M-c to come out.

M-x set-variable : to set the value of a variable. Eg:
However this is only valid for a session. For permanent solution, either put in .emacs manually or use M-x custom
(setq-default case-fold-search nil) ; require exact matches
(setq-default case-replace nil) ; never change case when replacing

Regex search: wildcards you must know already
^ : search at beginning of line
$ : search at end of line
. : match any single character
.* : match zero or more occurrences of any character
\< : Match the beginning of a word
\> : Match the end of a word
\s: match whitespace. \S : match anything but a whitespace
\d: match any digit. \D match anything but a digit
\w: match any word, _ or digits. \W match anything but a word.
[abc]: match any character a,b or c
To search for ^,$,.,* etc use \ to escape it.

Commands are very similar
C-M-s : incremental regexp search forward
C-M-s Enter: NON incremental regexp search forward

C-M-r : incremental regexp search backward
C-M-r Enter: NON incremental regexp search backward


M-/ : equivalent of Ctrl-p in vim. 
You can create abbreviations in emacs just like in vim. The abbreviations are store in 
~/.emacs.d/abbrevs-defs file (Do not edit by hand)
To create abbreviation of the word under the cursor, do
C-x a i g (meaning add inverse global) for adding abbrev to global mode
C-x a i l (meaning add inverse local) for adding abbrev for local major mode only
M-x abbrev-mode (to turn on Abbrev mode, abbrev only work when this is enabled)
Prefer setting
(setq-default abbrev-mode t) in your .emacs
(setq save-abbrevs t)
M-n C-x a g (M-n defines the no of words before the cursor to include in the abbreviation). This command will then ask u for the abbreviation
Eg:
Indian Institute of Technology (assume cursor is after Technology)
Press M-4 C-x a g Enter iit Enter
M-x list-abbrev
M-x edit-abbrev
M-x write-abbrev-file
M-x kill-all-abbrev – to disable all abbrev
M-x read-abbrev-file to enable them again

M-x version : will give emacs version

C-a C-k : to delete all text from minibuffer.

In emacs you have a command
M-x compile Enter : which runs a compilation command in a new window (called compilation buffer).
C-x ` : will take you to the compiler errors one by one
M-n & M-p
C-c C-c: go to source code of the error file.
(setq 'compile-command "mkbuild_ninja")  to set the default compile command OR
M-x set-variable

C-u C-x` : to jump back to the first error
Compilation buffer shows [run] until compilation is running. Shows “exit [0]” once it finished without issue
ONE THING TO REMEMBER IS: The compilation command is not interpreted by a shell. It is just exec’ed by emacs (ie the process runs in an
Inferior shell).
So any aliases (like n for mkbuild_ninja), shell functions and other shell-specific things will not work. That’s why we are using
mkbuild_ninja
To make the above work we need to somehow source the bashrc again before running the compiler command.
We have an emacs variable “shell-command-switch” which by default is set to –c. If we set it to –ic, (ie interactive), then by default
bashrc is sourced. But this leads to dramatic slow down of emacs, because it always sources bashrc. The way is to source it only when doing the 
compile command or any other command where you need to source it explicitly.
;; Define + active modification to compile that locally sets
;; shell-command-switch to "-ic".
(defadvice compile (around use-bashrc activate)
  "Load .bashrc in any calls to bash (e.g. so we can use aliases)"
  (let ((shell-command-switch "-ic"))
    ad-do-it))
The above will make sense only later when you study lisp.
Space : scroll down
Del : scroll up
The M-x compile command belongs to the compile package. This package also includes support for multifile grep
M-x grep : Very helpful sometimes



All modes in emacs (fundamental, text, shell, dired, buffer list) have two main components:
1)	An emacs lisp package that implements the mode
2)	A function that invokes it.
For c++ mode, we use M-x c++-mode (so the function name is c++-mode). When you open a file, emacs tries to put the buffer in thr correct mode using the file extension.
If the file suffix is not in the list, then the mode will not be autoloaded. So u’ll need to edit your .emacs to load the package for the suffix u are using. This is done in 2 steps
1)	Autoload function
(autoload ‘MYFunction “filename/packageName” “description” t) : This basically says, that if emacs is unable to find a function “MyFunction”, then it should load the
<filename> package. So basically we create an association between a function and the package which implements it.

2)	You need to extend the auto-load-alist variable to include your suffix also. Read about it C-h v Enter auto-mode-alist 
(setq auto-mode-alist (cons ‘(\\.hcpp$ .c++-mode) auto-mode-alist))

Just like auto-mode-alist, we also have
1)	interpreter-mode-alist : which looks at the the first interpreter line #! To find which mode to use
2)	magic-mode-alist: which finds modes based on file contents

cons above is a simple command "meaning construct a list".
so if list if (a b c d) the cons e (a b c d) becomes ( e a b c d ), we'll look at other commands later.

M-; : to add comments in C++
C-M-\ : indents a line or region in C++ according to internal indenting rules
M-m : will move to the first character in the line. Use this instead of C-a
M-^ : Join this line to the previous one.

M-x font-lock-mode : Brings colors to the emacs. Otheriwse everything is black n white.
;;Turn on font-locking globally
(global-font-lock-mode t)
Also u can do
M-x list-faced-display to customize font colors like (comments, variables, classese etc etc)

Very useful c++ mode commands

M-a : Move to first character in the line
M-e : Move to the last character in the line
C-M-a : Move to the first line in the function
C-M-e : Move to the last line in the function
C-M-h : Will copy the whole function.
C-c C-q : indent the whole function under the cursor.

Indentation-style. emacs supports various styles by default like bsd, k&r, gnu, stroutsup etc.
Look at variable c-style-alist to check which all styles are available. To choose one of them
use
 M-x c-set-style Enter Tab Enter
 The style is stored in variable c-indentation-style
You can also define your own formatting style but that will require a lot of lisp programming.

C-c C-a (C-toggle-auto-state) : Will automatically put new line affter you press {, ) etc

Very trivial to use M-x customize
Also emacs will look for these files in order at startup. The first one found is used.
1) .emacs.elc - byte compile version of the lisp startup file.
2) .emacs.el - More formal name of the .emacs file
3) .emacs

If ever there is a problem with your .emacs file, try running emacs with -q option, to skip loading .emacs file.
Comments in lisp begin with double semicolon ;;

We'll now start writing our own emacs file. As far as possible, try to manually edit.

M-x load-file : to reload the .emacs file

Increase text size = C-x C-+
