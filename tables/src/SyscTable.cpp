#include "../include/SyscTable.h"
#include "../include/FieldTable.h"
#include "../../output/compilationOutput.h"

using namespace std;

SyscTable::SyscTable()
{
    //ctor
}

SyscTable::~SyscTable()
{
    //dtor
}


void SyscTable::insertSyscall(string sysc_id, FieldTable field_table) {
    if (isAdded(sysc_id)) {
        compilationError("0001\tMultiple syscall definitions: " + sysc_id);
    }
    else {
        table.insert({sysc_id, field_table});
    }
}

FieldTable SyscTable::getFieldTable(string sysc_id) {
        if (!isAdded(sysc_id)) {
            compilationError("0002\tSyscall" + sysc_id + "not initialized");
            return FieldTable();
        }
        else {
            map<string, FieldTable>::iterator it  = table.find(sysc_id);
            return it->second;
        }
}

bool SyscTable::isAdded (string syscID) {
    map<string, FieldTable>::iterator it  = table.find(syscID);
    return (it != table.end());
}

queue<string> SyscTable::makeRequestQueue() {
    queue <string> requestQueue;
    string request;
    map<string, FieldTable>::iterator it = table.begin();
    while (it != table.end()) {
        request = it -> second.makeRequest();
        requestQueue.push(request);
        it++;
    }
    return requestQueue;
}

int SyscTable::getSize() {
    return table.size();
}

void SyscTable::setNewFieldTable(string syscallID, FieldTable newTable) {
    map<string, FieldTable>::iterator it  = table.find(syscallID);
    if (it != table.end()) {
        it -> second = newTable;
    }
}
