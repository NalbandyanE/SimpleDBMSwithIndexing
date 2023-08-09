#ifndef DBMS_H
#define DBMS_H

#include "table.h"

#include <string>
#include <vector>

class DBMS {
public:
	DBMS() = default;
	DBMS(const std::string&);
	void createTable(const std::string&);
	void showTable(const Table&) const;
	void dropTable(const std::string&);
	void addTable(const Table&);
	const Table* getTable(const std::string&) const;
private:
	std::vector<Table> tables;
	std::string name;
};

#endif // DBMS_H