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

#include "SyscTable.h"
#include "TagDB.h"
#include "FieldTable.h"
#include "ErrorTable.h"
#include "RetcodeTable.h"
#include "CompilationOutput.h"
#include "../NAS_client/NAS_client.h"
extern int yylex ();
void yyerror (char const *);
%}

TagDB database;
SyscTable generalSyscallTable;
ErrorTable generalErrorTable;

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
 
%glr-parser
%%
syscall: 
		SYSCALL IDENTIFIER '{' field_list '}' tag_list {  
			generalSyscallTable.insertSyscall ($2, $4);
			for (vector<string>::iterator it = $6.begin(); it < $6.end(); it++) {
				database.insertSyscallTag (*it, $2);
			}
		}
		
tag_list:       { $$ = new vector<string>; } 
				| tag_list TAG { $1.push_back($2); }
				
field_list: { $$ = new FieldTable(); }
			| field_list IDENTIFIER '[' DEC_NUM ']' ';' tag_list {
				$1.insertField ($2, $4);
				for (vector<string>::iterator it = $6.begin(); it < $6.end(); it++) {
				database.insertFieldTag (*it, $2);
			}
			
			| field_list IDENTIFIER '[' DEC_NUM ']' '=' HEX_NUM ';' tag_list {
				$1.insertField ($2, $4, $7);
				for (vector<string>::iterator it = $8.begin(); it < $8.end(); it++) {
				database.insertFieldTag (*it, $2);
			}
			
			
error: ERROR IDENTIFIER '{' STRING '}' { generalErrorTable.insertError($2, $4); }

command: COMMAND IDENTIFIER '{' rules_list '}' {
								if ($4 == 0)
									successMessage();
							}
rules_list: | rules_list rule {$$ = $2} //TODO

rule:	DO IDENTIFIER field_assignment_list error_list ';' {
			SyscTable callingTable = database.getSyscalls($2);
			queue<string> syscallQueue = callingTable.makeRequestQueue();
			string answer, errorId;
			int retcode = 0;
			while (!syscallQueue.empty() && retcode == 0) {
				answer = nasclient::send_command(syscallQueue.front(), SERVER_IP, SERVER_PORT); 
				syscallQueue.pop()
				retcode = stoi(answer.substr(4, 4), 0, 16); 
			} 

			if (retcode != 0) {
				errorId = $4.getId(retcode);
				if (errorId == "0") {
					badRetcodeError (retcode);
				}
				else {
					userError (generalErrorTable.getMessage(errorId));
				}
			}
			$$ = retcode;
		}	
			
		
error_list:
		| ','  { $$ = new RetcodeTable(); }
		| error_list ',' ERROR '=' HEX_NUM ',' IDENTIFIER { $1.insertRetcode(stoi($5, NULL, 16), $7); }
		
field_assignment_list: 
		| ':' IDENTIFIER '=' HEX_NUM { database.setFieldValues ($2, $4, generalSyscallTable); }
		| field_assignment_list ',' IDENTIFIER '=' HEX_NUM { database.setFieldValues ($3, $5, generalSyscallTable); }


%%
int main ()
{
  yydebug=1;
  return yyparse ();
}
void yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s); 
}