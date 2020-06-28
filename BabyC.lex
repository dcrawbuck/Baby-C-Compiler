%{
#include <stdio.h>
#include <string.h>
#include "your_code.h"
#include "BabyC.tab.h"

void yyerror (const char *s) 
{
   printf("ERROR on line %d: %s.\n", yylineno, s);
   exit(1);
}


%}

/*Option to get the line number*/
%option yylineno

/*We are not using yywrap. So, use this option to disable it and supress a compile error*/
%option noyywrap

%%
"," return ',';
";" return ';';
"+" return '+';
"-" return '-';
"*" return '*';
"/" return '/';
"=" return '=';
"(" return '(';
")" return ')';
"{" return '{';
"}" return '}';

"||" return OR;
"&&" return AND; 
"==" return EQ;
"!=" return NE;
"<=" return LE;
">=" return GE;
"<" return LT;
">" return GT;

"int" return INT;
"main" return MAIN;
"if"  return IF;
"else" return ELSE;
"while" return WHILE;

[a-zA-z][a-zA-Z0-9]*        yylval.string = strdup(yytext); return IDENT; // This is the action for IDENT. Write the regular expression before the action.
(0|[1-9][0-9]*)    	yylval.num = atoi(yytext); return NUM; // This is the action for NUM. Write the regular expression before the action.

[ \t\n]+		//Whitespace is ignored
.           printf( "ERROR on Line %d: Unrecognized token \n", yylineno ); exit(1); //No match. Fatal error.


