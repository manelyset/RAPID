#include "ErrorTable.h"
#include "compilationOutput.h"

using namespace std;

ErrorTable::ErrorTable()
{
    //ctor
}

ErrorTable::~ErrorTable()
{
    //dtor
}

string ErrorTable::getMessage(string error_id) {
    map<string, string>::iterator it  = table.find(error_id);
    if (it == table.end()) {
        runtimeError("0002\tError "+error_id+" not initialized");
        return "0";
    }

    return it->second;
}

void ErrorTable::insertError(string error_id, string error_message) {
    map<string, string>::iterator it  = table.find(error_id);
    if (it != table.end()) {
        runtimeError("0001\tMultiple error definitions:" + error_id);
    }
    else {
        table.insert({error_id, error_message});
    }

}
