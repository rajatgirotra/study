#!/usr/bin/env python3

## reading a file

## Open a file for reading
f = open('26.formatting.reading.txt','r')

## Do the read . Calling read with no arguents will read the entire file. Otherwise pass an argument which will read only as many bytes as you said. If EOF is reached, you get back
## an empty string ''.
x = f.read()
print(x)

y  = f.read()
print(len(y))  ## should be an empty string


## Otherwise use the readline function to read line by line. the line read also has the newline character appended to it.
f = open('26.formatting.reading.txt', 'r')
while True:
   x = f.readline()
   if(len(x) == 0) :
      break;
   print('Line:', x[0:len(x) - 1])


## Better still, use readlines(), which returns you a list of all the lines in the file.
## Also if you give it an argument, it will read only those many bytes (and a few more to read the whole line) and return you the list
## this way you can read the file in chunks or blocks to be more effecient than reading the whole file at once in memory.
print()
print('Using file.readlines()')
f = open('26.formatting.reading.txt', 'r')
x = f.readlines(200)
for line in x:
   print('Line: ', line[0:len(line)-1])


print()
print()
print('Iterating over the file now')
## Another approach and often the best is to iterate over the file object. Each iteration retuns you a line in the file.
f = open('26.formatting.reading.txt', 'r')
for line in f:
   print('Line: ', line[0:len(line)-1])

## Writing to a file
## Use f.write(string) function. Note anything you write to a file must be converted to a string, So use str() and repr() functions as needed.
## write() returns the no. of bytes written to the file.

f = open('newTempFile.txt', 'w')
x = f.write('This is the first line.');
print('Bytes written:', x)

## You should be familiar with the seek(offset, from_what) and the tell() functions to get the current location in the file.
print(f.tell())
#f.seek(0, 0)
print(f.tell())
x = f.write('first line.\n');

f.close() ## must close the file to free resources.

## A new keyword in python in "with". You can use this to make sure file objects are closed when done working with them or in the face of an exception.
## this way there will be no resource or memory leak. Its a bit wierd (the syntax), but you should get used to it.

with open('26.formatting.reading.txt', 'r') as f:
   for line in f:
      print('Line: ', line[0:len(line)-1])

print(f.closed)
