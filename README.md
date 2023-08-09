# SimpleDBMSwithIndexing
This project is a lightweight, file-based Database Management System designed to provide basic data storage and manipulation functionalities. It allows users to create databases, define tables with columns, insert and manage data, query data using SQL-like commands, and leverage B-Tree indexing for improved query performance.

## Features

- **File-Based Database Management:** Stores data in files on disk. This approach provides simplicity and portability.
- **Database Creation:** Create and manage multiple file-based databases.
- **Table Definition:** Define tables with specified columns and data types.
- **Data Manipulation:** Insert, update, and delete rows in tables.
- **Querying Data:** Retrieve data from tables using SQL-like queries.
- **Indexing:** Automatically create and utilize indexes to optimize query performance.

### Usage

Once the DBMS starts, you can enter SQL-like commands to interact with the database.

## Commands
- `CREATE DATABASE <db_name>;` - Creates a new database with the given name.
- `CREATE TABLE <table_name>;` - Creates a new table with the given name.
- `INSERT INTO <table_name> (<column1>, <column2>, ...) VALUES (<value1>, <value2>, ...);` - Inserts a new row of data into the table.
- `SELECT <column1>, <column2>, ... FROM <table_name>;` - Queries data from the table and retrieves the specified columns.
- `UPDATE <table_name> SET <column1>=<value1>, <column2>=<value2>, ... WHERE <condition>;` - Updates data in the table based on the specified condition.
- `DELETE FROM <table_name> WHERE <condition>;` - Delete data from table based on the specified condition.


### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/NalbandyanE/SimpleDBMSwithIndexing.git
   ```
2. Compile the source files using your preferred C++ compiler:
   ```bash
   cd SimpleDBMSwithIndexing
   ```
   ```bash
   g++ src/field.cpp src/row.cpp src/table.cpp src/dbms.cpp src/command.cpp src/commandValidator.cpp src/commandExecutor.cpp src/index.cpp main.cpp
   ```
3. Run the executable:
   ```bash
   ./a.out
   ```

## Contributing

Contributions are welcome! If you find any bugs or have ideas for improvements, please open an issue or submit a pull request.
