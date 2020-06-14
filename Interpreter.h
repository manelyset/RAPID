#ifndef INTERPRETER_H_INCLUDED
#define INTERPRETER_H_INCLUDED
#include "tree/CommandTable.h"
#include "tables/include/ErrorTable.h"

void interpreter (std::__cxx11::string command, CommandTable commandTable, ErrorTable errorTable);

#endif // INTERPRETER_H_INCLUDED
