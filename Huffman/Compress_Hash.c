#include "Compress_Hash.h"

Comp_HT* create_Comp_HT()
{
	int i;
	Comp_HT* new_ht = (Comp_HT*)malloc(sizeof(Comp_HT));
	for(i=0;i<MAX_HASH_SIZE;i++)
	{
		new_ht->table[i]=NULL;
	}
	return new_ht;
}

void put2(Comp_HT * ht,char byte ,int number)
{
	int key = byte%MAX_HASH_SIZE;
	ht->table[key]->byte = byte;
	ht->table[key]->number_of_bits = number;
}
