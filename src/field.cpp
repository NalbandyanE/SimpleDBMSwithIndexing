#include "../include/field.h"

Field::Field(const std::string& name, const std::string& value) : name{name}, value{value}
{
}

std::string Field::getName() const {
	return name;
}

std::string Field::getValue() const {
	return value;
}

void Field::setName(const std::string& n) {
	name = n;
}

void Field::setValue(const std::string& v) {
	value = v;
}