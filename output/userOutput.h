#ifndef USEROUTPUT_H_INCLUDED
#define USEROUTPUT_H_INCLUDED
#include <string>

void userError (std::__cxx11::string message);
void badRetcodeError (int retcode);
void successMessage();

#endif // USEROUTPUT_H_INCLUDED
