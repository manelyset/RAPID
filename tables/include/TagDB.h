#ifndef TAGDB_H_INCLUDED
#define TAGDB_H_INCLUDED

#include <map>
#include <string>
#include "SyscTable.h"

enum tag_type {syscall_tag, field_tag};

struct TagInfo {
    tag_type type;
    std::__cxx11::string sysc_id;
    std::__cxx11::string field_id;
    TagInfo (std::__cxx11::string sysc_id) {
        this -> type = syscall_tag;
        this -> sysc_id = sysc_id;
        this -> field_id = "";
    }
    TagInfo (std::__cxx11::string sysc_id, std::__cxx11::string field_id) {
        this -> type = field_tag;
        this -> sysc_id = sysc_id;
        this -> field_id = field_id;
    }
};

class TagDB
{
    public:
        TagDB();
        virtual ~TagDB();
        void insertSyscallTag (std::__cxx11::string tagName, std::__cxx11::string syscallID);
        void insertFieldTag (std::__cxx11::string tagName, std::__cxx11::string syscallID, std::__cxx11::string fieldID);
        SyscTable getSyscalls (std::__cxx11::string tagName, SyscTable globalTable);
        void setFieldValues (std::__cxx11::string tagName, std::__cxx11::string value, SyscTable & syscallTable);

    protected:

    private:
        std::multimap <std::__cxx11::string, TagInfo> table;
};

#endif // TAGDB_H_INCLUDED
