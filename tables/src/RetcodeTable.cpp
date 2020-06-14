#include "../include/RetcodeTable.h"
#include "../../output/compilationOutput.h"
#include "../../output/userOutput.h"
#include <fstream>

using namespace std;

RetcodeTable::RetcodeTable()
{
    //ctor
}

RetcodeTable::~RetcodeTable()
{
    //dtor
}

RetcodeTable::RetcodeTable(ofstream& logFile)
{
    this->logFile = logFile;
}

void RetcodeTable::insertRetcode(int retcode, string error_id) {
    table.insert({retcode, error_id});
}

string RetcodeTable::getId(int retcode) {
    map<int,string>::iterator it  = table.find(retcode);
    if (it == table.end()) {
        badRetcodeError(retcode, logFile);
        return "0";
    }

    return it->second;
}
