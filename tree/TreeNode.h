#ifndef TREENODE_H
#define TREENODE_H

#include <queue>
#include <fstream>
#include "RuleType.h"
#include "../tables/includeRetcodeTable.h"

class TreeNode
{
    public:
        TreeNode();
        TreeNode(std::__cxx11::string message, std::ofstream& logFile);
        TreeNode(std::queue<std::__cxx11::string> syscallQueue, RetcodeTable retcodeTable, std::ofstream& logFile);
        virtual ~TreeNode();

        //void setNext(std::__cxx11::string message);
        //void setNext(std::queue<std::__cxx11::string> syscallQueue, RetcodeTable retcodeTable);
        void setNext(TreeNode* next);
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
        TreeNode *next;
        std::ofstream logFile;

};

#endif // TREENODE_H
