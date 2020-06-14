%define parse.trace
// %define lr.type canonical-lr
%{
#define YYDEBUG 1
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5060

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <queue>
#include <string>
#include <fstream>

#include "tables/include/SyscTable.h"
#include "tables/include/TagDB.h"
#include "tables/include/FieldTable.h"
#include "tables/include/ErrorTable.h"
#include "tables/include/RetcodeTable.h"
#include "output/сompilationOutput.h"
#include "output/userOutput.h"
#include "../NAS_client/NAS_client.h"
#include "tree/TreeNode.h"
#include "tree/RuleType.h"
#include "tree/CommandTable.h"
#include "Interpreter.h"
extern int yylex ();
void yyerror (char const *);
%}

TagDB database;
SyscTable generalSyscallTable;
ErrorTable generalErrorTable;
CommandTable generalCommandTable;
ofstream userLog ("userLog.txt");

%token IDENTIFIER
%token DEC_NUM
%token HEX_NUM
%token STRING
%token SYSCALL
%token COMMAND
%token DO
%token ERROR
%token PRINT
%token COMMENT
%token TAG

%type field_list
%type tag_list
%type error_list
%type rules_list
%type rule
 
%glr-parser
%%
syscall: 
		SYSCALL IDENTIFIER '{' field_list '}' tag_list {  
			generalSyscallTable.insertSyscall ($2, $4);
			for (std::vector<std::__cxx11::string>::iterator it = $6.begin(); it < $6.end(); it++) {
				database.insertSyscallTag (*it, $2);
			}
		}
		
tag_list:       { $$ = new std::vector<std::__cxx11::string>; } 
				| tag_list TAG { $1.push_back($2); }
				
field_list: { $$ = new FieldTable(); }
			| field_list IDENTIFIER '[' DEC_NUM ']' ';' tag_list {
				$1.insertField ($2, $4);
				for (std::vector<std::__cxx11::string>::iterator it = $6.begin(); it < $6.end(); it++) {
				database.insertFieldTag (*it, $2);
			}
			
			| field_list IDENTIFIER '[' DEC_NUM ']' '=' HEX_NUM ';' tag_list {
				$1.insertField ($2, $4, $7);
				for (std::vector<std::__cxx11::string>::iterator it = $8.begin(); it < $8.end(); it++) {
				database.insertFieldTag (*it, $2);
			}
			
			
error: ERROR IDENTIFIER '{' rules_list '}' { generalErrorTable.insertError($2, $4.first); }

command: COMMAND IDENTIFIER '{' rules_list '}' {generalCommandTable.insertCommand($2, $4.first)}
			
rules_list:   rule  {$$ = std::make_pair((*$1), (*$1));}
			| rules_list rule {
				(*$1.second).setNext($2);
				$1.second = $1.second.getNext();
				$$ = $1;
			} 

rule:	  DO IDENTIFIER field_assignment_list error_list ';' {
			SyscTable callingTable = database.getSyscalls($2);
			std::queue<string> syscallQueue = callingTable.makeRequestQueue();
			$$ = TreeNode(syscallQueue, $4, userLog);
		}
		| PRINT STRING {
			$$ = TreeNode($2, userLog);
		}
			
		
error_list:
		| ','  { $$ = new RetcodeTable(userLog); }
		| error_list ',' ERROR '=' HEX_NUM ',' IDENTIFIER { $1.insertRetcode(stoi($5, NULL, 16), $7); }
		
field_assignment_list: 
		| ':' IDENTIFIER '=' HEX_NUM { database.setFieldValues ($2, $4, generalSyscallTable); }
		| field_assignment_list ',' IDENTIFIER '=' HEX_NUM { database.setFieldValues ($3, $5, generalSyscallTable); }


%%
int main ()
{
  yydebug=1;
  std::__cxx11::string command = "start";
  userLog.open();
  yyparse ();
  while (command != end) {
	interpreter(command, generalCommandTable, generalErrorTable);
	std::cin >> command;
  }
  userLog.close();
  return 0;
}
void yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s); 
}