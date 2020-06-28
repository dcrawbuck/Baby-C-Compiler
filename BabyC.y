// Duncan Crawbuck 2020
// Baby C Compiler

%{
	#include <stdio.h>
	#include "your_code.h"

// The parser needs to call the scanner to get the next token 
	extern int yylex();

// The error function 
	extern int yyerror(const char *);

// The ASTNode root
    extern ASTNode* gASTRoot;
%}

// Put any initialization code here
%initial-action 
{

}

%token <string> EQUAL "="
%token <string> LT "<"
%token <string> GT ">"
%token <string> LE "<="
%token <string> GE ">="
%token <string> EQ "=="
%token <string> NE "!="
%token OR "||"
%token AND "&&"
%token MAIN "main"
%token INT "int"
%token IF "if"
%token ELSE "else"
%token WHILE "while"

// Define the types for the grammar attributes ($$, $1, $2, ...)
%union 
{
	struct ASTNode* node; // Most $$ values will be ASTNodes
	int num; // Integer numbers
	char* string; // Strings for identifiers 
}

// Type for each token.
// Only needed for IDENT and NUM, because they are the only ones that have actual regexp rules
%token <string> IDENT
%token <num> NUM

// Type for each non-terminal in the grammar.
%type <node> Statement
%type <node> Assignment
%type <node> LHS
%type <node> Expr
%type <node> Term
%type <node> Factor
%type <node> Goal
%type <node> DeclarationList
%type <node> StatementList
%type <node> Declaration
%type <node> IfElse
%type <node> Condition
%type <node> ConditionAnd
%type <node> Compare
%type <string> Op
%type <node> While1

%%

Goal: "main" '(' ')' '{' DeclarationList StatementList '}' { gASTRoot=$6; } // Store the AST root node in gASTRoot
;

DeclarationList: { $$ = NULL; }
	| Declaration DeclarationList
;

StatementList: { $$ = NULL; }
	 | Statement StatementList	{ $$ = CreateStatementListNode($1, $2); printf("Adding a Statement to a Statement list \n"); }
;

Declaration: "int" IDENT ';' { AddDeclaration($2); printf("Processing declaration of %s\n", $2); }
;

Statement: Assignment { $$ = $1; }
	| IfElse { $$ = $1; }
	| While1 { $$ = $1; }
;

Assignment: LHS '=' Expr ';' { $$ = CreateAssignmentNode($1, $3); printf("Creating Assignment node\n"); }
;

LHS: IDENT { $$ = CreateIdentNode($1); printf("Creating left-hand IDENT node for %s\n", $1); }
;

Expr: Term { $$ = $1; }
	| Expr '+' Term { $$ = CreateAdditionNode($1, $3); printf("Creating Addition node\n"); }
	| Expr '-' Term { $$ = CreateSubtractionNode($1, $3); printf("Creating Subtraction node\n"); }
;

Term: Factor { $$ = $1; }
	| Term '*' Factor { $$ = CreateMultiplicationNode($1, $3); printf("Creating Multiplication node\n"); }
	| Term '/' Factor { $$ = CreateDivisionNode($1, $3); printf("Creating Division node\n"); }
;

Factor: IDENT { $$ = CreateIdentNode($1); printf("Creating IDENT node for %s\n", $1);}
	| NUM { $$ = CreateNumNode($1); printf("Creating NUM node for %d\n", $1); }
	| '(' Expr ')'	{ $$ = $2; printf("Creating Expression node in parentheses\n"); }
;

IfElse: "if" '(' Condition ')' '{' StatementList '}' { $$ = CreateIfNode($3, $6); printf("Creating if Statement node\n"); }
| "if" '(' Condition ')' '{' StatementList '}' ELSE '{' StatementList '}' { $$ = CreateIfElseNode($3, $6, $10); printf("Creating if-else Statement node\n"); }
;

Condition: Condition "||" ConditionAnd { $$ = CreateOrNode($1, $3);  printf("Creating OR node\n"); }
	| ConditionAnd { $$ = $1; }
;

ConditionAnd: ConditionAnd "&&" Compare { $$ = CreateAndNode($1, $3); printf("Creating AND node\n"); }
	| Compare { $$ = $1; }
;

Compare: Expr Op Expr { $$ = CreateCondNode($1, $2, $3); printf("Creating Compare node\n"); }
;

Op:   EQ { $$ = "EQ"; }
	| NE { $$ = "NE"; }
	| GT { $$ = "GT"; }
	| LT { $$ = "LT"; }
	| LE { $$ = "LE"; }
	| GE { $$ = "GE"; }
;

While1: "while" '(' Condition ')' '{' StatementList '}' { $$ = CreateWhileNode($3, $6); printf("Creating while loop node\n"); }
;

%%
