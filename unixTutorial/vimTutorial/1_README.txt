1) how can you print a short message at the bottom of the vim screen
:echo "Hello World!"
or 
:echom "Hello again, World!"

The difference is that "echom" will also additionally store the message in the messages buffer which you can view by using ":messages". This is useful if you want to debug your own big vimrc script.
Use ":3messages to view only last 3 messages", use ":messages clear" to clear all messages etc. Use ":help :messages" to see more help on it.

-------------------------------------------------------------------------------------------------------------------------

2) Modify your vimrc to print an ascii cat "(>^.^<)" when you enter vim.
:echo "(>^.^<)"

-------------------------------------------------------------------------------------------------------------------------
3) how do you set line number, unset set, toggle it, check the current value, and set to default value
set number
set nonumber
set number!
set number?
set number&

Read also about
set relativenumber
set numberwidth=5
set wrap
set shiftround
set matchtime 

and set your vimrc accordingly

-------------------------------------------------------------------------------------------------------------------------
4) How do you set a basic mapping
:map <new_Key> <action>
By default, :map will set the mapping in all vim modes - normal, insert, visual etc. To selectively set a mapping for a given mode, use
:nmap, :vmap, :imap etc. :unmap, :nunmap, :vunmap, :iunmap etc are used to remove the mappings

create a mapping to move the current line up or down with one key stroke
:map - ddp
:map _ kddpk

create a mapping for key \ to delete the current line in normal mode and to Uppercase the word selected in Visual mode
:nmap \ dd
:vmap \ U

create a mapping for key <c-d> to delete the current line in insert mode
:imap <c-d> <esc>ddi

-------------------------------------------------------------------------------------------------------------------------
5) What is the problem with mapping commands like :map, :nmap, :vmap etc? --> They take other mapping defined also into account. This can lead to recursive mappings which is pure evil. Also if you install a plugin, it could create a conflicting mapping. So the rule of THUMB IS TO AVOID THESE RECURSIVE MAPPINGS. example:

:map \ dd
:map - \

using - will delete the current line

Also

:nmap dd O<esc>jddk
This is also a recursive mapping.

vim provides *noremap versions for all *map versions like :nnoremap, :vnoremap, :inoremap etc. nore means no recursion. Always use these. go back and change your vimrc accordingly

-------------------------------------------------------------------------------------------------------------------------
6) mapleader and maplocalleader
vim mapping commands allow multiple keystrokes also to be mapped to some action, in addition to just using a single keystroke. When using multiple keystrokes, the first keystroke is called the prefix key or also the leader. this prefix actually activates your mappings. the advantage is that you do not overshadow any functions that a single keystroke may be binded to by default. There are many keys which you will hardly ever used when using vim. Once such key is the "-" which can be used as the prefix or the mapleader

Similarly you have maplocalleader which can also be defined in addition to the mapleader. maplocalleader only takes effects for certain file types like python, c/c++, java etc. We'll see later how to use maplocalleader. in your vimrc define a leader key and then re-define all mappings to use the leader key

Mapleader and maplocalleader can work in all modes: normal, visual, insert etc.

Useful commands:

:let mapleader --> will show you if mapleader is actually set
:echo mapleader --> will show you the actual value (key) of the mapleader
:imap --> will show you all the insert mode mappings
-------------------------------------------------------------------------------------------------------------------------

7) Create a mapping for surrounding the word under the cursor with double quotes and single quotes
:nnoremap <leader>" viw<esc>a"<esc>bi"<esc>lel
:nnoremap <leader>' viw<esc>a'<esc>bi'<esc>lel

a command like
:nnoremap <buffer> <leader>x dd
only applies the mapping the buffer in which the mapping was defined. However instead of using <leader> for applying a mapping to 
buffers of a specified type, use localleader instead of leader. we'll see how we can use localleader in a bit. Also local buffer mappings
are assumed more specific and override any similar mappings at a wider scope.

Also there are many options that can also apply locally only to a buffer, like

setlocal nowrap
setlocal nonumber

see the relevant help to find out if the option can be applied locally.
-------------------------------------------------------------------------------------------------------------------------

8) What are autocommand?
These are commands that get run automatically when some events happen in vim. Vim defines a number of different events like
Buffer Open, Buffer saved, File Created, etc etc. You can define your own commands to be executed when these events happen. Syntax is very simple

:autocmd Event1,Event2,Event3 <some_filter_pattern> <commads_to_execute>

example: create an autocmd not to set wrap on vimrc file

:autocmd BufNewFile,BufRead .vimrc setlocal nowrap

run ":help autocmd-events" to see list of all events
-------------------------------------------------------------------------------------------------------------------------

9) FileType event and filetype option
filetype on --> will enable vim to detect the filetype (by looking at the file extension and sometimes by looking at the file contents)
this will also fire the FileType event which can be used to set options or run command using autocmd above. The code in the $VIMRUNTIME/filetype.vim
is run to detect the filetype

filetype plugin on --> will enable loading of any plugin file for a recognized fileytpe. this plugin file will basically set many options which
would be local to the buffer for these filetypes. So basically your global vimrc settings might get overriden. if you still want to retain your global settings, create a .vim/after/ftplugin/cpp.vim and create your own setlocal options here. filetype plugin on will load the $VIMRUNTIME/plugin/cpp.vim file

filetype indent on --> same as plugin but used for indentation. will load the $VIMRUNTIME/indent/cpp.vim

:filetype will show what all is on and off
-------------------------------------------------------------------------------------------------------------------------

10) By now you should know that mappings, abbreviations and autocmd can be set locally using <buffer>
Write an autocmd for python filetype where if you type "iff" it should expand to "if:" with the cursor between if and :

autocmd FileType python :iabbrev iff if :<left>
-------------------------------------------------------------------------------------------------------------------------

11) What are augroups and why we need them. --> Lets say you have a single autocmd defined like
autocmd BufWrite * :echom "Written"
then everytime the vimrc is sourced, the same autocmd will be registered again. ie every file save will log two messages.. this is a problem
to get around it. vim decided to group autocmd in a group called augroup. augroup can have a name. and there can be multiple augroups with the 
same name. autocmds in multiple augrups with the same name are merged together. and there is a way to clear all autocmds in an augroup by using the
syntax "autocmd!". Let's see an example:

:augroup testgroup
: autocmd!
: autocmd BufWrite * :echom "File Written"
:augroup END
-------------------------------------------------------------------------------------------------------------------------

12) What is onoremap --> There are many ways to modify text in vim like "d" (to delete), "y" (to yank/copy), "c" (to change) text.
These commands take a second argument called motion. The motion tells what to delete example:

yy --> will copy the line
y$ --> will copy the line from the current cursor to the end of the line
dw --> will delete the a word
ci( --> means change inside parenthesis
yt, --> means yank until comma

vim allows you to create new motions which can be used with the existing commands using the onoremap mapping
example:

:onoremap p i(

will create a mapping such that dp --> will work like delete inside paranthesis. Try it out. Run the command above and then try on the
text below.

person.get_pets(type="cat", fluffy=True)


