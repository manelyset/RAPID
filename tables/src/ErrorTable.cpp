#include "ErrorTable.h"
#include "compilationOutput.h"
#include <cstddef>

using namespace std;

ErrorTable::ErrorTable()
{
    //ctor
}

ErrorTable::~ErrorTable()
{
    //dtor
}

TreeNode* ErrorTable::getTree(string error_id) {
    map<string, TreeNode*>::iterator it  = table.find(error_id);
    if (it == table.end()) {
        runtimeError("0002\tError "+error_id+" not initialized");
        return nullptr;
    }

    return it->second;
}

void ErrorTable::insertError(string error_id, TreeNode* tree) {
    map<string, TreeNode*>::iterator it  = table.find(error_id);
    if (it != table.end()) {
        runtimeError("0001\tMultiple error definitions:" + error_id);
    }
    else {
        table.insert({error_id, tree});
    }

}
