#include "UserOutput.h"
#include <string>
#include <fstream>
using namespace std;

void successMessage(ofstream& userLog) {
     userLog << "Command successfully executed" << endl;
 }

 void badRetcodeError (int retcode, ofstream& userLog) {
     userLog << "Program terminated with a " << retcode << " return code" << endl;
 }

 void userError(string message, ofstream& userLog) {
     userLog << message << endl;
 }
