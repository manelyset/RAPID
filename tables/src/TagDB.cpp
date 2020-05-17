#include "TagDB.h"
#include <map>
#include "SyscTable.h"
#include "FieldTable.h"
#include <iostream>

using namespace std;

TagDB::TagDB()
{
    //ctor
}

TagDB::~TagDB()
{
    //dtor
}

void TagDB::insertSyscallTag (string tagName, string syscallID){
    table.insert({tagName,TagInfo(syscallID)});
}

void TagDB::insertFieldTag (string tagName, string syscallID, string fieldID){
    table.insert({tagName,TagInfo(syscallID, fieldID)});
}

SyscTable TagDB::getSyscalls (string tagName, SyscTable globalTable){
    SyscTable syscallTable;
    pair <multimap <string, TagInfo>::iterator, multimap <string, TagInfo>::iterator> range = table.equal_range(tagName);
    while (range.first != range.second) {
        if (range.second -> second.type == syscall_tag && !syscallTable.isAdded(range.first -> second.sysc_id)) {
            syscallTable.insertSyscall(range.first -> second.sysc_id, globalTable.getFieldTable(range.first -> second.sysc_id));
        }
        range.first++;
    }
    return syscallTable;
}

void TagDB::setFieldValues (string tagName, string value, SyscTable & syscallTable) {
    pair <multimap <string, TagInfo>::iterator, multimap <string, TagInfo>::iterator> range = table.equal_range(tagName);
    while (range.first != range.second) {
        if (range.first -> second.type == field_tag) {
            string syscallID = range.first -> second.sysc_id;
            if (syscallTable.isAdded(syscallID)) {
                FieldTable newTable;
                newTable = syscallTable.getFieldTable(syscallID);
                newTable.setValue(range.first -> second.field_id, value);
                syscallTable.setNewFieldTable(syscallID, newTable);
            }
        }
        range.first++;
    }
}





