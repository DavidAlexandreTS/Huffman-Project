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


void put2(Comp_HT * ht,void *byte ,int number,void * chave)
{
	int key = (*(unsigned char*)chave)%MAX_HASH_SIZE;
	ht->table[key] = (Comp_element *)malloc(sizeof(Comp_element));
	ht->table[key]->byte = malloc(sizeof(unsigned char));
	*(unsigned char*)ht->table[key]->byte = *(unsigned char*)byte;
	ht->table[key]->number_of_bits = number;
}
