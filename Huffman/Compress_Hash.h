#ifndef COMPRESS_HASH_H
#define COMPRESS_HASH_H
#include <stdio.h>
#include <stdlib.h>
#include "Hash.h"
typedef struct comp_hash_table Comp_HT;
typedef struct comp_element
{
	void * byte;
	int number_of_bits;
}Comp_element;
struct comp_hash_table
{
	Comp_element* table[MAX_HASH_SIZE];
};
Comp_HT* create_Comp_HT();
void put2(Comp_HT * ht,void *byte ,int number,void * chave);
#endif
