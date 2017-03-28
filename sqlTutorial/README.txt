1] SQL is Structured Query Language
2] It is an ANSI standard
3] most RDBMS support SQL put provide their own extensions. For example: PL/SQL for Oracle & T-SQL in MS SQL Server.
4] It is not case - sensitive.
5] You can divide SQL into parts : DML (Data Manipulation Language) and DDL ( Data Definition Language)
DML consists of all sql statements that are used to modify/alter the data in the database tables: Eg:
    * SELECT - extracts data from a database
    * UPDATE - updates data in a database
    * DELETE - deletes data from a database
    * INSERT INTO - inserts new data into a database

DDL consists of all sql statements that are used to create and delete databases, create indexes, specify links between tables. Eg:
    * CREATE DATABASE - creates a new database
    * ALTER DATABASE - modifies a database
    * CREATE TABLE - creates a new table
    * ALTER TABLE - modifies a table
    * DROP TABLE - deletes a table
    * CREATE INDEX - creates an index (search key)
    * DROP INDEX - deletes an index


SQL Statements
--------------

select
******
SELECT column_name(s)
FROM table_name

eg: 
SELECT * FROM persons
SELECT LastName,FirstName FROM Persons

select distinct
***************
SELECT DISTINCT column_name(s)
FROM table_name

eg:
SELECT DISTINCT City FROM Persons

where
*****
SELECT column_name(s)
FROM table_name
WHERE column_name operator value

eg:
SELECT * FROM Persons WHERE City='New York'

SELECT * FROM Persons WHERE FirstName='Tove'  --> Correct
SELECT * FROM Persons WHERE FirstName=Tove  --> Incorrect (must quote text values, sometimes double quotes might also work)

SELECT * FROM Persons WHERE Year=1965   --> Correct
SELECT * FROM Persons WHERE Year='1965' --> Incorrect (numeric values need not be quoted).

SELECT * FROM Persons WHERE FirstName='Tove' AND LastName='Svendson'  --> Note the AND
SELECT * FROM Persons WHERE LastName='Svendson'  AND (FirstName='Tove' OR FirstName='Ola')  --> Note AND & OR.

= 		Equal
<> or != 	Not equal
> 		Greater than
< 		Less than
>=	 	Greater than or equal
<=	 	Less than or equal
BETWEEN 	Between an inclusive range
LIKE	 	Search for a pattern
NOT LIKE   Opposite of LIKE
IN 		If you know the exact value you want to return for at least one of the columns

SELECT * FROM Persons WHERE CITY LIKE '%tav%'  --> i.e. beginning with anything followed by "tav" and then anything.
SELECT * FROM Persons WHERE CITY NOT LIKE '%tav%'

Other wildcards that can be used with LIKE:
% 		A substitute for zero or more characters
_ 		A substitute for exactly one character
[charlist] 	Any single character in charlist
[^charlist]	Any single character not in charlist
or
[!charlist]

SELECT column_name(s)
FROM table_name
WHERE column_name IN (value1,value2,...)

SELECT column_name(s)
FROM table_name
WHERE column_name
[NOT] BETWEEN value1 AND value2

eg:
SELECT * FROM Persons
WHERE LastName
BETWEEN 'Hansen' AND 'Pettersen'

order by
********
SELECT column_name(s)
FROM table_name
ORDER BY column_name(s) ASC|DESC   --> Used to sort the result set.

SELECT * FROM Persons ORDER BY LastName 


insert into
***********
2 forms are avilable. In the first firm you only specify the values that are to be inserted.
in the second form, you can specify the colomns that you want to populate, leaving the others blank.

INSERT INTO table_name
VALUES (value1, value2, value3,...)
	
	OR
	
INSERT INTO table_name (column1, column2, column3,...)
VALUES (value1, value2, value3,...)


INSERT INTO Persons 
VALUES (4,'Nilsen', 'Johan', 'Bakken 2', 'Stavanger')
             OR
INSERT INTO Persons (P_Id, LastName, FirstName)
VALUES (5, 'Tjessem', 'Jakob')


update
******
UPDATE table_name
SET column1=value, column2=value2,...
WHERE some_column=some_value   --> Used to update colomns in an existing database

UPDATE Persons
set LastName='Girotra', Age=27
WHERE FirstName='Rajat'


delete
******
DELETE FROM table_name
WHERE some_column=some_value  --> Used to delete entries from a database

DELETE FROM Persons
WHERE LastName='Tjessem' AND FirstName='Jakob'

DELETE FROM Persons  --> Will delete all rows but keep the database, structures, indexed etc intact
or DELETE * FROM Persons


top  --> To return only a specified no. of rows.
***

MS SQL Server --> SELECT TOP number|percent columns_name(s) FROM table_name
Eg:
SELECT TOP 2 * FROM Persons
SELECT TOP 50 PERCENT LastName FROM Persons

MySQL   -->    SELECT column_name(s) FROM table_name
	       LIMIT number
Eg:
SELECT * FROM Persons
LIMIT 5

Oracle  --> SELECT column_name(s) FROM table_name WHERE ROWNUM <= number	
eg:
SELECT * FROM Persons
WHERE ROWNUM <= 5


alias 
*****
You can give a table or a column another name by using an alias. This can be a good thing to do if
you have very long or complex table names or column names.

An alias name could be anything, but usually it is short.

SQL Alias Syntax for Tables

SELECT column_name(s)
FROM table_name
AS alias_name

SQL Alias Syntax for Columns

SELECT column_name AS alias_name
FROM table_name

eg:
SELECT po.OrderID, p.LastName, p.FirstName
FROM Persons AS p,
Product_Orders AS po
WHERE p.LastName='Hansen' AND p.FirstName='Ola'


joins
*****

Inner join:

SELECT column_name(s)
FROM table_name1
INNER JOIN table_name2
ON table_name1.column_name=table_name2.column_name

eg:
select c.customerID,c.CompanyName,c.contactName,o.orderID
from customers as c
inner join orders as o
on
c.customerID = o.customerID
order by c.customerID

Here, we select the first customerID from table customers, then we go thru each row in orders table and compare customerID with orders.customerID.
If there is a match we select the columns listed, else go forward.

LEFT Join:

The LEFT JOIN keyword returns all rows from the left table (table_name1), even if there are no matches in the right table (table_name2).

SELECT column_name(s)
FROM table_name1
LEFT JOIN table_name2
ON table_name1.column_name=table_name2.column_name
order by ...


Right Join:

The RIGHT JOIN keyword Return all rows from the right table (table_name2), even if there are no matches in the left table (table_name1).

SELECT column_name(s)
FROM table_name1
RIGHT JOIN table_name2
ON table_name1.column_name=table_name2.column_name

Eg:
select c.customerID,c.CompanyName,c.contactName,o.orderID
from customers as c
right join orders as o
on
c.customerID = o.customerID
order by c.customerID

Here, we select the first customerID from table orders, then we go thru each row in customers table and compare customerID with orders.customerID.
If there is a match we retrieve columns listed in customers, else we display them as NULL. We always display the columns from Orders table. 

Full Join:
The FULL JOIN keyword return rows when there is a match in one of the tables.

It is like doing a left join and then a right join.

union
*****
Union command is used to combine the result set of two select statements.
Union by default displays only distinct rows. Use UNION ALL to display all rows.
For UNION, tables must have the same number of columns. The columns must also have similar data types.

SELECT * FROM table_name1
UNION [ALL]
SELECT * FROM table_name2

select into
***********

SELECT column_name(s)
INTO new_table_name [IN externaldatabase]
FROM old_tablename  --> To create a new table from an existing one. Mostly used for backing up purposes.

In Oracle rather use:

insert into rgirotra.address  //schemaName.tableName
select * from 
rgirotra_shared_global.taddress;  //Note the table must already exist in rgirotra schema.

eg:
SELECT *
INTO Persons_Backup IN 'Backup.mdb'
FROM Persons

to create a back up of all customers and orders at the end of the day, use this command.
select o.orderid, c.customerid, c.companyName
into orders_backup
from customers as c 
INNER JOIN orders as o
ON c.customerid = o.customerid


create database
***************
create database myNewDatabase;


create table
***********

CREATE TABLE table_name
(
column_name1 data_type,
column_name2 data_type,
column_name3 data_type,
....
)

eg:
CREATE TABLE Persons (
	P_ID int,
	LastName nvarchar(255),  --> nvarchar() will also store Unicode characters.
	FirstName nvarchar(255),
	Address nvarchar(255),
	City nvarchar(255)
)

constraints
***********

constraints can be specified on the table columns when they are created or after they are created.
You can apply the following contraints:

UNIQUE
NOT NULL
PRIMARY KEY
FOREIGN KEY
DEFAULT
CHECK

NOT NULL
CREATE TABLE Persons (
	P_ID int NOT NULL,
	LastName nvarchar(255) NOT NULL,
	FirstName nvarchar(255),
	Address nvarchar(255),
	City nvarchar(255)
)


UNIQUE - to have unique elements per row for a given columns. Primary key columns are implicitly unique.
	 A UNIQUE field can be NULL. But a PRIMARY KEY field cannot be NULL.
CREATE TABLE Persons (
	P_ID int NOT NULL UNIQUE,
	LastName nvarchar(255) NOT NULL,
	FirstName nvarchar(255),
	Address nvarchar(255),
	City nvarchar(255)
)

OR

CREATE TABLE Persons (
	P_ID int NOT NULL,
	LastName nvarchar(255) NOT NULL,
	FirstName nvarchar(255),
	Address nvarchar(255),
	City nvarchar(255),
	CONSTRAINT uc_pid UNIQUE (P_ID,LastName) --> This means that the combination of both these fields for each row
					 	     should be unique. This syntax also allows you to give a name
					 	     to your constraint.
)

OR 
ALTER TABLE Persons
ADD CONSTRAINT uc_pid UNIQUE (P_ID, LastName) --> This will fail if there are already rows that violate this constraint.

or
ALTER TABLE Persons
DROP CONSTRAINT uc_pid


PRIMARY KEY
CREATE TABLE Persons (
	P_ID int NOT NULL,
	LastName nvarchar(255),
	FirstName nvarchar(255),
	Address nvarchar(255),
	City nvarchar(255),
	CONSTRAINT pk_pid PRIMARY KEY (P_ID)	
)

OR
CREATE TABLE Persons (
	P_ID int PRIMARY KEY NOT NULL,
	LastName nvarchar(255),
	FirstName nvarchar(255),
	Address nvarchar(255),
	City nvarchar(255),	
)
OR
CREATE TABLE Persons (
	P_ID int NOT NULL,
	LastName nvarchar(255),
	FirstName nvarchar(255),
	Address nvarchar(255),
	City nvarchar(255),	
)
ALTER TABLE Persons
ADD CONSTRAINT pk_pid PRIMARY KEY(P_ID)

OR 

ALTER TABLE Persons
DROP CONSTRAINT pk_pid


FOREIGN KEY - Used to prevent actions that would destroy the links between two tables.
A field in a table which yo mark with a Foreign key Constraint must be Primary key in another table.
Eg:
CREATE TABLE MyOrders (
	O_ID int NOT NULL,
	OrderNo int NOT NULL,
	P_ID int NOT NULL,
	CONSTRAINT fk_pid FOREIGN KEY (P_ID) REFERENCES Persons(P_ID),
	CONSTRAINT pk_oid PRIMARY KEY (O_ID)
)

OR
CREATE TABLE MyOrders (
	O_ID int NOT NULL,
	OrderNo int NOT NULL,
	P_ID int NOT NULL,
	CONSTRAINT pk_oid PRIMARY KEY (O_ID)
)
ALTER TABLE MyOrders
ADD CONSTRAINT fk_pid FOREIGN KEY (P_ID) REFERENCES Persons(P_ID)

OR
ALTER TABLE MyOrders
DROP CONSTRAINT fk_pid


CHECK --> To limit values you want to put in columns. Eg: P_ID should be greater than 0 and City should always be "New Delhi"
Eg:
CREATE TABLE Persons (
	P_ID int NOT NULL PRIMARY KEY CHECK(P_ID > 0),
	LastName nvarchar(255),
	FirstName nvarchar(255),
	Address nvarchar(255),
	City nvarchar(255) CHECK (City = 'New Delhi'),	
)
OR
CREATE TABLE Persons (
	P_ID int NOT NULL PRIMARY KEY,
	LastName nvarchar(255),
	FirstName nvarchar(255),
	Address nvarchar(255),
	City nvarchar(255),
	CONSTRAINT chk_pid CHECK (P_ID > 0 AND City = 'New Delhi')
)
OR
CREATE TABLE Persons (
	P_ID int NOT NULL PRIMARY KEY,
	LastName nvarchar(255),
	FirstName nvarchar(255),
	Address nvarchar(255),
	City nvarchar(255),	
)
ALTER TABLE Persons
ADD CONSTRAINT chk_pid CHECK (P_ID > 0 AND City = 'New Delhi')

Another example:

ALTER TABLE PERSONS
ADD CONSTRAINT ID_NON_NULL CHECK (Id IS NOT NULL);


Deleting a constraint.
ALTER TABLE Persons
DROP CONSTRAINT chk_pid

Syntax:
ALTER TABLE table_name
add CONSTRAINT constraint_name CHECK (column_name condition) [DISABLE];

The DISABLE keyword is optional. If you create a check constraint using the DISABLE keyword, the constraint will be created, but the condition will not be enforced.

The syntax for enabling a check constraint is:

ALTER TABLE table_name
enable CONSTRAINT constraint_name;

ALTER TABLE table_name
disable CONSTRAINT constraint_name;

DEFAULT - Used to give defualt values to fields. Syntax is slightly different than other constraints.
Eg:
CREATE TABLE Persons
(
P_Id int NOT NULL,
LastName varchar(255) NOT NULL,
FirstName varchar(255),
Address varchar(255),
City varchar(255) DEFAULT 'Sandnes'
)

OR
CREATE TABLE MyOrders (
	O_ID int NOT NULL PRIMARY KEY,
	OrderNo int NOT NULL,
	P_ID int NOT NULL,
	OrderDate datetime DEFAULT GETDATE()	
)

OR
ALTER TABLE Persons
ADD CONSTRAINT def_city DEFAULT 'London'
FOR City

OR
ALTER TABLE Persons
DROP CONSTRAINT def_city


indexes
*******

You can create indexes on columns and tables which are frequently searched against. Creating indexes speeds up data retrieval.
But also slows down data updation. So you should create indexes only on columns/tables which require frequent searching.
Indexes are by the way not viewable by users.
Syntax is different for all databases. For MS SQL Server:

Eg:
CREATE INDEX PIndex
ON Persons (LastName)

OR
DROP INDEX table_name.index_name
Eg: drop index Persons.PIndex

drop
****

DROP TABLE table_name --->> For tables
DROP DATABASE database_name  -->> for databases

TRUNCATE TABLE table_name --> To remove all rows, you can use "DELETE FROM table_name" query also.

alter  -->> Used to add, delete or modify columns in a table.
*****

Eg:
ALTER TABLE table_name
ADD column_name datatype  --> To add a new column

OR
ALTER TABLE table_name
ALTER COLUMN column_name newDataType


Please go to w3schools SQL tutorial to read the rest of the tutorial. Then come back here to read more about Oracle SQL.

PseudoColomns
*************

Pseudocolomns are actually just like table colomns. but are not stored in a table. You can select from them but not update,
insert or delete them. You'll learn about different types of pseudocolomns as you read on.

Sequence
********

A sequence is a database object used to generate unique integers. Multiple users can use the same sequence and they are guaranteed
to get different values. Access sequence values using CURRVAL and NEXTVAL pseudocolomns. When you create a sequence first initialise
it using NEXTVAL. First call to NEXTVAL will return you the initial value.  To create a sequence you must have the desired permissions.
You get an error if you try to access sequence.CURRVAL before sequence.NEXTVAL

ORA-02289: sequence does not exist
02289. 00000 -  "sequence does not exist"
*Cause:    The specified sequence does not exist, or the user does
           not have the required privilege to perform this operation.
*Action:   Make sure the sequence name is correct, and that you have
           the right to perform the desired operation on this sequence.

Eg:
	CREATE SEQUENCE [schema.]sequenceName 
	[INCREMENT BY <positive or negative number, but not zero]
	[START WITH <integer>]
	[MAXVALUE <integer> | NOMAXVALUE]
	[MINVALUE <integer> | NOMINVALUE]
	[CYCLE | NOCYCLE] 
	[CACHE <integer> | NOCACHE] //For faster retrieval
	[ORDER | NOORDER]
	
	CREATE SEQUENCE rajatSeq;
	SELECT rajatSeq.NEXTVAL from DUAL;

To refer to the current or next value of a sequence in the schema of another user, you must qualify the sequence with the schema
containing it:

schema.sequence.CURRVAL
schema.sequence.NEXTVAL

To refer to the value of a sequence on a remote database, you must qualify the sequence with a complete or partial name of a database link:

schema.sequence.CURRVAL@dblink
schema.sequence.NEXTVAL@dblink

Use the ALTER SEQUENCE statement to change the increment, minimum and maximum values, cached numbers, and behavior of an existing sequence.
This statement affects only future sequence numbers. Eg:

ALTER SEQUENCE customers_seq
MAXVALUE 1500;

This statement turns on CYCLE and CACHE for the customers_seq sequence:

ALTER SEQUENCE customers_seq
CYCLE
CACHE 5;

Drop a sequence using the following syntax:

DROP SEQUENCE [schema.]sequenceName;

Use sequence like below:

INSERT INTO suppliers (supplier_id, supplier_name)
VALUES (supplier_seq.nextval, 'Kraft Foods');

VIEWS
*****

A virtual table which can consist of rows from one or more tables. 

CREATE VIEW <viewName> as
SELECT * from TABLE_NAME
WHERE CONDITION

SELECT * from viewName; // will always fetch latest data from the underlying tables.
where CONDITION


ROWID and ROWNUM
****************

Both these are pseudo colomns. ROWID contains the address of each row in the database. Although this is unique but rows
in two tables in the same cluster can have the same ROWID's, so you should never use it as a primary key.
ROWNUM is an integer that uniquely identifies each row in a table.


ORACLE Data types
*****************

Oracle has many built-in data types. Here I am only going to list a few important and most frequently used ones. You can look
up others in the SQL reference guilde.

1] VARCHAR2 (size BYTE|CHAR) --> For holding variable size character values. Maximum is 4000 bytes. Also 1 Byte is not same as 1 character as some characters take more than 1 byte.
2] NVARCHAR2 (size) --> Same as above but used for storing Unicode. This is the best option to use. Always install your Oracle DB with UTF-8 character set and use NVARCHAR2 for storing strings.
3] NUMBER (precison, scale) -->Number having precesion and scale. precision is the number of digits and scale is the no. of decimal digits.
If you specify a negative scale, Oracle Database rounds the actual data to the specified number of places to the left of the decimal point. 
For example, specifying (7,-2) means Oracle Database rounds to the nearest hundredths, i.e. 7,456,123.89 will be stored as 7,456,100.
4] FLOAT (precesion) --> Basically a subtype of number with precesion p. Use NUMBER instead of FLOAT wherever possible.
5] LONG ---> To store character data upto 2 GB. Only provided for backwards compatability. Use CLOB or NCLOB instead which support upto 8 tera bytes of data.
6] DATE --> Used to store data in YEAR, MONTH, DAY, HOUR, MINUTE and SECOND format. No fractional seconds available.
7] TIMESTAMP (fractional_seconds_precesion) --> Same as DATE but with support for fractional seconds.
8] TIMESTAMP (fractional_seconds_precesion) WITH TIME ZONE.
9] TIMESTAMP (fractional_seconds_precesion) WITH LOCAL TIME ZONE.
10] CHAR (size BYTE|CHAR) --> For holding fixed length character data.
11] NCHAR (size) --> Same as CHAR but used for holding Unicode characters.

There are many more.

VARCHAR2, NUMBER etc are very trivial. Lets look at DATE AND TIMESTAMP. As you already know they are made up of YEAR, MONTH, DAY,
HOUR, MINUTE, SECOND etc.

You can specify a DATE value as a literal, or you can convert a character or numeric value to a date value with the TO_DATE function.

CREATE TABLE dateTest
(
   dateValue DATE NOT NULL
)

Oracle will display the value of the DATE field based on the parameter NLS_DATE_FORMAT value in the NLS_SESSION_PARAMETERS table;
You can do a 

select * from sys.nls_session_parameters and see. This is actually a view so you cannot modify it.
Use the Alter session command to do it..
ALTER SESSION SET NLS_DATE_FORMAT='YYYY-MON-DD';  //For me default was- RR-MON-DD  ie. 13-Jul-17
commit;


INSERT INTO dateTest
values (DATE '1983-05-21');  //Specifying a DATE LITERAL IN THE ANSI FORMAT YYYY-MM-DD. The Time field will be set to midnight.

INSERT INTO dateTest
VALUES(TO_DATE('98-DEC-25 17:30','YY-MON-DD HH24:MI')); //Using the to_date() function to generate an Oracle date.
							//The time field will be set to MIDNIGHT.

SELECT * FROM dateTest;

DATEVALUE
---------
21-MAY-83 
25-DEC-98 

If you specify a date value without a time component, then the default time is midnight (00:00:00 or 12:00:00 for 24-hour and
12-hour clock time, respectively). If you specify a date value without a date, then the default date is the first day of
the current month.

INSERT INTO my_table VALUES (1, SYSDATE); //Set the date with some value in the time field other than midnight.
INSERT INTO my_table VALUES (2, TRUNC(SYSDATE));  //The trunc() function sets the time field to midnight.

SELECT *
FROM my_table
WHERE datecol = TO_DATE('03-OCT-02','DD-MON-YY');

ROW_NUM    DATECOL
-------    -------
2          03-OCT-02 

because the first row has a time field set which is not midnight.

The date function SYSDATE returns the current system date and time. The function CURRENT_DATE returns the current session date.

SELECT SYSDATE  FROM DUAL;
SELECT CURRENT_DATE FROM DUAL;

The default date values are determined as follows:
■ The year is the current year, as returned by SYSDATE.
■ The month is the current month, as returned by SYSDATE.
■ The day is 01 (the first day of the month).
■ The hour, minute, and second are all 0.

These default values are used in a query that requests date values where the date itself is not specified, as in the following example,
which is issued in the month of May:

SELECT TO_DATE('2009', 'YYYY') FROM DUAL;

TO_DATE('
---------
01-MAY-09

Julian Days - A Julian day number is the number of days since January 1' 4712 BC. Use the  TO_DATE() and TO_CHAR() functions to convert
between Oracle dates and Julian days.

SELECT TO_CHAR(TO_DATE('2009', 'YYYY'),'J') FROM DUAL;

TO_CHAR
-------
2454833

It looks like you can also perform arithmetic with dates. Example,

select sysdate - 1 from dual; //Will show the next system date
select sysdate + 10 from dual; //will show the date 10 days ahead.
select date '2013-06-13' + 2 from dual;

DUAL TABLE
**********

The DUAL table is created automatically when you install Oracle. It is part of the schema of the user SYS but is available for use to
all users. It contains just one colomn DUMMY of type VARCHAR2(1), and one row with the value X. The dual table is used for computing
a constant expression using the select statement. Alternatively, you can compute a constant, pseudocolomn or expression from any table
but the value will be returned as many times as there are rows in that table.  Eg

create sequence abcd;
select abcd.nextval from dual; //returns a single value 1.
select abcd.nextval from exchange; //returns 2,3,4,5 etc based on how many rows there are in the table.

You can also perform arithmetic on DATE and TIMESTAMP and INTERVAL data types. I am not showing that here

There is also a USER_TABLES table which lists all the tables for the current user. So if you want to drop all tables in your schema use:
SELECT 'DROP DATABASE ' || table_name || ' CASCADE CONSTRAINTS' AS ABCD FROM USER_TABLES; 
//Note we are using the concatenation operator || in the above query.

Any arithmetic expression containing a null always evaluates to null. For example, null added to 10 is null. In fact, all operators
(except concatenation) return null when given a null operand.

To test for nulls, use only the comparison conditions IS NULL and IS NOT NULL. If you use any other condition with nulls and the
result depends on the value of the null, then the result is UNKNOWN.

TIMESTAMP
*********

You have:
1] simple TIMESTAMP(fractional_precisoin) and - 
2] TIMESTAMP (fractional_precisoin) WITH TIME ZONE - Where you need to preserve time zone information.
3] TIMESTAMP (fractional_precisoin) WITH LOCAL TIME ZONE - Used where date information is always to be displayed in the time
   zone of the client system.

Just like you can specify DATE using DATE literals or to_date() function, you can use TIMESTAMP literals or to_timestamp() function.

select systimestamp from dual;

SELECT TO_TIMESTAMP ('10-Sep-02 14:10:10.123000', 'DD-Mon-RR HH24:MI:SS.FF')
   FROM DUAL;

TO_TIMESTAMP('10-SEP-0214:10:10.123000','DD-MON-RRHH24:MI:SS.FF')
---------------------------------------------------------------------------
10-SEP-02 02.10.10.123000000 PM

create table timetest
(
    timeValue TIMESTAMP WITH LOCAL TIME ZONE //Insert queries will insert time in the session's time zone.
	                                         //Select queries will display time in the sessions time zone.
);

select dbtimezone from dual;  // +00.00 Given that DB is stored in London
select sessiontimezone from dual; //+08.00 given that database queries are run in SG.

Eg:
From SG:
--------
insert into timeTest
values (to_timestamp('21-May-1983 08:00:00', 'DD-MON-YYYY HH24:MI:SS'));

select * from timetest; //Will show time as 00.00 in London.


OPERATORS
*********

Precedence - Unary plus minus, followed by * and / (multiply and divide), followed by binary addition and subtraction (+, -)

SELECT * FROM order_items WHERE quantity = -1 ORDER BY order_id, line_item_id, product_id;  //Unary minus & plus.
SELECT * FROM employees WHERE -salary < 0 ORDER BY employee_id;

SELECT hire_date FROM employees WHERE SYSDATE - hire_date > 365 ORDER BY hire_date; //subtraction.

UPDATE employees
SET salary = salary * 1.1; //Multiplication.

Do not use two consecutive minus signs (--) in arithmetic expressions to indicate double negation or the subtraction of a negative value.
The characters -- are used to begin comments within SQL statements. You should separate consecutive minus signs with a space or parentheses.

CONCATENATION OPERATOR
**********************

The concatenation operator manipulates character strings and CLOB data.
The result of concatenating two character strings is another character string. If both character strings are of data type CHAR, then the
result has data type CHAR and is limited to 2000 characters. If either string is of data type VARCHAR2, the result has data type VARCHAR2 
and is limited to 4000 characters. If either argument is a CLOB, the result is a temporary CLOB. Trailing blanks in character strings are
preserved by concatenation, regardless of the data types of the string or CLOB.

Eg: SELECT 'Name is ' || last_name FROM employees ORDER BY last_name;

Although Oracle treats zero-length character strings as nulls, concatenating a zero-length character string with another operand always
results in the other operand, so null can result only from the concatenation of two null strings. However, this may not continue to be true
in future versions of Oracle Database. To concatenate an expression that might be null, use the NVL function to explicitly convert the
expression to a zero-length string.

HIERARCHICAL QUERIES
********************

A relational database does not store data in a hierarchical way. Then how do I get the data in a hierarchical manner? For eg: Consider
the following data in the employees table.

EmpNo				Mgr
----				---
7369	SMITH	CLERK		7902	17-DEC-80
7499	ALLEN	SALESMAN	7698	20-FEB-81
7521	WARD	SALESMAN	7698	22-FEB-81
7566	JONES	MANAGER		7839	02-APR-81
7654	MARTIN	SALESMAN	7698	28-SEP-81
7698	BLAKE	MANAGER		7839	01-MAY-81
7782	CLARK	MANAGER		7839	09-JUN-81
7788	SCOTT	ANALYST		7566	19-APR-87
7844	TURNER	SALESMAN	7698	08-SEP-81
7876	ADAMS	CLERK		7788	23-MAY-87
7900	JAMES	CLERK		7698	03-DEC-81
7902	FORD	ANALYST		7566	03-DEC-81
7934	MILLER	CLERK		7782	23-JAN-82
7839	KING	PRESIDENT		17-NOV-81

The script to create the database table and insert values is separately places in a file. How do you retrieve all employees reporting
directly to the President.

SELECT empno, 
       ename, 
       job, 
       mgr, 
       hiredate,
       level   --level is a Pseudocolomn
FROM   employees
START WITH mgr IS NULL 
CONNECT BY PRIOR empno = mgr

START WITH – Specifies the root rows of the hierarchy or in other words, where to start parsing from. This clause is necessary for
true hierarchical queries

CONNECT BY PRIOR – This explains the relationship between the parent and the child. 
CONNECT BY PRIOR col_1 = col_2
When working from top to bottom, then col1_1 should be the parent key.
When working from bottom to top, then col1_1 should be the child key.

You can also restrict the records to a level using the where clause.

SELECT empno, 
       ename, 
       job, 
       mgr, 
       hiredate, 
       LEVEL 
FROM   emp 
WHERE  LEVEL <= 2 
START WITH mgr IS NULL 
CONNECT BY PRIOR empno = mgr

And you can display it in a nice fashion like this.

SELECT Lpad(ename,Length(ename) + LEVEL * 10 - 10,'-') 
FROM   emp 
START WITH mgr IS NULL 
CONNECT BY PRIOR empno = mgr

Dont Worry!! You'll learn about Lpad() and Length() later. If you want to prune a child of a parent, you can use the normal where clause.

SELECT empno, 
       ename, 
       job, 
       mgr, 
       hiredate 
FROM   emp 
WHERE  ename <> 'JONES' -- Will not show JONES but will still show its descendents.
START WITH mgr IS NULL 
CONNECT BY PRIOR empno = mgr

To prune the complete child hierarchy, use a clause in the "CONNECT BY PRIOR" operator.

SELECT empno, 
       ename, 
       job, 
       mgr, 
       hiredate 
FROM   emp 
START WITH mgr IS NULL 
CONNECT BY PRIOR empno = mgr AND ename <> 'CLARK' --THis will restrict CLARK and all its children.

There are also PRIOR and CONNECT_BY_ROOT operators, but I am skipping those for now.

FUNCTIONS
*********

SQL functions:

select ABS(-987.567) from dual; -- 987.567
select LN(100) from dual; -- Log natural of 100 approx = 4.605 
select LOG(10, 100) from dual; -- Log 100 to the base 10. = 2.
select MOD(5, 2) from dual; -- remainder of 100/10 = 0.
select NANVL(n2, n1) from dual; -- only for types BINARY_FLOAT and BINARY_DOUBLE. If n2 is NaN, then returns n1.
                                   If n2 is NOT a NaN, returns n2.
select POWER(a, b) from dual; --returns a to the power b.
select REMAINDER(a, b) from dual; --same as MOD. MOD uses FLOOR in its formula, whereas REMAINDER uses ROUND.
select ROUND(n1, n2) from dual; --round number n1 to n2 decimal places.
select TRUNC(15.79, 1) "TRUNCATE" from dual; -- truncate to 1 decimal place.

NVL(expr1, expr2) -- If expr1 IS NULL, return expr2. If expr1 IS NOT NULL, return expr1.
NVL2(expr1, expr2, expr3) -- If expr1 IS NOT NULL, return expr2. If expr1 IS NULL, return expr3.
LENGTH(expr1)   -- The length of the expression.
INITCAP (expr1) -- For each word in expr1, INITCAP will capitalize the first alphabet and the rest will be in lower case.
COALESCE(expr1, expr2, ...) - COALESCE returns the first non-null expr in the expression list. You must specify at least two expressions. 
If all occurrences of expr evaluate to null, then the function returns null.

And an endless list of functions follow. See the SQL reference for more.

EXPRESSIONS
***********
You can combine values, constants, operators and functions to form expressions. Lets see how. For eg:

select (2*2) from dual;  -- (2*2) is an expression
select to_char(trunc(sysdate+7)) from dual; -- to_char(trunc(sysdate+7)) is an expression.

Case expresssions: These allow you to write IF.. THEN.. ELSE type of constructs directly into the SQL SELECT statement without
using STORED PROCEDURES. The syntax is something like this.

CASE expr WHEN comparison_expr1 THEN return_expr1
          WHEN comparison_expr2 THEN return_expr2
          WHEN comparison_expr3 THEN return_expr3
          ELSE return_expr4 END

eg:
   SELECT cust_last_name,
          CASE credit_limit WHEN 100 THEN 'Low'
                            WHEN 5000 THEN 'Medium'
                            ELSE 'High' END AS credit
   FROM CUSTOMERS
   ORDER BY cust_last_name, credit


  SELECT AVG(CASE WHEN e.salary > 2000 THEN e.salary
                  ELSE 2000 END) "Average Salary" FROM employees e;

Here we are finding the average salary of employees in the employees table using 2000 as the lowest salary.


Also note that 

COALESCE(expr1, expr2)
is equivalent to:
CASE WHEN expr1 IS NOT NULL THEN expr1 ELSE expr2 END

COALESCE(expr1, expr2, ..., exprn)
where n >= 3, is equivalent to:
CASE WHEN expr1 IS NOT NULL THEN expr1
ELSE COALESCE (expr2, ..., exprn) END

