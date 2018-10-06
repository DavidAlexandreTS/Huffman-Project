#ifndef Heap_H
#define Heap_H
#include <stdio.h>
#include <stdlib.h>
#include "Huffmantree.h"

#define MAX_HEAP_SIZE 257

typedef struct Heap Heap;

struct Heap
{
	huffmanTree *data[MAX_HEAP_SIZE];
	long long int size;
};

/*Check if the Heap is empty*/
int is_empty(Heap *heap)
{
	return (heap -> size == 0);
}

/*Gets the parent of index*/
int get_parent_index(Heap *heap, int i)
{
	return i/2;
}

/*Gets the left son of index*/
int get_left_index(Heap *heap, int i)
{
	return 2*i;
}

/*Gets the right son of index*/
int get_right_index(Heap *heap, int i)
{
	return 2*i + 1;
}

/*Creates a Heap*/
Heap* create_heap ()
{
	int i; 
	Heap * hp = (Heap *) malloc(sizeof(Heap ));
	for(i = 0;i < MAX_HEAP_SIZE;i ++) hp -> data[i] = NULL;
	hp -> size = 0;
	return hp;
}

/*Swaps the values of two Heap nodes*/
void swap(huffmanTree **a, huffmanTree **b)
{
	huffmanTree  *aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

/*Line a node in the heap*/
void enqueue(Heap *heap, huffmanTree *ht)
{
	if (heap -> size >= MAX_HEAP_SIZE)
	{
		printf("Heap Overflow\n");
	}else
	{
		heap -> data[++heap -> size] = ht;
		int key_index = heap -> size;
		int parent_index = get_parent_index(heap, heap -> size);

		while (parent_index >= 1 && (heap -> data[key_index] -> frequency) < (heap -> data[parent_index] -> frequency))
		{
			swap(&heap -> data[key_index], &heap -> data[parent_index]);
			key_index = parent_index;
			parent_index =  get_parent_index(heap, key_index);
		}
	}
}

/*It maintains the property of min heap, where all parents must be smaller than the children*/
void min_heapify(Heap *heap, int i)
{
	int lowest;
	int left_index = get_left_index(heap, i);
	int right_index = get_right_index(heap, i);

	if (left_index <= heap -> size && heap -> data[left_index] -> frequency < heap -> data[i] -> frequency)
	{
		lowest = left_index;
	}else
	{
		lowest = i;
	}

	if (right_index <= (heap -> size) && (heap -> data[right_index] -> frequency) < (heap -> data[lowest] -> frequency))
	{
		lowest = right_index;
	}

	if (i != lowest)
	{
		swap(&(heap -> data[i]), &(heap -> data[lowest]));
		min_heapify(heap, lowest);
	}
}

/*Deletes a heap node*/
void* dequeue(Heap *heap)
{
	if (is_empty(heap))
	{
		printf("Heap Underflow\n");
		return NULL;
	}else
	{
		huffmanTree *item = heap -> data[1];

		heap -> data[1] = heap -> data[(heap -> size)];
		(heap -> size) --;
		min_heapify(heap, 1);

		return item;
	}
}

/*Creates a Tree with the Heap*/
huffmanTree* createHTfromHEAP(Heap *heap)
{
	huffmanTree *a,*b,*aux;
	while(heap -> size > 1) 
	{
		a = dequeue(heap);
		b = dequeue(heap);
		unsigned char daddy = '*';
		aux = createTREE(&daddy, a -> frequency + b -> frequency, a, b);
		enqueue(heap,aux);
	}
	return dequeue(heap);
}

#endif