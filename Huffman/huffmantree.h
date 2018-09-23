#ifndef HUFFMANTREE_H_
#define HUFFMANTREE_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
typedef struct _HUFFMANTREE huffmanTree;
struct _HUFFMANTREE{
	void *byte;
	long long int frequency;
	int size;
	huffmanTree *left;
	huffmanTree *right;
};
huffmanTree* createNODE(void * byte, long long int frequency);

huffmanTree* createTREE(void * byte, long long int frequency, huffmanTree *left, huffmanTree *right);

bool isHTempty(huffmanTree *ht);

bool isLeaf(huffmanTree *ht);

huffmanTree* go_left(huffmanTree *ht);

huffmanTree* go_right(huffmanTree *ht);

void * getBYTE(huffmanTree *ht);

long long int getFREQ(huffmanTree *ht);
void printNODE(huffmanTree *ht);

void printHTinFile (huffmanTree * ht,FILE *new);
void destroyHTREE(huffmanTree *ht);

#endif
