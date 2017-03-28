>>> a = ['spam', 'eggs', 100, 1234]
>>> a
['spam', 'eggs', 100, 1234]
>>> a[0]
'spam'
>>> a[1]
'eggs'
>>> a[2]
100
>>> a[3]
1234


>>> a[2] = a[2] + 34  --> You can modify list elements.
>>> a
['spam', 'eggs', 134, 1234]


>>> a[:2]  --> Access is similar to that in case of strings.
['spam', 'eggs']
>>> a[2:]
[134, 1234]
>>> a[:]
['spam', 'eggs', 134, 1234]


>>> 3*a[3]  --> Can also mutiply lists just like strings
3702
>>> 3*a[:2]
['spam', 'eggs', 'spam', 'eggs', 'spam', 'eggs']
>>> ['spam'] * 6
['spam', 'spam', 'spam', 'spam', 'spam', 'spam']


>>> a.append('right')  --> Can modify the size of lists.
>>> a
['spam', 'eggs', 134, 1234, 'right']

>>> a[1:2] = ['a','b']  --> Change elements starting from index 1 to index 1 (1 less than index 2 is index 1)
>>> a
['spam', 'a', 'b', 134, 1234, 'right']

>>> a[1:2] = ['c']
>>> a
['spam', 'c', 'b', 134, 1234, 'right']

>>> a[1:3] = ['c']
>>> a
['spam', 'c', 134, 1234, 'right']
>>> a[:0] = a
>>> a
['spam', 'c', 134, 1234, 'right', 'spam', 'c', 134, 1234, 'right']
>>> a
['spam', 'c', 134, 1234, 'right', 'spam', 'c', 134, 1234, 'right']
>>> a = a * 2
>>> a
['spam', 'c', 134, 1234, 'right', 'spam', 'c', 134, 1234, 'right', 'spam', 'c', 134, 1234, 'right', 'spam', 'c', 134, 1234, 'right']


>>> len(a)  --> Length of a list just like that of string
20
>>> a[0:len(a)] = ''
>>>
>>> a
[]
>>>


>>> q = [2,'b']   ---> Lists can also be nested.
>>> p = [1, q, 3]
>>> p
[1, [2, 'b'], 3]
>>> p[1].append('c')
>>> p
[1, [2, 'b', 'c'], 3]
>>> p.append('d')
>>> p
[1, [2, 'b', 'c'], 3, 'd']

