#ifndef TABLE_H
#define TABLE_H

#include "row.h"
#include "index.h"

#include <vector>
#include <unordered_map>

class Table {
public:
	Table() = default;
	Table(const std::string&);
	Table(const std::string&, const std::vector<std::string>&, int);
	void insertRow(const Row&);
	void updateRow(int, const Row&);
	std::vector<Row> selectAll() const;
	Row selectRow(int);
	void selectRowNum(int);
	void select(const std::vector<std::string>&) const;
	void deleteRow(int);
	std::string getName() const;
	void show() const;
	bool loadFromFile(const std::string&, Row&) const;
	bool loadFromFile(const std::string&);
    bool saveToFile(const std::string&, const Row&) const;
    bool meetCondition(const Row&, const std::string&);
    bool hasIndexOn(const std::string&) const;
    Index& getIndex(const std::string&);
    void createIndex(const std::string&, int);
private:
	std::vector<Row> rows;
	std::string name;
	std::vector<std::string> rowFiles;
	std::unordered_map<std::string, Index*> indexes;
	int order;
	std::vector<std::string> columns;
	std::string generateFileName(int) const;
};

#endif // TABLE_H