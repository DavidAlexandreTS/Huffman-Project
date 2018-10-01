#ifndef HASH_H
#define HASH_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_HASH_SIZE 256

typedef struct element element;
typedef struct hash_table hash_table;

struct element
{
	void * byte;
	long long int frequency;
};

 struct hash_table
{
	element *table[256];
};

/*Creates the Hash Table*/
hash_table* create_hash()
{
	int i;
	hash_table *new_ht = (hash_table*) malloc(sizeof(hash_table));
	for(i = 0;i < MAX_HASH_SIZE;i ++)
	{
		new_ht -> table[i]= NULL;
	}
	return new_ht;
}

/*Create Hash elements, in the future they will store the bytes and their frequencies*/
element* create_element(void *data, size_t data_size)
{
	element *newelement = (element*)malloc(sizeof(element));
	newelement -> byte = malloc(data_size);
	*(unsigned char*)(newelement->byte) = *(unsigned char*)data;
	newelement -> frequency = 1;
	return newelement;
}

/*Puts a value in the Hash, in case of reapts increase the frequency*/
void put(hash_table *ht,void *data)
{
	int key;
	key = (*(unsigned char *)data % MAX_HASH_SIZE);
	if(ht -> table[key] != NULL)
	{
		ht -> table[key] -> frequency ++;
	}else
	{
		ht -> table[key] = create_element(data, sizeof(unsigned char));
	}
}

#endif