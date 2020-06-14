#ifndef ERRORTABLE_H
#define ERRORTABLE_H

#include <map>
#include <string>
#include "../../tree/TreeNode.h"

class ErrorTable
{
    public:
        ErrorTable();
        virtual ~ErrorTable();
        void insertError (std::__cxx11::string error_id, TreeNode* tree);
        TreeNode* getTree (std::__cxx11::string error_id);

    protected:

    private:
        std::map <std::__cxx11::string, TreeNode*> table;

};

#endif // ERRORTABLE_H
