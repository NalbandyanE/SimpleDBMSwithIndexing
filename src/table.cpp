#include "../include/table.h"

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>

Table::Table(const std::string& n) : name{n} {}

Table::Table(const std::string& n, const std::vector<std::string>& c, int o) 
    : name{n},
    columns{c},
    order{o}
{
} 

void Table::insertRow(const Row& row) {
    rows.push_back(row);
    std::string filename = "data/" + generateFileName(rows.size() - 1);
    saveToFile(filename, row);
    rowFiles.push_back(filename);
}

void Table::updateRow(int index, const Row& row) {
    if (index < 0 || index >= rows.size()) {
        throw std::out_of_range{"Index out of range"};
    }
    rows[index] = row;
    saveToFile(rowFiles[index], row);
}

std::vector<Row> Table::selectAll() const {
    return rows;
}

Row Table::selectRow(int index) {
    if (index < 0 || index >= rows.size()) {
        throw std::out_of_range{"Index out of range"};
    }
    Row row;
    loadFromFile(rowFiles[index], row);
    return row;
}

void Table::selectRowNum(int n) {
    Row row = selectRow(n);
    for (int i = 0; i < row.getFields().size(); ++i) {
        std::cout << row.getFields()[i].getValue() << "\t";
    }
    std::cout << std::endl;
}

void Table::select(const std::vector<std::string>& field_names) const {
    for (int i = 0; i < rows.size(); ++i) {
        for (int j = 0; j < field_names.size(); ++j) {
            std::cout << rows[i].getFieldValue(field_names[j]) << "\t";
        }
        std::cout << std::endl;
    }
}

void Table::deleteRow(int index) {
    if (index < 0 || index >= rows.size()) {
        throw std::out_of_range{"Index out of range"};
    }
    rows.erase(rows.begin() + index);
    std::remove(rowFiles[index].c_str());
    rowFiles.erase(rowFiles.begin() + index);
}

std::string Table::getName() const {
    return name;
}

void Table::show() const {
    if (rows.empty()) {
        std::cout << "Table is empty." << std::endl;
        return;
    }
    for (const auto& field : rows[0].getFields()) {
        std::cout << field.getName() << "\t";
    }
    std::cout << std::endl;
    for (int i = 0; i < rows.size(); ++i) {
        Row row;
        loadFromFile(rowFiles[i], row);
        for (const auto& field : row.getFields()) {
            std::cout << field.getValue() << "\t";
        }
        std::cout << std::endl;
    }
}

bool Table::loadFromFile(const std::string& filename, Row& row) const {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }
    row = Row(); 
    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string fieldName, fieldValue;
        if (ss >> fieldName >> fieldValue) {
            fieldName.erase(fieldName.length() - 1);
            Field field(fieldName, fieldValue);
            row.addField(field);
        }
    }
    file.close();
    return true;
}

bool Table::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }
    rows.clear();
    std::string line;
    while (getline(file, line)) {
        std::cout << "Reading line: " << line << std::endl; 
        std::stringstream ss(line);
        std::string fieldName, fieldValue;
        Row row; 
        while (ss >> fieldName >> fieldValue) {
            fieldName.erase(fieldName.length() - 1);
            Field field(fieldName, fieldValue);
            row.addField(field);
        }
        rows.push_back(row); 
    }
    file.close();
    if (rows.empty()) {
        std::cerr << "Table is empty." << std::endl;
        return false;
    }

    return true;
}

bool Table::saveToFile(const std::string& filename, const Row& row) const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    for (const auto& field : row.getFields()) {
        file << field.getName() << ": " << field.getValue() << "\n";
    }
    file << std::endl;
    file.close();
    return true;
}

std::string Table::generateFileName(int index) const {
    return name + "_" + std::to_string(index) + ".txt";
}

bool Table::meetCondition(const Row& row, const std::string& condition) {
    size_t pos = condition.find('=');
    if (pos == std::string::npos) {
        return false;
    }
    std::string field_name = condition.substr(0, pos);
    std::string value = condition.substr(pos + 1);
    std::string row_value = row.getFieldValue(field_name);
    return row_value == value;
}

bool Table::hasIndexOn(const std::string& columnName) const {
    return indexes.find(columnName) != indexes.end();
}

Index& Table::getIndex(const std::string& columnName) {
    return *indexes[columnName];
}

void Table::createIndex(const std::string& columnName, int order) {
    Index* newIndex = new Index(order);
    indexes[columnName] = newIndex;
    indexes[columnName]->createIndex(rows, columnName);
}