#include "userOutput.h"
#include <string>
#include <fstream>
using namespace std;

void successMessage() {
	 ofstream userLog;
	 userLog.open("../log.txt");
     userLog << "Command successfully executed" << endl;
	 userLog.close();
 }

 void badRetcodeError (int retcode) {
	 ofstream userLog;
	 userLog.open("../log.txt");
     userLog << "Program terminated with a " << retcode << " return code" << endl;
	 userLog.close();
 }

 void userError(string message) {
	 ofstream userLog;
	 userLog.open("../log.txt");
     userLog << message << endl;
	 userLog.close();
 }
