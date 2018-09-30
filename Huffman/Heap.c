#include "Heap.h"
#include "huffmantree.h"
int is_empty(Heap *hipi)
{
	return (hipi -> size == 0);
}

int get_parent_index(Heap *hipi, int i)
{
	return i/2;
}

int get_left_index(Heap *hipi, int i)
{
	return 2*i;
}

int get_right_index(Heap *hipi, int i)
{
	return 2*i + 1;
}

int item_of(Heap *hipi, int i)
{
	return *(unsigned char *)hipi -> data[i]->byte;
}

Heap * create_heap ()
{
	int i; 
	Heap * hp = (Heap *) malloc(sizeof(Heap ));
	for(i=0;i<MAX_HEAP_SIZE;i++) hp->data[i]=NULL;
	hp->size =0;
	return hp;
}

void swap(huffmanTree **a, huffmanTree **b)
{
	huffmanTree  *aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void enqueue(Heap *hipi, huffmanTree *ht)
{
	if (hipi -> size >= MAX_HEAP_SIZE)
	{
		printf("Heap Overflow\n");
	}else
	{
		hipi -> data[++hipi -> size] = ht;
		int key_index = hipi -> size;
		int parent_index = get_parent_index(hipi,hipi -> size);

		while (parent_index >= 1 && (hipi ->data[key_index]->frequency) < (hipi -> data[parent_index]->frequency))
		{
			swap(&hipi -> data[key_index], &hipi -> data[parent_index]);
			key_index = parent_index;
			parent_index =  get_parent_index(hipi, key_index);
		}
	}
}



void min_heapify(Heap *hipi, int i)
{
	int lowest;
	int left_index = get_left_index(hipi, i);
	int right_index = get_right_index(hipi, i);

	if (left_index <= hipi -> size && hipi -> data[left_index] -> frequency < hipi -> data[i] -> frequency)
	{
		lowest = left_index;
	}else
	{
		lowest = i;
	}

	if (right_index <= (hipi -> size) && (hipi -> data[right_index] -> frequency) < (hipi -> data[lowest] -> frequency))
	{
		lowest = right_index;
	}

	if (i != lowest)
	{
		swap(&(hipi -> data[i]), &(hipi -> data[lowest]));
		min_heapify(hipi, lowest);
	}
}
void print_heap(Heap *hipi, int aux)
{
	int i = 1;

	while(i <= aux)
	{
		printf("(%c) ",*(unsigned char*) (hipi -> data[i]->byte));
		i ++;
	}
	printf("\n");
}
void Tree_size(huffmanTree * ht,int * size)
{
	if(ht!=NULL)
	{
		(*size)++;
		Tree_size(ht->left,size);
		Tree_size(ht->right,size);
	}
}
void heapsort(Heap *hipi)
{
	int i;
	for (i = hipi -> size; i >= 2; i --)
	{
		swap(&(hipi -> data[1]),&(hipi -> data[i]));
		hipi -> size --;
		min_heapify(hipi, 1);
	}
}
void * dequeue(Heap *hipi)
{
	if (is_empty(hipi))
	{
		printf("Heap Underflow\n");
		return NULL;
	}else
	{
		huffmanTree *item = hipi -> data[1];

		hipi -> data[1] = hipi -> data[(hipi -> size)];
		(hipi -> size) --;
		min_heapify(hipi, 1);

		return item;
	}
}
huffmanTree* createHTfromHEAP(Heap *heap){
	huffmanTree *a,*b,*aux;
	while(heap->size>1) {
		//retira os nos da heap.
		a = dequeue(heap);
		b = dequeue(heap);
		//comentaro a seguir: caso a arvore nao esteja sendo feita corretamente descomente-o
		//if((*(unsigned char*) b->byte)=='*'&&(*(unsigned char*)a->byte)!='*') swap(&a,&b);
		//cria nó com as frequencias somadas e seu char será
		//'*'(ou '\', ainda falta implementar) que é nosso caractere de apoio
		unsigned char multiplicacion = '*';
		aux = createTREE(&multiplicacion, a->frequency + b->frequency, a, b);
		//coloca nossa arvore de volta na heap
		enqueue(heap,aux);
	}
	return dequeue(heap);
}
