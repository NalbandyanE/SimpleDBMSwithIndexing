#include "../include/commandexecutor.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

CommandExecutor::CommandExecutor() = default;

CommandExecutor::CommandExecutor(const Command& c) : command{c} {}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void CommandExecutor::execute(const Command& com) {
    CommandValidator validator; 
    std::string sql_command = com.getName();
    std::vector<std::string> args = com.getArguments();
    std::transform(sql_command.begin(), sql_command.end(), sql_command.begin(), ::toupper);
    if (sql_command == "CREATE DATABASE") {
        if (validator.isValidCommand(com)) {
            db = DBMS(args[0]);
            std::cout << "Database '" << args[0] << "' created." << std::endl;
        } else {
            std::cout << "Invalid 'CREATE DATABASE' command. Please try again." << std::endl;
        }
    } else if (sql_command == "CREATE TABLE") {
        if (validator.isValidCommand(com)) {
            table = Table(args[0]);
            db.addTable(table);
            std::cout << "Table '" << args[0] << "' created." << std::endl;
        } else {
            std::cout << "Invalid 'CREATE TABLE' command. Please try again." << std::endl;
        }
    } else if (sql_command == "INSERT INTO") {
        std::string table_name = args[0];
	    std::string field_names_str = args[1];
	    std::string field_values_str = args[2];
	    field_names_str = field_names_str.substr(1, field_names_str.length() - 2);
	    field_values_str = field_values_str.substr(1, field_values_str.length() - 2);
	    std::vector<std::string> field_names = splitCommand(field_names_str, ',');
	    std::vector<std::string> field_values = splitCommand(field_values_str, ',');
	    Row new_row;
	    for (size_t i = 0; i < field_names.size(); ++i) {
	        Field field(field_names[i], field_values[i]);
	        new_row.addField(field);
            if (!table.hasIndexOn(field_names[i])) {
                table.createIndex(field_names[i], 3);
            }

            Index& index = table.getIndex(field_names[i]);
            index.insert(field_values[i], new_row);
	    }
	    table.insertRow(new_row);
	    std::cout << "Row inserted" << std::endl;
    } else if (sql_command == "SELECT") {
        std::string table_name = args.back();
        std::vector<std::string> field_names(args.begin(), args.end() - 1);
        std::string condition = args[args.size() - 1];
        std::vector<std::string> cond_pairs = splitCommand(condition, '=');
        if (cond_pairs.size() == 2) {
            std::string field_name = field_names[0];
            std::string field_value = cond_pairs[1];
            int row_index = -1;
            std::vector<Row> rows = table.selectAll();
            for (int i = 0; i < rows.size(); ++i) {
                if (rows[i].getFieldValue(cond_pairs[0]) == cond_pairs[1]) {
                    row_index = i;
                    break;
                }
            }
            if (row_index == -1) {
                std::cout << "Error: No row meets the specified condition." << std::endl;
                return;
            }
            Row row = table.selectAll()[row_index];
            if (table.hasIndexOn(field_name)) {
                Index& index = table.getIndex(field_name);
                std::vector<Row> search_result = index.search(row.getFieldValue(field_name));
                if (!search_result.empty()) {
                    std::cout << "Search result using index:" << std::endl;
                    for (const Row& row1 : search_result) {
                        std::cout << row1.getFieldValue(field_name) << " ";
                        std::cout << std::endl;
                    }
                } else {
                    std::cout << "No matching rows found using index." << std::endl;
                }
                return;
            }
        }
        if (field_names[0] == "*") {
            table.show();
        }
        else {
            table.select(field_names);
        }
    } else if (sql_command == "UPDATE") {
        if (args.size() < 3) {
            std::cout << "Invalid UPDATE command. Please provide the SET clause and a valid WHERE condition." << std::endl;
            return;
        }
        std::string table_name = args[0];
        std::string condition = args[args.size() - 1];
        std::vector<std::string> new_values(args.begin() + 1, args.end() - 1);
        std::vector<std::string> cond_pairs = splitCommand(condition, '=');
        
        int row_index = -1;
        std::vector<Row> rows = table.selectAll();
        for (int i = 0; i < rows.size(); ++i) {
            if (rows[i].getFieldValue(cond_pairs[0]) == cond_pairs[1]) {
                row_index = i;
                break;
            }
        }
        if (row_index == -1) {
            std::cout << "Error: No row meets the specified condition." << std::endl;
            return;
        }
        Row new_row = table.selectAll()[row_index];
        for (size_t i = 0; i < new_values.size(); i += 2) {
            std::vector<std::string> values_pairs = splitCommand(new_values[i], '=');
            std::string field_name = values_pairs[i];
            std::string field_value_str = values_pairs[i + 1];
            new_row.setField(field_name, field_value_str);
        }
        table.updateRow(row_index, new_row);
        std::cout << "UPDATE successful."<< std::endl;
    } else if (sql_command == "DELETE") {
        if (args.size() < 2) {
            std::cout << "Invalid DELETE command. Please provide a valid WHERE condition." << std::endl;
            return;
        }
        std::string table_name = args[0];
        std::string where_condition = args[1];
        std::vector<Row> rows = table.selectAll(); 
        for (int i = rows.size() - 1; i >= 0; --i) {
            if (table.meetCondition(rows[i], where_condition)) { 
                table.deleteRow(i); 
            }
        }
    } else {
        std::cout << "Unsupported SQL command. Please try again." << std::endl;
    }
}

std::vector<std::string> CommandExecutor::splitValues(const std::string& values) {
    std::vector<std::string> result;
    std::istringstream ss(values);
    std::string value;
    while (getline(ss, value, ',')) {
        result.push_back(value);
    }
    return result;
}

std::vector<std::string> CommandExecutor::splitCommand(const std::string& str, char delimiter) {
    std::vector<std::string> parts;
    std::stringstream ss(str);
    std::string part;
    while (std::getline(ss, part, delimiter)) {
        parts.push_back(trim(part));
    }
    return parts;
}