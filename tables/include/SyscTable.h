#ifndef SYSCTABLE_H
#define SYSCTABLE_H

#include <map>
#include <string>
#include <queue>
#include "FieldTable.h"

class SyscTable
{
    public:
        SyscTable();
        virtual ~SyscTable();
        void insertSyscall (std::__cxx11::string sysc_id, FieldTable field_table);
        std::queue <std::__cxx11::string> makeRequestQueue();
        FieldTable getFieldTable (std::__cxx11::string sysc_id);
        bool isAdded (std::__cxx11::string syscID);
        void setNewFieldTable(std::__cxx11::string syscallID, FieldTable newTable);
        int getSize();

    protected:

    private:
        std::map <std::__cxx11::string, FieldTable> table;

};

#endif // SYSCTABLE_H
