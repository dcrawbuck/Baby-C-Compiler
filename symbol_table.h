// Duncan Crawbuck 2020
// Baby C Compiler

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct Symbol Symbol;
struct Symbol {
	char* name;
	int value;
	int offset;
};

Symbol** table;

void symbolTableInit();

void insertInto(char* name, int value);
struct Symbol* lookup(char* name);

void resize();

int getHashValue(char* name, int size);

#endif
