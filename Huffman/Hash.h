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
hash_table * create_hash();
element * create_element(void * data,size_t data_size);
void put(hash_table * ht,void * data);
#endif
