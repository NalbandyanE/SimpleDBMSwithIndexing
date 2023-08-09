#ifndef INDEX_H
#define INDEX_H

#include "row.h"
#include "btree.h"

#include <string>
#include <vector>
#include <unordered_map>

class Index {
public:
	Index(int);
	void createIndex(const std::vector<Row>&, const std::string&);
    void insert(const std::string&, const Row&);
    void remove(const std::string&, const Row&);
    std::vector<Row> search(const std::string&) const;
private:
	BTree<std::string> btree;
	std::string indexedColumn;
	std::unordered_map<std::string, Row> keyToRowMap;
};

#endif // INDEX_H