#include "TreeNode.h"
#include "CommandTable.h"
#include "../output/compilationOutput.h"
using namespace std;

CommandTable::CommandTable()
{
    //ctor
}


CommandTable::~CommandTable()
{
    //dtor
}

void CommandTable::insertCommand (string command_id, TreeNode *tree) {
    map<string, TreeNode*>::iterator it  = table.find(command_id);
    if (it != table.end()) {
        compilationError("0001\tMultiple command definitions:" + command_id);
    }
    else {
        table.insert({command_id, tree});
    }
}

TreeNode* CommandTable::getTree (string command_id) {
    map<string, TreeNode*>::iterator it  = table.find(command_id);
    if (it == table.end()) {
        compilationError("0002\tCommand "+command_id+" not initialized");
        return nullptr;
    }

    return it->second;
}
