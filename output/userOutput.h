#ifndef USEROUTPUT_H_INCLUDED
#define USEROUTPUT_H_INCLUDED
#include <string>
#include <fstream>

void userError (std::__cxx11::string message, std::ofstream& userLog);
void badRetcodeError (int retcode, std::ofstream& userLog);
void successMessage(std::ofstream& userLog);

#endif // USEROUTPUT_H_INCLUDED
