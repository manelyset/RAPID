#ifndef ERRORTABLE_H
#define ERRORTABLE_H

#include <map>
#include <string>

class ErrorTable
{
    public:
        ErrorTable();
        virtual ~ErrorTable();
        void insertError (std::__cxx11::string error_id, std::__cxx11::string error_message);
        std::__cxx11::string getMessage (std::__cxx11::string error_id);

    protected:

    private:
        std::map <std::__cxx11::string, std::__cxx11::string> table;

};

#endif // ERRORTABLE_H
