#include "TreeNode.h"
#include "RetcodeTable.h"
#include "RuleType.h"
using namespace std;

TreeNode::TreeNode()
{
    //ctor
}

TreeNode::TreeNode(std::__cxx11::string message){
    this.type = PRINT;
    this.message = message;
}
TreeNode::TreeNode(std::queue<std::__cxx11::string> syscallQueue, RetcodeTable retcodeTable){
    this.type = DO;
    this.syscallQueue = syscallQueue;
    this.retcodeTable = retcodeTable;
}

TreeNode::~TreeNode()
{
    //dtor
}

void TreeNode::setNext(std::__cxx11::string message) {
    next = TreeNode(message);
}
/*void TreeNode::setNext(std::queue<std::__cxx11::string> syscallQueue, RetcodeTable retcodeTable){
    next = TreeNode(syscallQueue, retcodeTable);
}
void TreeNode::setNext(TreeNode next){
    this.next = next;
}*/
string TreeNode::getError(int retcode){
    return retcodeTable.getId(retcode);
}


TreeNode TreeNode::getNext() {
    return next;
}

RuleType TreeMode::getType() {
    return type;
}

string TreeNode::getMessage() {
    return message;
}

queue<string> TreeNode::getSyscallQueue() {
    return syscallQueue;
}
