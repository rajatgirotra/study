#!/usr/bin/env python3

## Here we will look at default aruguments to functions. Pay attention as there are many varities available.

## First - Very easy - DEFAULT ARGUMENTS. We'll write a simple function that asks a question to the user. The answer should be yes or no. If anything else,
## the question should be repeated as many times as the retries argument is set. This argument will be have a default value. The first mandatory argument
## will the be question itself - a simple string. A third default argument will be the complaint to display if the user does not correctly answer the question.

def ask_ok (prompt, retries = 4, complaint = 'Yes or no, please!!') :
   isOK = input(prompt)
   if isOK in ('y', 'yes', 'Yes', 'YES', 'Y') :
      return True;

   if isOK in ('n', 'no', 'No', 'NO', 'N') :
      return False;

   retries = retries - 1

   if(retries < 0) :
     raise IOError ('refusing user')

   print(complaint);

## All of the following are valid ways to call the ask_ok function
ask_ok("WHat is your age?");
ask_ok("WHat is your age?", 2);
ask_ok("WHat is your age?", 2, "No Complaint");
ask_ok(prompt = "What is your age?")
ask_ok(prompt = "What is your age?", complaint = "No Complaint")


## Now lets see something a bit strange
def foo(name, nameList = []) :
   nameList.append(name)
   return nameList

print(foo("Vidhu"))
print(foo("Rajat"))
print(foo("Shweta"))
print(foo("Jitin"))

## Actually default arguments are only evaluated once. So they retain their value between multiple function calls. 
## much like C++ static variables in functions. To get past this, you can do.

def foo2(name, nameList=None) :
   if (nameList is None) :
      nameList = []

   nameList.append(name)
   return nameList


print(foo2("Vidhu"))
print(foo2("Rajat"))
print(foo2("Shweta"))
print(foo2("Jitin"))

## Lets see some other types of parameters
## *arguments will hold a tuple of values
## **keywords will hold a list of key=value pairs
## See carefully how to call such a function and how to use these parameters.
def cheeseshop(kind, *arguments, **keywords):
   print("-- Do you have any", kind, "?")
   print("-- I'm sorry, we're all out of", kind)
   for arg in arguments:
      print(arg)
   print("-" * 40)
   keys = sorted(keywords.keys())
   for kw in keys:
      print(kw, ":", keywords[kw])

cheeseshop("Hamburger", "Specially around easter", "We are all finished pretty early sir",
           shopkeeper = "Rajat Girotra",
           client = "Vidhu Girotra",
           sketch = "ABCD")


## Function with variable number of arguments
def foo3(*varArgs) :
   print("No of arguments:", len(varArgs))
   for arg in varArgs:
      print(arg)


foo3('one');
foo3('one', 2, 'three');

## Another example, where the variable parameter holder is the first parameter
## the parameters after that must be keyword arguments, i.e. arguments with a default value.
def foo4(*varArg, sep = "/"):
   return sep.join(varArg) ## See how the join function of string class works

print(foo4('earth', 'mars', 'jupiter'))


## Sometimes you require to unpack the tuple arguments. i.e. let say you have a list [3, 10], but you want a list of numbers from 3 to 10.
## you can do this using the * operator
args = [3, 12]
print(list(range(*args))) ## *args gives a range from 3 to 12, list converts it to a list and print prints it.

