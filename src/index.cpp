#include "../include/index.h"

Index::Index(int order) : btree(order) 
{
}

void Index::createIndex(const std::vector<Row>& rows, const std::string& indexed) {
	indexedColumn = indexed;
	for (int i = 0; i < rows.size(); ++i) {
		std::string key = rows[i].getFieldValue(indexedColumn);
		btree.insert(key);
		keyToRowMap[key] = rows[i];
	}
}

void Index::insert(const std::string& key, const Row& record) {
	btree.insert(key);
	keyToRowMap[key] = record;
}

void Index::remove(const std::string& key, const Row& record) {
	btree.remove(key);
	keyToRowMap.erase(key);
}

std::vector<Row> Index::search(const std::string& key) const {
	std::vector<Row> result;
    auto range = keyToRowMap.equal_range(key);
    for (auto it = range.first; it != range.second; ++it) {
        result.push_back(it->second);
    }
    return result;
}