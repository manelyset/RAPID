#include "../NAS_client/NAS_client.h"
#include "tree/TreeNode.h"
#include "tree/RuleType.h"
#include "tables/include/ErrorTable.h"
#include "output/compilationOutput.h"

int sendSyscalls (queue<string> syscallQueue) {
    string answer, errorId;
    int retcode = 0;
    while (!syscallQueue.empty() && retcode == 0) {
        answer = nasclient::send_command(syscallQueue.front(), SERVER_IP, SERVER_PORT);
        syscallQueue.pop()
        retcode = stoi(answer.substr(4, 4), 0, 16);
    }
    return retcode;
}

void interpreter (TreeNode* tree, ErrorTable errorTable) {
    if (tree == nullptr)
        return;
    RuleType type = (*tree).getType();
    switch(type) {
    case PRINT:
        userError((*tree).getMessage());
        interpreter((*tree).getNext(), errorTable);
    case DO:
        int retcode = sendSyscalls((*tree).getSyscallQueue());
        if (retcode == 0) {
            interpreter((*tree).getNext(), errorTable);
        }
        else {
            string error_id = (*tree).getError(retcode);
            TreeNode* newTree = errorTable.getTree(error_id);
            interpreter(newTree, errorTable);
        }
    }
}




