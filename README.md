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
    loadAI rarp, 0 -> r1
    loadi 3 -> r2
    cmp_EQ r1, r2 -> r3
    cbr r3 -> L1_T, L1_M
L1_T:
    loadAI rarp, 8 -> r4
    loadi 2 -> r5
    sub r4, r5 -> r6
    storeAI r6 -> rarp, 4
L1_M:
```
