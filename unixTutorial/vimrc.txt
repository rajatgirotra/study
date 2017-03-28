" vimrc configuration file.
" tailored for C++ development, but useful for other languages too
" Author: Rajat Girotra

"load plugins first
execute pathogen#infect()

set exrc               "load project specific vimrc if available
set secure             "prevent some commands from being run from project specific vimrc
set nocompatible       "we don't need compatibility with plain vi
set nonumber           "we dont need to see line numbers. We'll enable ruler instead
set ruler              "enable ruler. Use default ruler format
set laststatus=2       "always enable statusbar"
set wrap               "wrap to fit window width.
set t_Co=256           "force vim into 256 color mode.
set encoding=utf-8     "enable unicode in vim.
set tabstop=4          "tab is 4 columns
set softtabstop=4      "ditto
set expandtab          "no tabs in my code.
set shiftwidth=4       "number of columns to auto indent
set autoindent         "autoindent based on previous line
set showmatch          "match corresponding brace while editing
set relativenumber     "show numbers relative to current line.
set hidden             "hide the current buffer on close.
filetype on            "enable filetype detection using $VIMRUNTIME/filetypes.vim
filetype plugin  on    "enable filetype plugins if available
filetype indent  on    "enable auto filetype indentation if available.
syntax enable          "enable default vim syntax highlighting for the particular file type.
set ignorecase         "ignore case while searching
set smartcase          "only ignore-case when i search with all lower case
set hlsearch           "highlight my searches
set incsearch          "show patterns as i type my search string
set colorcolumn=110    "for setting column 110 to a different color. Try not to write code that goes past 110 characters.
highlight ColorColumn ctermbg=53

let mapleader="-"
"mappings
"convert the word under the cursor to upper case.
noremap <leader>u <esc>gUaw<esc>
"convert the word under the cursor to lower case.
noremap <leader>l <esc>guaw<esc>
"quickly open your vimrc when in normal mode.
nnoremap <leader>ev :vsplit $MYVIMRC<cr>
"quickly source your vimrc when in normal mode.
nnoremap <leader>sv :source $MYVIMRC<cr>
"double quote the word under the cursor
nnoremap <leader>" viw<esc>a"<esc>hbi"<esc>lel
"open file under the cursor in a new tab.
nnoremap gf :find <cfile><cr>
"move to next or previous tabs
nnoremap <Right> :bn<cr>
inoremap <Right> <esc>:bn<cr>
nnoremap <Left> :bp<cr>
inoremap <Left> <esc>:bp<cr>
"close the current tab
nnoremap <F4> :bdelete<cr>
inoremap <F4> <esc>:bdelete<cr>
"go to normal mode quickly
inoremap jk <esc>
"also disable esc so that you get used to jk
"inoremap <esc> <nop>

"vim-airline specific settings to view tabline.
" Enable the list of buffers
let g:airline#extensions#tabline#enabled = 1
" Show just the filename
let g:airline#extensions#tabline#fnamemod = ':t'
"Display only filename in the statusline
let g:airline_section_c = '%t'

"vim-CtrlP specific settings
"always start CtrlP in mixed mode: ie fileMode+MRUMode+BufferMode
let g:ctrlp_cmd='CtrlPMixed'
"By default, search by filename. Can use <c-d> to toggle anytime
let g:ctrlp_by_filename = 1
"always search with regular expression mode on. Use <c-g> to toggle this anytime.
let g:ctrlp_regexp = 1
"set the window position, etc for CtrlP
let g:ctrlp_match_window = 'bottom,order:btt,min:1,max:10,results:10'
"set CtrlP working path mode
let g:ctrlp_working_path_mode = 'ra'
"ignore unnecessary paths
let g:ctrlp_custom_ignore = '\v[\/]\.(git|hg|svn)$'
"the project specific vimrc sets a local cache directory. So we dont need to destroy it on session exit.
let g:ctrlp_clear_cache_on_exit = 0
"scan all files.
let g:ctrlp_max_files = 0
"open new files in the current window.
let g:ctrlp_open_new_file = 'r'
"open multiple files as hidden buffers
let g:ctrlp_open_multiple_files = 'ri'
"follow synbolic links
let g:ctrlp_follow_symlinks = 1
inoremap <F8> <esc>:CtrlPMixed<cr>
nnoremap <F8> :CtrlPMixed<cr>
