#include <iostream>
#include "compilationOutput.h"
 using namespace std;


 void warning(string message) {
     cout << message << endl;
 }

  void compilationError (string message) {
     cout << "Compilation error:\t" << message << endl;
 }
