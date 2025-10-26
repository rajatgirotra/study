List, Dictionary, tables
=======================


dictionary
----------
Just a mapping between a key list and a value list. created using the ! operator. Ex: keys!value

q)10 20 30! 1 2 3 / simple dict
q)(10;`hello;0b) : (1;2;3) / key or value list can be non-homogenous
q)d: 10 20 30! 1 2 3 / simple dict
q)key d / get keys as list
q)value d / get values as list
q)d[10] / lookup single value. If duplicate keys exist in the dictionary, the first value is retruned.
q)d[10 20] / lookup multiple values or d[(10;20)]
q)count d / get dict size
q)()!() / empty dict
q)`symbol$():`float$() / empty dict of symbol to floats
q)(enlist `x)!(enlist 42) / must convert a single atom to a list.
q)d?2 / ? is the find operator which reverese the mapping. i.e you are doing a value-key mapping
q)d?(2;1) 

Remember that q does not enforce keys to be unique. and by default, lookup are done sequentially. So if you are sure your dictionary has unique keys. you can use the "u#" attribute while creating your dict. this way dict will behave like a hash table and lookup will also be faster.

q)d: (`u#10 20 30)!`a`b`c
q)d[10]

if an item is not found null is returned. 
q)null d[1] / will return 1b
q)null d[10] / will return 0b

dictionaries can be added (similar to python). Duplicate keys have their value overwritten:
q)d:`a`b`c!1 2 3
q)e:`x`y`z!10 20 30
q)f:(enlist `x)!(enlist 100)
q)d+e+f

q)d:`a`b`c`a!10 20 30 40 / dict with duplicate key `a.
q)where d=`a / return 10 40

q) d:(`a`b`; `c`d`e; (enlist `f))!10 20 30 / heterogeneous list where keys are lists themselves.
/ REMEMBER. Never have dictionaries with heterogenous keys or values as there is some limitation on lookups and reverse lookups.

q)d:`a`b`c!10 20 30
q)d[`a]: 100 / updates a to 100
q)d[`x]: 200 / will insert. that's why this operation is called upsert (i.e. update or insert)
q)d[-1]: 1 / will give error as key type is not a symbol
q)d[`a]: `hello / will give error as value is not integer

q)/use the Take operator (#) to get a sub dictionary
q)`a`b#d / keys followed by # followed by dictionary variable

q) /remove elements using _ operator
q)`a`b _d / keys followed by _ followed by dictionary variable
q)`a`b cut d / cut is just a synonym for _

q) /empty the dictionary
q) (key d) _ d / (key d) will return the keys as list and _d will delete those entires.

if you apply a unary function to a dictionary it will be applied to its value list
if you apply a binary function to two dictionaries it will be applied to its value list. For keys which only exist in one dictionary, the function wont be applied and the value will be returned as such.

q)d:`a`b`c:1 2 3
q)d1:`a`b`c`d:1 2 3 4
q)d+d1

When you use the join operator i.e. comma, the dict on the right side takes precedence.
when you coalesce two dict, behavior is same as , except that null values in the right side are overwritten from the left side. the coalesce operator is ^

Tables
------
If you have dictionary where key is a list of symbols and each value itself is a list, you basically get a table in q.

q) travelers:`name`iq!(`Dent`Beeblebrox`Prefect;42 98 126)
q) travelers[`iq]
q) travelers[`iq][1] / returns 98
q) travelers[`iq;1] / also returns 98. just another way to use index operator. it's called "indexing at depth."

/ think of travelers[`iq;1] as accessing a 2d array. First dimension is symbol representing the column name, 2nd dimension is index for that column. If you don't specify anything for the 1st dimension, and only specify an index for 2nd dimension. you basically get a slice of the table. ie. all rows at that index.
q) travelers[;1]

q) / flip is very handy to calculate the transpose of a dictionary or list. It allows you to also reverse the indices used during "indexing at depth". see example below.
q)dc:`c1`c2!(`a`b`c; 10 20 30)
q)dc[`c2:2]
q)t: flip dc
q)t[2;`c2]

the transpose of a column dictionary gives you a table.
you either you create a table using a column dict and call flip or you just create using the table syntax.
q) v:flip `name`iq!(`Dent`Beeblebrox`Prefect;98 42 126) / first way
q) v:([]name:`Dent`Beeblebrox`Prefect; iq: 98 42 126)

q)tbl[0] / will give you all rows at index 0. i.e. a record in the table
q)tbl[;`col]] / will give you the column 'col'
q)tbl[`col]] / q allows you to omit the leading ; when the second index is a column name
q)tbl.col / q allows you to use dot notation also, just like for dictionaries. Don't use dot notation at all. Period.

q)c1:`Dent`Beeblebrox`Prefect
q)c2:98 42 126
q)([] c1; c2) / creating a table from lists. column names will be c1 and c2.
/if you don't explicitly specify column names, q will create them on a best-effort basis. like q can give column names as x, y, z etc.

q) cols tbl / list columns of table 'tbl'
q) meta tbl / display metadata for each column, which shows type of column, domain of any foreign key or link columns and any attributes associated with the column.
q) tables `. / list all the tables in the root namespace
q) count tbl / return row count for table
q) value tbl[0] / return a list of all fields in the row at index 0.

q) empty_table:([] name: `symbol$(); iq: `long$())
q) empty_table:([] name:0#`; iq:0#0) / shorter form using the take operator #

q defines a set of functions and constructs for manipulating q tables. These are part of q-SQL because they resemble some of the SQL constructs.

q) select name,iq from tbl / select query
q) select from tbl / same as above
q) select NAME:name, Intellect:iq from tbl / give new names to the columns

q) update iq:iq%100 from t / simple update statement. iq is the col to update and iq%100 is the new value

Keyed tables
-------------
Since many times you want your table to have some primary key used for retrieval, q implements this using a keyed table. internally q separates the keys column from the rest of the value columns and internally builds a dictionary mapping each row of key table to each row of values table. so a Keyed table in q is actually a dictionary of type 99h.

q) v:([]name:`Dent`Beeblebrox`Prefect; iq: 98 42 126) / values table
q) k:flip (enlist `eid)!enlist 1001 1002 1003 / keys table

to create a keyed table manually, you place the keys inside the [] when creating your table
q)kt:([eid: 1001+til 4] name: `Rajat`Vidhu`Myra`Viraj; iq: 10 20 30 40)
