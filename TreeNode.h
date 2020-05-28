#ifndef TREENODE_H
#define TREENODE_H

#include <queue>
#include "RuleType.h"
#include "RetcodeTable.h"

class TreeNode
{
    public:
        TreeNode();
        TreeNode(std::__cxx11::string message);
        TreeNode(std::queue<std::__cxx11::string> syscallQueue, RetcodeTable retcodeTable);
        virtual ~TreeNode();

        //void setNext(std::__cxx11::string message);
        //void setNext(std::queue<std::__cxx11::string> syscallQueue, RetcodeTable retcodeTable);
        void setNext(TreeNode next);
        TreeNode getNext();
        std::__cxx11::string getMessage();
        RuleType getType();
        std::queue<std::__cxx11::string> getSyscallQueue();
        std::__cxx11::string getError(int retcode);

    protected:


    private:
        RuleType type;
        std::__cxx11::string message;
        std::queue<std::__cxx11::string> syscallQueue;
        RetcodeTable retcodeTable;
        TreeNode next;
};

#endif // TREENODE_H
