#ifndef RETCODETABLE_H
#define RETCODETABLE_H

#include <map>
#include <string>

class RetcodeTable
{
    public:
        RetcodeTable();
        virtual ~RetcodeTable();
        void insertRetcode (int retcode, std::__cxx11::string error_id);
        std::__cxx11::string getId (int retcode);

    protected:

    private:
        std::map <int, std::__cxx11::string> table;
};

#endif // RETCODETABLE_H
