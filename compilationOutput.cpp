#include <iostream>
#include "compilationOutput.h"
 using namespace std;

 void successMessage() {
     cout << "Command successfully executed" << endl;
 }

 void runtimeError(string message) {
     cout << "Runtime error:\t" << message << endl;
 }

 void badRetcodeError (int retcode) {
     cout << "Program terminated with a " << retcode << " return code" << endl;
 }

 void userError(string message) {
     cout << message << endl;
 }

 void warning(string message) {
     cout << message << endl;
 }
