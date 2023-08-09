#ifndef FIELD_H
#define FIELD_H

#include <string>

class Field {
public:
	Field(const std::string&, const std::string&);
	std::string getName() const;
	std::string getValue() const;
	void setName(const std::string&);
	void setValue(const std::string&); 
private:
	std::string name;
	std::string value;
};

#endif // FIELD_H