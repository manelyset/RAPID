%option noyywrap
%top{
  #include <iostream>
  #include <stdlib.h>
  #include "rapid.tab.h"
  using namespace std;
}
%%
[ \t\n]               ;
[:alpha:_][[:alpha:][:digit:]_]* {yylval.val = yytext; return IDENTIFIER;}
[0-9]+               {yylval.val = atoi(yytext); return DEC_NUM;}
"0x"[[0-9][a-f][A-F]]+          {/*yylval.val = stoi(yytext, NULL, 16);*/ yylval.val = yytext; return HEX_NUM;}

"syscall "               return SYSCALL;
"command "               return COMMAND;
"do "                    return DO;
"error "                 return ERROR;
"print "                 return PRINT;
'#'[[:alpha:][:digit:]_]+ {yylval.val = yytext.substr(1, yytext.length() - 1); return TAG;}


"{"                 return '{';
"}"                 return '}';
":"                 return ':';
"["                 return '[';
"]"                 return ']';
";"                 return ';';
","                 return ',';
"="                 return '=';
"\""                return '"';
"//"[^\n]*"\n"      return COMMENT;
\"[^\"]\"           {yylval.val = yytext; return STRING;}
<<EOF>>             ; 
%%