Relational Parser

1)Syntax to define a table

<define> <table_name> <attribute_name1> <attribute_type1> <,> <attribute_name2> <attribute_type2> ...... <attribute_namen> <attribute_typen>

This command creates an empty table with the table name as table_name having n attributes of the given name and type. The supported types are 
1) int
2) string

It also allocates all the necessary hashmaps and dictionaries being used to access or update the table

The method used to implement this command is check_query_def. This method calls other helper functions, created to remove redundancy of code.

2)Syntax to rename a table

<rename> <old_tname> <new_tname>

This method temporarily renames a table. It is used when the same table needs to be accessed twice or more times. This is useful for joins and cartesian products and other such queries.

The method used to implement this command is check_query_rename

3)Syntax to project attributes of a table

This command is used to project certain attributes of a table. After projecting the attributes, it also removes any duplicates present in the projected table.

<project> <attribute1> <,> <attribute2> .... <attributen> <from> <tablename>

The command projects all the attributes given with the command from the table given in the command. It is implemented using the method project_nested. It uses various other helper functions and hash maps for faster access of tables and its attributes.


4)Syntax to insert into the table 

The parser supports both relational algebra assignment , which removes prior values of the table, and standard insertion that will preseve the original contents of the table.

To assign the value 
tablename <- { (tupleblock_1) , (tupleblock_2) ... } 

To insert into the table 
tablename <<- { (tupleblock_1) , (tupleblock_2) ... } 


Each tuple block has values that are comma separated and must match the type of the attribute. Also , the number of attributes must match with each tupleblock size. 
The command is implemented using check_query_assign method and it uses other helper functions which are prior defined.


5) Syntax to select from the table

Select command supports both the project operation and the rename operation in itself. 
The general syntax of the select command is

<select> <attribute_1> , <attribute_2>... <attribute_n> from <table_1> ,<table_2> ... <table_n> where expression

In case of multiple tables, rach attribute must be specified with its table name as table_name.attribute to maintian consistency.
The expression given in the where clause supports 

1) And 
2) Or

connectors to join sub-expressions.
It supports the following operators
1) =
2) >
3) <
4) >=
5) <=
To compare the attribute with constants

Any number of connectors and operators can be added for comparison. It is implemented using the method select_nested. It uses various other helper functions and hash maps for faster access of tables and its attributes.

6) Syntax for cartesian product

This is used to take the cartesian product of multiple tables
Syntax <table name 1 > cartesian_product < table name 2 > cartesian_product ... <table name n >
This command is implemented using check_query_cartesian

7) Syntax for expressions

Any number of tables can be used to write an expression using union or intersection
Syntax for which is

<table name 1> <operator> <table name 2> .... <table name n >

The tables must be union compatible.
The supported operators are 
1) union 
2) intersect


8) Nested Queries

The parser supports nested queries. If the rightmost command is a select command than the user can also specify the attributes to be projected from multiple tables. project is used to display attributes from a single table. Outer select are used to impose additional conditions. 
Syntax
<select > <condition> <project> <attributes> .... <select> <attributes> from <tables> <where> <condition>

Detailed examples are given in the queries.txt file
The method is implemented using check_query_nested, along with other helper functions
 

Data Storage :
Each table has its own text file, named after the table name that stores the data and other metadata like attribute name, attribute size , attribute type, size of the table.
A common text file named as parser.txt stores the table names and no. of tables.

9) Join

To join a table ( inner join ) use the syntax
<join> <table name >  <{> < attrib 1> , <attrib 2 > ... <attrib n >   <}> 

It is implemented using check_query_join method, which used other helper functions


