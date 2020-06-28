// Duncan Crawbuck 2020
// Baby C Compiler

#include "your_code.h"
#include "symbol_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern void yyerror(const char* s);

// Write the implementations of the functions that do the real work here

ASTNode* CreateNumNode(int num)
{
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	
	node->type = ASTNODE_NUM;
	node->num = num;
	
	return node;
}

ASTNode* CreateIdentNode(char* name)
{
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = ASTNODE_IDENT;
	
	node->name = name;
	
	Symbol* symbol = lookup(name);
	if (symbol != NULL) {
		node->symbol = symbol;
	}
	else {
		yyerror("Ident not declared");
	}
	
	return node;
}

// Take a statement node and a statement list node and connect them together
// to form a bigger statement list node (add the statement to the statement list).
// Return a pointer to the bigger list that resulted from this linking
ASTNode* CreateStatementListNode(ASTNode* st, ASTNode* stList)
{
	// Link statement nodes together
	st->next = stList;
	
	return st;
}

ASTNode* CreateAdditionNode(ASTNode* expr, ASTNode* term)
{
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	
	node->type = ASTNODE_ARITH_OP;
	node->op = ADD_OP;
	node->left = expr;
	node->right = term;
	
	return node;
}

ASTNode* CreateSubtractionNode(ASTNode* expr, ASTNode* term)
{
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	
	node->type = ASTNODE_ARITH_OP;
	node->op = SUB_OP;
	node->left = expr;
	node->right = term;
	
	return node;
}

ASTNode* CreateMultiplicationNode(ASTNode* term, ASTNode* factor)
{
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	
	node->type = ASTNODE_ARITH_OP;
	node->op = MULT_OP;
	node->left = term;
	node->right = factor;
	
	return node;
}

ASTNode* CreateDivisionNode(ASTNode* term, ASTNode* factor)
{
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	
	node->type = ASTNODE_ARITH_OP;
	node->op = DIV_OP;
	node->left = term;
	node->right = factor;
	
	return node;
}

ASTNode* CreateAssignmentNode(ASTNode* lhs, ASTNode* expr)
{
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	
	node->type = ASTNODE_ASSIGN;
	node->left = lhs;
	node->right = expr;
	
	return node;
}

ASTNode* CreateIfNode(ASTNode* cond, ASTNode* body)
{
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	
	node->type = ASTNODE_IF;
	node->left = cond;
	node->middle = body;
	
	return node;
}

ASTNode* CreateIfElseNode(ASTNode* cond, ASTNode* body, ASTNode* elseNode)
{
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	
	node->type = ASTNODE_IF;
	node->left = cond;
	node->middle = body;
	node->right = elseNode;
	
	return node;
}

ASTNode* CreateOrNode(ASTNode* left, ASTNode* right)
{
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	
	node->type = ASTNODE_LOGIC_OP;
	node->left = left;
	node->right = right;
	node->op = OR_OP;
	
	return node;
}

ASTNode* CreateAndNode(ASTNode* left, ASTNode* right)
{
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	
	node->type = ASTNODE_LOGIC_OP;
	node->left = left;
	node->right = right;
	node->op = AND_OP;
	
	return node;
}

ASTNode* CreateCondNode(ASTNode* left, char* op, ASTNode* right)
{
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	
	node->type = ASTNODE_COMPARE;
	node->left = left;
	node->right = right;
	node->name = op;
	
	return node;
}

ASTNode* CreateOpNode(char* op)
{
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	
	node->type = ASTNODE_COMPARE;
	node->name = op;
	
	return node;
}

ASTNode* CreateWhileNode(ASTNode* cond, ASTNode* body)
{
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	
	node->type = ASTNODE_WHILE;
	node->left = cond;
	node->right = body;
	
	return node;
}

void AddDeclaration(char* name)
{
	Symbol* symbol = lookup(name);
	if (symbol != NULL) {
		char error[100];
		strcpy(error, "Multiple declarations of ");
		strcat(error, "'");
		strcat(error, name);
		yyerror(strcat(error, "'"));
	}
	else {
		insertInto(name, 1);
	}
}
