#ifndef COMPILATIONOUTPUT_H_INCLUDED
#define COMPILATIONOUTPUT_H_INCLUDED

#include <string>

void runtimeError (std::__cxx11::string message);
void userError (std::__cxx11::string message);
void badRetcodeError (int retcode);
void warning (std::__cxx11::string message);

void successMessage();

#endif // COMPILATIONOUTPUT_H_INCLUDED
