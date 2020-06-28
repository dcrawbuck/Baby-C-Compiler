// Duncan Crawbuck 2020
// Baby C Compiler

#include "symbol_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int items = 0;
int size = 100;
int offset = 0;

int debugPrint = 0;

void symbolTableInit()
{
	if(debugPrint) printf("symbolTableInit\n");
	table = malloc(sizeof(Symbol*) * size);
}

void insertInto(char* name, int value)
{
	if(debugPrint) printf("insertInto(%s, %d)\n", name, value);
	Symbol* symbol = (Symbol*)malloc(sizeof(Symbol));
	symbol->name = strdup(name);
	symbol->value = value;
	symbol->offset = offset;
	
	offset += 4;

	int hashValue = getHashValue(name, size);

	while (table[hashValue] != NULL) {
		hashValue = (hashValue + 1) % size;
	}
	
	table[hashValue] = symbol;
	items += 1;
	
	if (items >= size) {
		resize();
	}
}

Symbol* lookup(char* name)
{
	if(debugPrint) printf("Symbol_Table.lookup(%s)...", name);
	int hashValue = getHashValue(name, size);
	
	while (table[hashValue] != NULL) {
		if (strcmp(table[hashValue]->name, name) == 0) {
			if(debugPrint) printf(" found!\n");
			return table[hashValue];
		}
		
		hashValue = (hashValue + 1) % size;
	}
	
	if(debugPrint) printf(" NOT FOUND\n");

	return NULL;
}

int getHashValue(char* str, int size)
{
	int hash = 0;
	int i;
	for (i = *str; i; i = *str++) {
		hash = (hash * 10) + i;
	}
	return hash % size;
}

void resize()
{
	if(debugPrint) printf("Symbol_Table.resize(), items: %d\n", items);
	
	int newSize = size + 5;
	Symbol** newTable = malloc(sizeof(Symbol*) * newSize);

	int i;
	for (i = 0; i < size; i++) {
		
		if (table[i] != NULL) {
			Symbol* symbol = table[i];
			int hashValue = getHashValue(symbol->name, newSize);

			while (newTable[hashValue] != NULL) {
				hashValue = (hashValue + 1) % newSize;
			}
			
			newTable[hashValue] = symbol;
			table[i] = NULL;
		}
	}
	
	
	size = newSize;
	table = newTable;
	free(newTable);
}
