// Duncan Crawbuck 2020
// Baby C Compiler

#include "code_gen.h"
#include "your_code.h"
#include "symbol_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE* output;

void GenerateILOC(ASTNode* node)
{
	if (node != NULL) {
		// Create output file "testx.iloc"
		output = fopen("testx.iloc", "w");
		
		// Start with root node
		Expr(node);

		// Close output file
		fclose(output);
	}
}


int Expr(ASTNode* node)
{
	int debugPrint = 0;
	int t1 = 0, t2 = 0, result = 0, loopCount = 0;
	Symbol* symbol;
	
	if (node != NULL) {
		// ASTNodeType { ASTNODE_ARITH_OP, ASTNODE_LOGIC_OP, ASTNODE_COMPARE, ASTNODE_ASSIGN, ASTNODE_IDENT, ASTNODE_NUM, ASTNODE_IF, ASTNODE_WHILE }
		switch (node->type) {
			case ASTNODE_ARITH_OP:
				if (debugPrint) fprintf(output, "ASTNODE_ARITH_OP\n");
				t1 = Expr(node->left);
				t2 = Expr(node->right);
				result = GetNextReg();
				
				fprintf(output, "\t");
				
				// ASTOp { ADD_OP, SUB_OP, MULT_OP, DIV_OP }
				switch (node->op) {
					case ADD_OP:
						fprintf(output, "add");
						break;
						
					case SUB_OP:
						fprintf(output, "sub");
						break;
						
					case MULT_OP:
						fprintf(output, "mult");
						break;
						
					case DIV_OP:
						fprintf(output, "div");
						break;
					default:
						fprintf(output, "ERROR: Invalid arthimetic operation: %d", node->op);
						break;
				}
				
				fprintf(output, " r%d, r%d -> r%d\n", t1, t2, result);
				break;
				
			case ASTNODE_LOGIC_OP:
				if (debugPrint) fprintf(output, "ASTNODE_LOGIC_OP\n");
				// TODO: ASTNODE_LOGIC_OP
				
				if (node->left == NULL) {
					fprintf(output, "ERROR: node->left = NULL");
					break;
				}
				if (node->right == NULL) {
					fprintf(output, "ERROR: node->right = NULL");
					break;
				}
				
				t1 = Expr(node->left);
				t2 = Expr(node->right);
				result = GetNextReg();
				
				fprintf(output, "\t");
				// ASTOp { AND_OP, OR_OP }
				switch (node->op) {
					case AND_OP:
						fprintf(output, "and");
						break;
						
					case OR_OP:
						fprintf(output, "or");
						break;
						
					default:
						fprintf(output, "ERROR: Invalid arthimetic operation: %d", node->op);
						break;
				}

				fprintf(output, " r%d, r%d -> r%d\n", t1, t2, result);
				
				break;
				
			case ASTNODE_COMPARE:
				if (debugPrint) fprintf(output, "ASTNODE_COMPARE\n");
				
				if (node->left != NULL) {
					if (debugPrint) fprintf(output, "->LEFT\n");
					t1 = Expr(node->left);
				}
				else {
					fprintf(output, "ERROR: node->left = NULL");
					break;
				}
				if (node->right != NULL) {
					if (debugPrint) fprintf(output, "->RIGHT\n");
					t2 = Expr(node->right);
				}
				else {
					fprintf(output, "ERROR: node->right = NULL");
					break;
				}
				
				result = GetNextReg();
				
				fprintf(output, "\tcmp_%s r%d, r%d -> r%d\n", node->name, t1, t2, result);
				
				break;
				
			case ASTNODE_ASSIGN:
				if (debugPrint) fprintf(output, "ASTNODE_ASSIGN\n");
				if (node->right != NULL) {
					if (debugPrint) fprintf(output, "->RIGHT\n");
					t2 = Expr(node->right);
				}
				else {
					fprintf(output, "ERROR: node->right = NULL");
					break;
				}
				if (node->left->name == NULL) {
					fprintf(output, "ERROR: node->left->name = NULL");
					break;
				}
				
				
				symbol = lookup(node->left->name);
				if (symbol == NULL) {
					fprintf(output, "ERROR: lookup(node->name) = NULL");
					break;
				}
				
				fprintf(output, "\tstoreAI r%d -> rarp, %d\n", t2, symbol->offset);
				break;
				
			case ASTNODE_IDENT:
				if (debugPrint) fprintf(output, "ASTNODE_IDENT\n");
				result = GetNextReg();

				symbol = lookup(node->name);
				if (symbol == NULL) {
					fprintf(output, "ERROR: lookup(node->name) = NULL");
					break;
				}
				
				fprintf(output, "\tloadAI rarp, %d -> r%d\n", symbol->offset, result);

				break;
				
			case ASTNODE_NUM:
				if (debugPrint) fprintf(output, "ASTNODE_NUM\n");
				result = GetNextReg();
				fprintf(output, "\tloadi %d -> r%d\n", node->num, result);
				break;
				
			case ASTNODE_IF:
				if (debugPrint) fprintf(output, "ASTNODE_IF\n");
				// TODO: ASTNODE_IF
				
				loopCount = GetNextLoopCount();
				
				if (node->left == NULL) {
					fprintf(output, "ERROR: node->left = NULL");
					break;
				}
				
				if (debugPrint) fprintf(output, "->LEFT\n");
				// Condition
				t1 = Expr(node->left);
				
//				fprintf(output, "\tcbr r%d -> L%d_T, L%d_M\n", t1, loopCount, loopCount);
				fprintf(output, "\tcbr r%d -> L%d_T, L%d_", t1, loopCount, loopCount);
				
				if (node->right == NULL) {
					// No else
					fprintf(output, "M\n");
				}
				else {
					// Else
					fprintf(output, "E\n");
				}
				
				fprintf(output, "L%d_T:\n", loopCount);
				// THEN
				
				if (node->middle == NULL) {
					fprintf(output, "ERROR: node->middle = NULL");
					break;
				}
				if (debugPrint) fprintf(output, "->MIDDLE\n");
				Expr(node->middle);
				
				
				// ELSE?
				if (node->right != NULL) {
					fprintf(output, "\tjumpi -> L%d_M\n", loopCount);
					fprintf(output, "L%d_E:\n", loopCount);

					if (debugPrint) fprintf(output, "->RIGHT\n");
					Expr(node->right);
				}
				
				fprintf(output, "L%d_M:\n", loopCount);
				// AFTER (node-> called automatically after switch)
				
				break;
				
			case ASTNODE_WHILE:
				if (debugPrint) fprintf(output, "ASTNODE_WHILE\n");
				// TODO: ASTNODE_WHILE
				
				loopCount = GetNextLoopCount();
				
				// CONDITION
				fprintf(output, "L%d_C:\n", loopCount);
				
				if (node->left == NULL) {
					fprintf(output, "ERROR: node->left = NULL");
					break;
				}
				if (debugPrint) fprintf(output, "->LEFT\n");
				// Condition
				t1 = Expr(node->left);
				
				fprintf(output, "\tcbr r%d -> L%d_B, L%d_O\n", t1, loopCount, loopCount);
				
				
				// BODY
				fprintf(output, "L%d_B:\n", loopCount);
				
				if (node->right == NULL) {
					fprintf(output, "ERROR: node->right = NULL");
					break;
				}
				if (debugPrint) fprintf(output, "->RIGHT\n");
				
				Expr(node->right);
				
				fprintf(output, "\tjumpi -> L%d_C\n", loopCount);
				
				
				// AFTER
				fprintf(output, "L%d_O:\n", loopCount);
				// (node-> called automatically after switch)
				break;
				
			default:
				if (debugPrint) fprintf(output, "default\n");
				fprintf(output, "node->type: %d\n", node->type);
				// TODO: Error
				break;
		}
	}
	
	// If node is in StatementList then node->next will be not NULL
	//	fprintf(output, "NEXT check\n");
	if (node != NULL) {
		//		fprintf(output, ">");
		if (node->next != NULL) {
			// Execute next statement in list
			if (debugPrint) fprintf(output, "->NEXT\n");
			Expr(node->next);
		}
		//		fprintf(output, "\n");
	}
	
	return result;
}

int currentRegister = 0;

int GetNextReg()
{
	currentRegister += 1;
	return currentRegister;
}

int currentLoopCount = 0;

int GetNextLoopCount()
{
	currentLoopCount += 1;
	return currentLoopCount;
}
