#!/usr/bin/env python3

def ask_q(prompt, retries=4, complaint="Yes or no, please..!!"):
    while (retries > 0):
        isOK = input(prompt)
        if (isOK.lower() == 'y' or isOK.lower() == "yes"):
            return True
        elif(isOK.lower() == 'n' or isOK.lower() == "no"):
            return False
        
        retries -= 1
        if (retries > 0):
            print(complaint)
            
    # if control reaches here, raise error
    raise IOError('incorrect answer to question ' + prompt)
    

def foo(name, namelist=None):
    if(namelist is None):
        namelist=[]
    namelist.append(name)
    return namelist


try:
    x = ask_q("Is the weather good today? : ")
    print('First : ' + str(x))
except IOError as e:
    print('First : ' + str(e))

try:
    x = ask_q("Is the weather good today? : ")
    print('Second : ' + str(x))
except IOError as e:
    print('Second : ' + str(e))

print(foo("A"))
print(foo("B"))
print(foo("C"))
print(foo("D"))

n = 10
print(list(range(n)))

def cheeseshop(kind, *args, **map):
    print("--Do you have any ", kind, "?")
    print("-- I am sorry, we are all out of", kind)
    for arg in args:
        print("     ", arg)
    keys = sorted(map.keys())
    for key in keys:
        print(key, ":", map[key])
    print(list(map.keys()))
    print("Number of variable arguments", len(args))
    print(args[0], args[1])

def foo2(*args, prompt):
    for arg in args:
        print(arg)
    print("prompt", prompt)
    print(prompt.join(args))

cheeseshop("Hamburger", "specially during christmas", "and during easter",
           client="Rajat", sketch = "ABCD", sales = "Vidhu")

map = {}
map['jack'] = 1234
map['mark'] = 8197
map['mike'] = 9872
map['alex'] = -987

print(map)
del map['jack']
print(map)

if ('alex' in map):
    print("Yes")
if('jonathan' not in map):
    print("Yes")

for k,v in map.items():
    print(k, ":", v)
    

foo2("A","B","C","D",prompt="/")

# list can be converted to tuple very easily
l = [3, 12]
print(list(range(*l)))

def make_lambda(n):
    return lambda x : x + n

f = make_lambda(100)
print(f(0))
print(f(1))
print(f(2))

# function returning a function, can be used when the outer function needs to be tied
# to a list of known parameters.
def outer_function(*keys):
    """ Outer function documentation.
Used to bring together key/value pairs"""
    def inner_function(*values):
        i = 0
        resultList = []
        for key in keys:
            pair = key + "=" + str(values[i])
            resultList.append(pair)
            i += 1
        return resultList
    return inner_function

a = outer_function("A", "B", "C", "D")
print(a(1, 2, 3, 4))

print(outer_function.__doc__)

tup = 4, 5, 6
print(tup)

x,y,z, = tup
print(x,y,z)

listA = ["A", "B", "C"]
listB = [1, 2, 3]
for x,y in zip(listA, listB):
    print(x, y)

tup = tuple('string')
print(tup)

tup = 4, 5, (6, 7)
print(tup)
x, y, (a, b) = tup
print(x, y, a, b)

l = sorted(set('hereicome'))
print(l)
for i,value in enumerate(l):
    print(i, value)
print(list(reversed(l)))

l = [1,2]
l.append(3)
x = l.pop()
print(l.pop(0))
print(l.pop(0))
