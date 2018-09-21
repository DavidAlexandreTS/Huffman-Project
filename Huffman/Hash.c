#include "Hash.h"

hash_table * create_hash()
{
	int i;
	hash_table * new_ht = (hash_table*) malloc(sizeof(hash_table));
	for(i=0;i<MAX_HASH_SIZE;i++)
	{
		new_ht->table[i]= NULL;
	}
	return new_ht;
}

element * create_element(void * data,size_t data_size)
{
	element * newelement = (element *)malloc(sizeof(element));
	newelement->elemento = malloc(data_size);
	*(unsigned char*)(newelement->elemento) = *(unsigned char*)data;
	newelement->frequency =1;
	return newelement;
}
void put(hash_table * ht,void * data)
{
	int key;
	key = (*(int *)data%MAX_HASH_SIZE);
	if(ht->table[key]!=NULL)
	{
		ht->table[key]->frequency++;
	}
	else
	{
		ht->table[key]=create_element(data,sizeof(unsigned char));
	}
}
