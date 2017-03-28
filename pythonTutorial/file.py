#!/usr/bin/env python3

# get a file object
try :
    f = open("diary1.txt",mode='r+')
    # go to end of file.
    print(f.tell())
    f.seek(0,2)
    print(f.tell())    
    f.write('Python writing line 1\n')
    f.write('Python writing line 2\n')
except (IOError, OSError) as e:
    print(e)
    print(e.args)
    

