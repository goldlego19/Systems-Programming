#pragma once

typedef struct nodeRec {
	int item;
	struct nodeRec* next;
} node;

typedef node* nodePtr;

/* Function Prototypes */

void print(const char* format, ...);
_Bool readInt(const char* prompt, int* value);
void clearInputBuffer();
nodePtr createStack();
_Bool createNode(int n, nodePtr* ptr);
void showNode(nodePtr p);
_Bool push(int n, nodePtr* t);
_Bool pop(nodePtr* t);
_Bool isEmptyStack(nodePtr t);
void showStack(nodePtr t);
int stackSize(nodePtr t);
nodePtr loadStackFromFile(const char* fileName);