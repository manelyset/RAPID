#ifndef RETCODETABLE_H
#define RETCODETABLE_H

#include <map>
#include <string>
#include <fstream>

class RetcodeTable
{
    public:
        RetcodeTable();
        RetcodeTable(std::ofstream& logFile);
        virtual ~RetcodeTable();
        void insertRetcode (int retcode, std::__cxx11::string error_id);
        std::__cxx11::string getId (int retcode);

    protected:

    private:
        std::ofstream logFile;
        std::map <int, std::__cxx11::string> table;
};

#endif // RETCODETABLE_H
