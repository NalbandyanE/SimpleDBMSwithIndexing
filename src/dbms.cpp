#include "../include/dbms.h"

#include <iostream>

DBMS::DBMS(const std::string& name) : name {name}
{
}

void DBMS::createTable(const std::string& n) {
	Table table(n);
	tables.push_back(table);
}

void DBMS::showTable(const Table& table) const {
	table.show();
}

void DBMS::dropTable(const std::string& n) {
	for (int i = 0; i < tables.size(); ++i) {
		if (tables[i].getName() == n) {
			tables.erase(tables.begin() + i);
		}
	}
}

void DBMS::addTable(const Table& t) {
	tables.push_back(t);
}

const Table* DBMS::getTable(const std::string& t) const {
    for (int i = 0; i < tables.size(); ++i) {
        if (tables[i].getName() == t) {
            return &tables[i];
        }
    }
    return nullptr; 
}