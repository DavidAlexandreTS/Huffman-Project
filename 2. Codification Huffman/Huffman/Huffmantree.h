#ifndef HUFFMANTREE_H_
#define HUFFMANTREE_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

typedef struct _HUFFMANTREE huffmanTree;

struct _HUFFMANTREE
{
	void *byte;
	long long int frequency;
	int size;
	huffmanTree *left;
	huffmanTree *right;
};

/*Checks if a node is a leaf*/
bool isLeaf(huffmanTree *ht)
{
	return (ht -> left == NULL && ht -> right == NULL);
}
/*Creates a leaf, receives a byte and byte frequency and return a leaf*/
huffmanTree* createNODE(void *byte, long long int frequency)
{
	huffmanTree *aux = (huffmanTree*) malloc(sizeof(huffmanTree));
	aux->byte = malloc(sizeof(unsigned char));
    *(unsigned char * )aux -> byte = *(unsigned char *) byte;
	aux -> frequency = frequency;
	aux -> left= NULL;
	aux -> right= NULL;
	return(aux);
}

/*Scroll through the tree and informs the size*/
void Tree_size(huffmanTree *ht,int *size)
{
	if(ht!=NULL)
	{
		(*size) ++;
		if(isLeaf(ht)&&(*(unsigned char *)ht->byte=='*')||*(unsigned char *)ht->byte=='\\') (*size)++;
		Tree_size(ht -> left, size);
		Tree_size(ht -> right, size);
	}
}

/*Creates a tree with the frenquencies, the bytes and the children*/
huffmanTree* createTREE(void * byte, long long int frequency, huffmanTree *left, huffmanTree *right)
{
	huffmanTree *aux = (huffmanTree*) malloc(sizeof(huffmanTree));
	aux -> byte = malloc(sizeof(unsigned char));
	*(unsigned char*)aux -> byte = *(unsigned char*)byte;
	aux -> frequency = frequency;
	aux -> left = left;
	aux -> right = right;
	return(aux);
}

/*Checks if the Tree is empty*/
bool isHTempty(huffmanTree *ht)
{
	return (ht == NULL);
}

/*Go to the left in the Tree and return the left child*/
huffmanTree* go_left(huffmanTree *ht)
{
	if (isHTempty(ht)) return NULL;
	
	return ht -> left;
}

/*Go to the right in the Tree and return the right child*/
huffmanTree* go_right(huffmanTree *ht)
{
	if (isHTempty(ht)) return NULL;
	
	return ht -> right;
}

/*Returns the byte nodes*/
void* getBYTE(huffmanTree *ht)
{
	if (isHTempty(ht)) return NULL;
	return ht -> byte;
}

/*Print the Tree in preorder in the file*/
void printHTinFile (huffmanTree *ht,FILE *newfile)
{
	if (!isHTempty(ht))
	{	if(isLeaf(ht)&&(*(unsigned char *)ht->byte=='*'||*(unsigned char *)ht->byte=='\\'))fputc('\\',newfile);
		fputc(*(unsigned char*)getBYTE(ht),newfile);
		printHTinFile(ht -> left, newfile);
		printHTinFile(ht -> right, newfile);
	}
}
/*Checks whether the bit is set at a given position and returns the result*/
int is_bit_i_set(unsigned char c, int i)
{
	unsigned char mask = 1 << i;

	return mask & c;
}

/*Puts a bit in a certain position of a byte*/
unsigned short set_bit(unsigned short c, int i)
{
	unsigned short mask = 1 << i;

	return c | mask;
}

#endif