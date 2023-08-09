#ifndef ROW_H
#define ROW_H

#include "field.h"

#include <vector>

class Row {
public:
	Row();
	void addField(const Field&);
	std::string getFieldValue(const std::string&) const;
	std::string getFieldName();
	std::vector<Field> getFields() const;
	Field getField(const std::string&) const;
	void setField(const std::string&, const std::string&);
private:
	std::vector<Field> fields;
};

#endif // ROW_H