# DBMS-project
The zipped file contains the following files:\n
• parse_rp.cpp
• parse_wb.cpp
• parse_cit.cpp
• loader.sql
• ERD.pdf
• pg_dump.sql
• relation_schema.sql
• ReadMe
• source.txt (original provided)

Note: All the source codes should be run on LINUX based system as windows system has
encoding WIN1252 different than UTF-8 which will cause problem in as some characters
don't have equivalents from WIN1252 to UTF-8.
The files parse_rp.cpp, parse_wb.cpp and parse_cit.cpp are the parser codes.
For compiling and running the codes.
1. The order of execution should be parse_rp.cpp, parse_wb.cpp then parse_cit.cpp
2. For compiling use g++ file_name.cpp -o filename
3. This will generate loader.sql (also provided in the zip)
For creating and populating the database:
1.  Open Postgresql and create database using command: CREATE DATABASE db_name
2.  Connect to the database using: \c db_name
3.  Load data in database using command: \i {file location of loader.sql}
4.  Wait for some time, make yourself a cup of coffee till our loader file populate the
database.

EXPLANATION
To create a database, we first created file relation_schema.sql which will create tables for
entity set and relations in the database.
After that we parsed the data from source.txt file into SQL files using c++ language.
We made 3 files for parsing.
• parse_rp.cpp= This file will parse the data in source.txt and output a file called
loader.sql which will be our loader file. This file will output the sql code to populate
entries of entity sets, research_paper and author.
• parse_wb.cpp = This file will parse the data in source.txt and append it at the end of
loader.sql. It will output entries to populate the entries of the relation written_by.
• parse_cit.cpp = This file will parse the data in source.txt and append it at the end of
loader.sql. It will output entries to populate the entries of the relation citations.

IMPORTANT NOTE: The file parse_rp.cpp must be compiled and executed before other two
parse files as the database must populate the entity sets research_paper and author before
the relations because relation will have foreign key constraint which must already be
present.
The loader.sql file obtained after compiling and executing all three parse files will contain all
the entries to populate the database.
pg_dump file has the backup of our obtained database.
CONTRIBUTION
 Ayush Jha
 Yuvraj Singh Shekhawat
 Rohan Atkurkar
