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
TagDB database;
SyscTable generalSyscallTable;
ErrorTable generalErrorTable;
CommandTable generalCommandTable;
ofstream userLog ("userLog.txt");
%}

%union {
    std::__cxx11::string text;
	int number;
	vector<string> string_vector;
	FieldTable field_table;
	TreeNode rule;
	pair<TreeNode, TreeNode> rules_list;
	RetcodeTable retc_table;
} 

%token<text> IDENTIFIER
%token<number> DEC_NUM
%token<number> HEX_NUM
%token<text> STRING
%token SYSCALL
%token COMMAND
%token DO
%token ERROR
%token PRINT
%token COMMENT
%token<text> TAG

%type<field_table> field_list
%type<string_vector> tag_list
%type<retc_table> error_list
%type<rules_list> rules_list
%type<rule> rule
 
%glr-parser
%%
syscall: 
		SYSCALL IDENTIFIER '{' field_list '}' tag_list {  
			generalSyscallTable.insertSyscall ($2, $4);
			for (std::vector<std::__cxx11::string>::iterator it = ($6).begin(); it < ($6).end(); it++) {
				database.insertSyscallTag (*it, $2);
			}
		}
		
tag_list:       { $$ = new std::vector<std::__cxx11::string>; } 
				| tag_list TAG { ($1).push_back($2); }
				
field_list:  { $$ = new FieldTable(); }
			| field_list IDENTIFIER '[' DEC_NUM ']' ';' tag_list {
				$1.insertField ($2, $4);
				for (std::vector<std::__cxx11::string>::iterator it = ($7).begin(); it < ($7).end(); it++) {
				database.insertFieldTag (*it, $2); }
			}
			
			| field_list IDENTIFIER '[' DEC_NUM ']' '=' HEX_NUM ';' tag_list {
				$1.insertField ($2, $4, $7);
				for (std::vector<std::__cxx11::string>::iterator it = ($9).begin(); it < ($9).end(); it++) {
				database.insertFieldTag (*it, $2); }
			}
			
			
err: ERROR IDENTIFIER '{' rules_list '}' { generalErrorTable.insertError($2, ($4).first); }

cmd: COMMAND IDENTIFIER '{' rules_list '}' {generalCommandTable.insertCommand($2, ($4).first)}
			
rules_list:   rule  {$$ = std::make_pair((*($1)), (*($1)));}
			| rules_list rule {
				(*($1).second).setNext($2);
				($1).second = ($1).second.getNext();
				$$ = $1;
			} 

rule:	  DO IDENTIFIER field_assignment_list error_list ';' {
			SyscTable callingTable = database.getSyscalls($2);
			std::queue<string> syscallQueue = callingTable.makeRequestQueue();
			$$ = TreeNode(syscallQueue, $4);
		}
		| PRINT STRING {
			$$ = TreeNode($2);
		}
			
		
error_list: { $$ = new RetcodeTable(); }
		| ','  { $$ = new RetcodeTable(); }
		| error_list ',' ERROR '=' HEX_NUM ',' IDENTIFIER { ($1).insertRetcode(stoi($5, NULL, 16), $7); }
		
field_assignment_list:
		| ':' IDENTIFIER '=' HEX_NUM { database.setFieldValues ($2, $4, generalSyscallTable); }
		| field_assignment_list ',' IDENTIFIER '=' HEX_NUM { database.setFieldValues ($3, $5, generalSyscallTable); }


%%
int main ()
{
  yydebug=1;
  std::__cxx11::string command = "start";
  yyparse ();
  while (command != end) {
	interpreter(command, generalCommandTable, generalErrorTable);
	std::cin >> command;
  }
  return 0;
}
void yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s); 
}