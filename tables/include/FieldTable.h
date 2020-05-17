#ifndef FIELDTABLE_H
#define FIELDTABLE_H

#include <vector>
#include <string>

struct field_info {
    std::__cxx11::string fieldID;
    int field_size;
    std::__cxx11::string value;
    field_info(std::__cxx11::string fieldID, int field_size) {
        this -> fieldID = fieldID;
        this -> field_size = field_size;
        this -> value = std::__cxx11::string(field_size, '0');
    }
};

class FieldTable
{
    public:
        FieldTable();
        virtual ~FieldTable();
        void insertField (std::__cxx11::string field_id, int field_size);
        void insertField (std::__cxx11::string field_id, int field_size, std::__cxx11::string value);
        void setValue(std::__cxx11::string field_id, std::__cxx11::string value);
        std::__cxx11::string makeRequest();
        std::__cxx11::string getValue (std::__cxx11::string fieldID);

    protected:

    private:
        std::vector<field_info>::iterator findFieldID(std::__cxx11::string ID);
        std::vector <field_info> table;
};

#endif // FIELDTABLE_H
