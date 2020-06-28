# Baby-C-Compiler
*Project for CSC 151 (Compiler Construction) at CSUS*

Parses and generates ILOC code for Baby-C programs.

## Parsing
The Bison file `BabyC.y` contains the Baby-C grammar and embedded actions that generate the abstract syntax tree (AST) and symbol table.
The embedded actions call functions in `your_code.c/h` which create AST nodes and symbol table entries.

## Code Generation
Using the generated AST and symbol table from parsing, `code_gen.c` generates ILOC code using virtual registers and outputs to `.iloc` file.

### Baby-C
Simplified version of C that includes variable declarations, expressions, assignments, if/else and while loops.
Program consists of a single main function, and all variables are integers.

Conditions consist of arbitrary number of logical comparisons linked with `&&` or `||` operators.
Logical comparisons consist of two expressions related by one operator: `==` `!=` `>` `>=` `<` `<=`

### ILOC
Abstract assembly code as described in *Engineering a Compiler (Second Edition)* by Keith D. Cooper & Linda Torczon.

## Example
### Baby-C program
```
main() {
    int x;
    int y; 

    while (x > 0 || y < 100) {
        x = x + 1;
        y = 3 * x;
    }
}
```

### ILOC code output
```
L1_C:
	loadAI rarp, 0 -> r1
	loadi 0 -> r2
	cmp_GT r1, r2 -> r3
	loadAI rarp, 4 -> r4
	loadi 100 -> r5
	cmp_LT r4, r5 -> r6
	or r3, r6 -> r7
	cbr r7 -> L1_B, L1_O
L1_B:
	loadAI rarp, 0 -> r8
	loadi 1 -> r9
	add r8, r9 -> r10
	storeAI r10 -> rarp, 0
	loadi 3 -> r11
	loadAI rarp, 0 -> r12
	mult r11, r12 -> r13
	storeAI r13 -> rarp, 4
	jumpi -> L1_C
L1_O:
```
