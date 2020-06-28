// Duncan Crawbuck 2020
// Baby C Compiler

#include "your_code.h"

#ifndef CODE_GEN_H
#define CODE_GEN_H

// This is the function that generates ILOC code after the construction of the AST
void GenerateILOC(ASTNode* node);

int Expr(ASTNode* node);
int GetNextReg();
int GetNextLoopCount();

#endif
