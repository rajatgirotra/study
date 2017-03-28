#!/usr/bin/env python3

## See how to use the if loop

x = int(input('Enter an integer: '))

if (x < 0) :
   x = 0
   print('Negative number changed to zero')
elif ( x == 1) :
   print('You enetered one')
elif ( x == 0 ) :
   print('You entered zero')
else :
 print('You entered a positive value more than 1');


print(x)


## Use of for loop : Very different from what it is in C/C++, Similar to what it is in bash where you iterator over a sequence.
## Here you can also iterate over any sequence (list or string) in the order the elements are places in the list or string.
## for iterating over integers, use the range() function.

words = [ 'I', 'am', 'Scooby', 'Doo' ]

for w in words :  ## Note the mandatory colon : just like you saw in while loop and the if statement.
   print(w, len(w))

## If you also want to make a change to the list as you iterate over it, it is recommended that you first make a copy of the list and then iterate over the copy. 

for w in words[:] : ## words[:] gives you a copy of the list 
   if ( len(w) > 3 ) :
      words.insert(0, w) ## Make change to the actual list

print(words)



## Lets see the range function now.
for i in range(5) :
   print (i, end = ', ')

print ('')
for i in range(4, 12) :
   print (i, end = ', ')

print ('')

for i in range(10, 100, 20) : ## Print from 10 to 100 with a step of 20.
   print (i, end = ', ')

print('')

## guess what range(4, 4) print ??? Nothing. cause it starts at 4 & has to go till 3. So Nothing.
for i in range(4,4) : 
   print (i, end = ', ')

print('')



## So now you can iterate over the list using indexes like this: First one you already saw: "for w in words : "
for index in range(len(words)) :
  print(words[index], end = ' ' )

print('')


## Very important stuff to follow
## if you say
print(range(10))
## it returns prints "range(0, 10)". Basically, range() returns an object which is iterable. I.e. functions and expressions can use it to iterate
## over it until the supply has exhausted. So you can say that the "for" statement is an iterator which iterates over the object returned by range()
## similarly we have another function called list(), which creates a list from an iterable.

newList = list(range(10))
print(newList)




## No need to tell you about break and continue keywords. They are the same as in C/C++. More there is another important thing here, the else keyword.
## Normally you have only used it with if statements, but in python you can also use it with for and while... How ?? When the for loop has exhausted or the while
## loop returns false, then the statements in the else part are executed.

## Lets write a program to print the prime numbers from 1 to 10. For each number, we will try to divide it by all numbers less than that. If the remainder is zero,
## Then it is not a prime number.

for a in range(2, 10) : ## First range is from two to ten as we know one is a unique number
   for b in range (2, a) : ## We divide a by each number less than a
      if ( a % b == 0) :
         print (a, 'equals', b, '*', a//b)
         break
   else: ## Note this else clause for the "for" loop
      print (a, 'is a prime number')


## Another keyword is pass. This is basically a no-operation keyword. When encountered, it does nothing. 
## Uses:
#while True:
   #pass ## this will create an indefinite loop.

class MyEmptyClass:
   pass ## This will create an empty/minimal class.


## Or lets say you define a function but dont yet implement the body. The also you can use pass.
def initlog(*args) :
   pass ## Remember to implement later..!!


