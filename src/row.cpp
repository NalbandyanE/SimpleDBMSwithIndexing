#include "../include/row.h"

#include <iostream>

Row::Row() = default;

void Row::addField(const Field& f) {
	fields.push_back(f);
}

std::string Row::getFieldName() {
	for (int i = 0; i < fields.size(); ++i) {
		return fields[i].getName();
	}
	return "";
}

std::string Row::getFieldValue(const std::string& name) const {
	for (int i = 0; i < fields.size(); ++i) {
		if (fields[i].getName() == name) {
			return fields[i].getValue();
		}
	}
	return "";
}

std::vector<Field> Row::getFields() const {
	return fields;
}

Field Row::getField(const std::string& name) const {
	for (int i = 0; i < fields.size(); ++i) {
		if (fields[i].getName() == name) {
			return fields[i];
		}
	}
	return Field("","");
}

void Row::setField(const std::string& field_name, const std::string& new_value) {
	for (Field& field : fields) {
        if (field.getName() == field_name) {
            field.setValue(new_value);
            return;
        }
    }
    std::cout << "Error: Field '" << field_name << "' not found." << std::endl;
}