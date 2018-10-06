#ifndef COMPRESS_H
#define COMPRESS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Heap.h"
#include "Hash.h"
#include "Huffmantree.h"
#include "Compress_Hash.h"
#include "Base.h"
/*Creates a header for the compressed file*/
unsigned char* Create_header(int trash_size,int tree_size)
{
	unsigned char *bytes = (unsigned char*) malloc(sizeof(3*sizeof(unsigned char)));
	bytes[0] =  trash_size << 5 | tree_size >> 8;
	bytes[1] =  tree_size;
	return (bytes);
}

/* Sets a new value to one byte and places it in the Hash*/
void set(huffmanTree * bt,Comp_HT* ht,int height,unsigned int *byte)
{
	if(bt!=NULL)
	{
		if(isLeaf(bt))
		{
			byte[height]=2;
			another_put(ht,byte,height,bt->byte);
		}
		byte[height]=0;
		set(bt -> left, ht, height + 1, byte);
		byte[height]=1;
		set(bt -> right, ht, height + 1,byte) ;
	}
}
/*It receives the file to be compressed, collects the frequencies of each byte and places them in a Hash,
then creates a Heap with the values of the frequencies and bytes.
From the Heap a tree is formed, from this tree another Hash is created, with the new byte values.
Reads the file to be compressed and creates a compressed file from the original and the second Hash.*/
void compress(char *name)
{
	hash_table *ht = create_hash();
	unsigned char byte;
	char exit[10000];
	int i;
	short tam = strlen(name);
	FILE *entrada,*saida;
	entrada = fopen(name, "rb");
	getchar();

	while(entrada==NULL)
	{
		puts("Invalid name\nType other");
		gets(name);
		entrada = fopen(name,"rb");
	}

	for(i = 0;i < tam;i ++) exit[i] = name[i];
	exit[i]='.';
	exit[i + 1] = 'h';
	exit[i + 2] = 'u';
	exit[i + 3] = 'f';
	exit[i + 4] = 'f';
	exit[i + 5] = '\0';

	printf("%s\n", exit);
	saida = fopen(exit, "wb");
	fputc(0, saida);
	fputc(0, saida);
	int file_size = 0;
	rewind(entrada);

	while(!feof(entrada))
	{
		byte = fgetc(entrada);
		if(!feof(entrada))
		{
			file_size ++;
			put(ht, &byte);
		}
	}
	printf("\nAll the bytes of this archive are on the Hash\n");

	Heap *heap = create_heap();
	huffmanTree * new_node = NULL;
	for(i = 0;i < 256;i ++)
	{
    	if(ht->table[i]!=NULL)
    	{
    		new_node = createNODE(ht->table[i]->byte,ht->table[i]->frequency);
    		enqueue(heap,new_node);
		}
	}

	huffmanTree * arvore = createHTfromHEAP(heap);
	puts("Created A HuffmanTree with the Hash");

	Comp_HT* nometemp = create_Comp_HT();
	printHTinFile(arvore,saida);
	puts("Got all the compressed bits for the archive");
	rewind(entrada);
	unsigned int *array = (unsigned int *)malloc(sizeof(unsigned int)*20);
	set(arvore, nometemp, 0, array);
	unsigned char Final_Byte = 0;
	unsigned int *bits;
	unsigned char temp;
	short bits_not_shifted = 7;
	short bits_number;
	short bits_int = (sizeof(unsigned short)*8);
	puts("Starting the compression of archive");
	printf("\n");
	while(!feof(entrada))
	{
		byte = fgetc(entrada);
		if(!feof(entrada))
		{
			bits_number = nometemp -> table[byte % MAX_HASH_SIZE] -> number_of_bits;
			bits = nometemp->table[byte% MAX_HASH_SIZE]->byte;
			for(i=0;i<bits_number;i++)
			{
				if(bits[i]==1) Final_Byte = set_bit(Final_Byte,bits_not_shifted);
				if(bits_not_shifted==0) {
					fputc(Final_Byte,saida);
					Final_Byte =0;
					bits_not_shifted =7;
				}
				else
				bits_not_shifted--;
			}
		}
	}
	puts("Compressed the archive");
	int trash = (bits_not_shifted+1)%8;
	if(trash!=0){
	fputc(Final_Byte,saida);
	}
	printf("%d\n",trash);
	rewind(saida);
	puts("Creating header");
	unsigned char *cabecalho;
	int tree_size = 0;
	Tree_size(arvore, &tree_size);
	cabecalho = Create_header(trash, tree_size);
	fputc(cabecalho[0], saida);
	fputc(cabecalho[1], saida);
	puts("End(closing the archives)");
	fclose(entrada);
	fclose(saida);
}

#endif