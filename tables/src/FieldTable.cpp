#include "../include/FieldTable.h"
#include "../../output/compilationOutput.h"
#include <iostream>

using namespace std;

FieldTable::FieldTable()
{
    //ctor
}

FieldTable::~FieldTable()
{
    //dtor
}

vector<field_info>::iterator FieldTable::findFieldID(string ID) {
    vector<field_info>::iterator it;
    for (it = table.begin(); it != table.end(); it++) {
        if (it -> fieldID == ID) {
            return it;
        }
    }
    return table.end();
}

void FieldTable::insertField (string field_id, int field_size) {
    vector<field_info>::iterator it  = findFieldID(field_id);
    if (it != table.end()) {
        compilationError("0001\tMultiple field definitions in one syscall: " + field_id);
    }
    else {
        table.push_back(field_info(field_id, field_size));

    }
}

void FieldTable::insertField(string field_id, int field_size, string value) {
    vector<field_info>::iterator it  = findFieldID(field_id);
    if (it != table.end()) {
        compilationError("0001\tMultiple field definitions in one syscall: " + field_id);
    }
    else {
        field_info *fi = new field_info(field_id, field_size);
        int valueLength = value.length();
        if (valueLength > field_size) {
            warning ("The value of the field " + field_id + " is out of boundaries. " + value.substr(valueLength - field_size, valueLength - 1) + " will be inserted");
            fi -> value = value.substr(valueLength - field_size, valueLength - 1);
        }
        else if (valueLength < field_size){
            fi -> value = string(field_size - valueLength, '0').append(value);
        }
        else {
            fi -> value = value;
        }
        table.push_back (*fi);

    }
}

void FieldTable::setValue(string field_id, string value) {
    vector<field_info>::iterator it  = findFieldID(field_id);
    if (it == table.end()) {
        compilationError("0002\tField " + field_id + "not initialized");
    }
    else {
        int valueLength = value.length();
        int field_size = it -> field_size;
        if (valueLength > field_size) {
            warning ("The value of the field " + field_id + " is out of boundaries. " + value.substr(valueLength - field_size, valueLength - 1) + " will be inserted");
            it -> value = value.substr(valueLength - field_size, valueLength - 1);
        }
        else if (valueLength < field_size){
            it -> value = string(field_size - valueLength, '0').append(value);
        }
        else {
            it -> value = value;
        }
    }
}

string FieldTable::makeRequest() {
    string request("");

	for (vector<field_info>::iterator it = table.begin(); it != table.end(); it++)
	{
		request += it -> value;
	}

	return request;
}

string FieldTable::getValue(string fieldID) {
    vector<field_info>::iterator it = findFieldID(fieldID);
    return it -> value;

}
