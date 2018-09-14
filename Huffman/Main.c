#include "Hash.h"
#include "Heap.h"
#include "huffmantree.h"
void print_pre(huffmanTree * ht)
{
	if(ht!=NULL)
	{
		printf("(%x)",*(char*)ht->byte);
		print_pre(ht->left);
		print_pre(ht->right);
	}
}
int main()
{
	hash_table * ht = create_hash();
	char name[100];
	unsigned char byte;
	//inicio da compressao
	printf("Type your file name\n");
	gets(name);
	FILE *entrada,*saida;
	entrada = fopen(name,"rb");
	saida = fopen("saida.txt","wb");
	int file_size=0;
	while(!feof(entrada)) {
		byte = fgetc(entrada);
		if(!feof(entrada))
		{
			file_size++;
		printf("(%x)",byte);
		put(ht,&byte);
		}
	}
	puts("end");
	Heap *heap = create_heap();
	int i;
	huffmanTree * new_node;
	for(i=0;i<256;i++) {
		if(ht->table[i]!=NULL){
			new_node = createNODE(ht->table[i]->elemento,ht->table[i]->frequency);
			enqueue(heap,new_node);
		}
	}
	huffmanTree * arvore = createHTfromHEAP(heap);
	printHTinFile(arvore,saida);
	fclose(entrada);
	fclose(saida);
	//fim da compressao
}
