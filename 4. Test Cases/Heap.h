#ifndef Heap_H
#define Heap_H
#include <stdio.h>
#include <stdlib.h>
#include "huffmantree.h"
#define MAX_HEAP_SIZE 257
typedef struct Heap Heap;
struct Heap
{
	huffmanTree *data[MAX_HEAP_SIZE];
	long long int size;
};
int is_empty(Heap *hipi);
/*verifica se a Heap está vazia*/
int get_parent_index(Heap *hipi, int i);
//pega o indice do pai
int get_left_index(Heap *hipi, int i);
//pega o indice do filho esquerdo
int get_right_index(Heap *hipi, int i);
//pega o indice do filho direito
int item_of(Heap *hipi, int i);
//pega o item de um indice
Heap* create_heap();
//cria a Heap
void swap(huffmanTree **a, huffmanTree **b);
//troca os dados entre dois ponteiros
void enqueue(Heap *hipi, huffmanTree * ht);
void Tree_size(huffmanTree * ht,int * size);
void min_heapify(Heap *hipi, int i);
void heapsort(Heap *hipi);
void *dequeue(Heap *hipi);
void print_heap(Heap *hipie, int aux);
huffmanTree* createHTfromHEAP(Heap *heap);
#endif
