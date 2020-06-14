#include "TreeNode.h"
#include "../tables/includeRetcodeTable.h"
#include "RuleType.h"
using namespace std;

TreeNode::TreeNode()
{
    //ctor
}

TreeNode::TreeNode(std::__cxx11::string message, ofstream& logFile){
    this->type = PRINT;
    this->message = message;
    this->logFile = logFile;
}
TreeNode::TreeNode(std::queue<std::__cxx11::string> syscallQueue, RetcodeTable retcodeTable, ofstream& logFile){
    this->type = DO;
    this->syscallQueue = syscallQueue;
    this->retcodeTable = retcodeTable;
    this->logFile = logFile;
}

TreeNode::~TreeNode()
{
    //dtor
}

/*void TreeNode::setNext(std::__cxx11::string message) {
    next = TreeNode(message);
}
void TreeNode::setNext(std::queue<std::__cxx11::string> syscallQueue, RetcodeTable retcodeTable){
    next = TreeNode(syscallQueue, retcodeTable);
}*/
void TreeNode::setNext(TreeNode* next){
    this->next = next;
}
string TreeNode::getError(int retcode){
    return retcodeTable.getId(retcode);
}


TreeNode TreeNode::getNext() {
    return *next;
}

RuleType TreeNode::getType() {
    return type;
}

string TreeNode::getMessage() {
    return message;
}

queue<string> TreeNode::getSyscallQueue() {
    return syscallQueue;
}
