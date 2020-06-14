#ifndef COMMANDTABLE_H
#define COMMANDTABLE_H


class CommandTable
{
    public:
        CommandTable();
        virtual ~CommandTable();
        void insertCommand (std::__cxx11::string command_id, TreeNode *tree);
        TreeNode *getTree (std::__cxx11::string command_id);

    protected:

    private:
        std::map <std::__cxx11::string, TreeNode*> table;

};

#endif // COMMANDTABLE_H
