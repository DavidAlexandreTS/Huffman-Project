#ifndef COMPRESS_H
#define COMPRESS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Heap.h"
#include "Hash.h"
#include "Huffmantree.h"
#include "Compress_Hash.h"

/*Creates a header for the compressed file*/
unsigned char* Create_header(int trash_size,int tree_size)
{
	unsigned char *bytes = (unsigned char*) malloc(sizeof(3*sizeof(unsigned char)));
	bytes[0] =  trash_size << 5 | tree_size >> 8;
	bytes[1] =  tree_size;
	return (bytes);
}

/* Sets a new value to one byte and places it in the Hash*/
void set(huffmanTree * bt,Comp_HT* ht,int height,unsigned int byte)
{
	if(bt!=NULL)
	{
		if(isLeaf(bt))
		{
			if(*(unsigned char *)bt -> byte == '*' || *(unsigned char *)bt -> byte == 92)
			{
				byte = byte>>1;
				height --;
			}
			another_put(ht,&byte,height,bt->byte);
		}
		set(bt -> left, ht, height + 1, byte << 1);
		set(bt -> right, ht, height + 1,(byte << 1) + 1);
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
	set(arvore, nometemp, 0, 0);
	unsigned char Final_Byte = 0;
	unsigned int bits;
	unsigned char temp;
	short bits_not_shifted = 8;
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
			bits = *(unsigned int*)nometemp -> table[byte % MAX_HASH_SIZE] -> byte;
			if(bits_not_shifted == 0) 
			{
				fputc(Final_Byte,saida);
				bits_not_shifted = 8;
				Final_Byte = 0;
			}
			if(bits_not_shifted >= bits_number)
			{
				bits_not_shifted = bits_not_shifted - bits_number;
				Final_Byte |= (bits << (bits_not_shifted));
			}else 
			{
				Final_Byte |= (bits >> (bits_number - bits_not_shifted));
				fputc(Final_Byte,saida);
				bits_not_shifted = 8 - (bits_number - bits_not_shifted);
				Final_Byte = 0;
				Final_Byte|= (bits << bits_not_shifted);
			}
		}
	}

	puts("Compressed the archive");
	fputc(Final_Byte,saida);
	if(bits_not_shifted == 8) bits_not_shifted = 0;
	int trash = bits_not_shifted;
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