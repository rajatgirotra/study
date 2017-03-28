Start a new screen session with

screen -S <sessionName>, eg: screen -S rajat

List screen sessions: screen -ls

Screen attach options
screen -d -r --> reattach to a session. -d means deattach if necessary
screen -d -R --> reattach to a session. -d means deattach if necessary. If session does not exist, then create it.
screen -d -RR --> reattach to a session. -d means deattach if necessary. If session does not exist, then create it. If multiple 
                  sessions exist, attach to the first session.
screen -D -r --> reattach to a session. -D means deattach and logout if necessary.
screen -D -R --> reattach to a session. -D means deattach and logout if necessary. Create session if necessary. This is the best option. Always use it
                 to attach to a detached screen.

screen -h <num> - To set history scrollback buffer to be num lines high

screen -f/-fn/-fa - To set flow control on, off or automatic mode.

screen -U --> set default encoding to screen to UTF-8

screen -t <titlename> --> to set the title of screen window.

screen -v --> print screen version number.

screen -wipe - clear all destroyed/dead sessions.

Commands: Screen has many commands that you can execute. If you have all commands in a file. you can execute
"source <fileName>" which will execute commands one by one.

If you are already inside a screen session, you can say "C-a :", which prompts you for a command.
Many of the commands start with "def"

C-a c (or C-a C-c) - creates a new screen window
C-a C-c - clear screen.
C-a '  - will ask for window name to switch.
C-a " - display all windows and choose one which you are interested in.
C-a 0-9 - Will select window 0 thru 9.
C-a C-a - quickly toggle between two windows.
C-a a - insert control-a into file.
C-a A - set title of window
C-a C-d - detach from screen
C-a F - resize to FIT
C-a i - show info on the current window
C-a k - kill current window
C-a m - repeat the last msg
C-a SPC or C-a n or C-a C-n - switch to next window
C-a N - show current window name and number
C-a BACKSPACE or C-a C-p or C-a p - switch to previous window
C-a \ - kill all windows and exit screen
C-a : - Enter command line mode to enter a screen command.

Region commands:
C-a Q - Delete all regions but current one (need to find out what a region is)
C-a S - Split the current region into multiple ones.

Put in your .screenrc
hardstatus alwayslastline '%{= G}[ %{G}%H %{g}][%= %{= w}%?%-Lw%?%{= R}%n*%f %t%?%{= R}(%u)%?%{= w}%+Lw%?%= %{= g}][ %{y}Load: %l %{g}][%{B}%Y-%m-%d %{W}%c:%s %{g}]'

