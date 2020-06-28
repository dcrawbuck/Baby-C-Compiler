// Duncan Crawbuck 2020
// Baby C Compiler

#include "symbol_table.h"

#ifndef YOUR_CODE_H
#define YOUR_CODE_H

typedef enum{ASTNODE_ARITH_OP, ASTNODE_LOGIC_OP, ASTNODE_COMPARE, ASTNODE_ASSIGN, ASTNODE_IDENT, ASTNODE_NUM, ASTNODE_IF, ASTNODE_WHILE } ASTNodeType;

// Define all operation types (add, mult, etc) here.
typedef enum { ADD_OP, SUB_OP, MULT_OP, DIV_OP, OR_OP, AND_OP } ASTOp;

typedef struct ASTNode ASTNode;
struct ASTNode {
	ASTNodeType type; 
    ASTOp op; // The actual operation (add, mult, etc)
	int num;  //Need to store the actual value for number nodes
	char *name; //Need to store the actual variable name for ident nodes
	ASTNode* left; // Left child
	ASTNode* right; // Right child
	ASTNode* middle; // middle child (only used in If/Else)
	
	// The following pointer is just a suggestion; you don't have to use it if you have a better design.
	ASTNode* next; // a pointer used to link statement nodes together in a statement list

	// Depending on your implementation, you may need to add other fields to this struct
	Symbol* symbol;
};


// Add functions to create the different kinds of ASTNodes 
// These functions are called by the code embedded in the grammar.
// Here are some samples:  
ASTNode* CreateNumNode(int num);
ASTNode* CreateIdentNode(char* name);
ASTNode* CreateStatementListNode(ASTNode* st, ASTNode* stList);

ASTNode* CreateAdditionNode(ASTNode* expr, ASTNode* term);
ASTNode* CreateSubtractionNode(ASTNode* expr, ASTNode* term);
ASTNode* CreateMultiplicationNode(ASTNode* term, ASTNode* factor);
ASTNode* CreateDivisionNode(ASTNode* term, ASTNode* factor);

ASTNode* CreateAssignmentNode(ASTNode* lhs, ASTNode* expr);

ASTNode* CreateIfNode(ASTNode* cond, ASTNode* body);
ASTNode* CreateIfElseNode(ASTNode* cond, ASTNode* body, ASTNode* elseNode);

ASTNode* CreateOrNode(ASTNode* left, ASTNode* right);
ASTNode* CreateAndNode(ASTNode* left, ASTNode* right);
//ASTNode* CreateCondNode(ASTNode* left, ASTNode* op, ASTNode* right);
ASTNode* CreateCondNode(ASTNode* left, char* op, ASTNode* right);

ASTNode* CreateOpNode(char* op);

ASTNode* CreateWhileNode(ASTNode* cond, ASTNode* body);

// Need a function to add a declaration to your symbol table
void AddDeclaration(char* name);

#endif
