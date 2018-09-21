#include "Compress.h"
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
	Comp_HT* nometemp = create_Comp_HT();
	printHTinFile(arvore,saida);
	rewind(entrada);
	set(arvore,nometemp,0,0);
	unsigned char Final_Byte =0;
	unsigned char bits;
	short bits_not_shifted =8;
	short bits_number;
	while(!feof(entrada)) 	{
		byte = fgetc(entrada);
		bits_number = nometemp->table[byte]->number_of_bits;
		bits = nometemp->table[byte]->byte;
		if(bits_not_shifted==0)  {
			fputc(Final_Byte,saida);
			bits_not_shifted = 8;
			Final_Byte = 0;
		}
		else if(bits_not_shifted>=bits) {
			bits_not_shifted -=bits_number;
			Final_Byte |= (bits<<(bits_not_shifted));
		}
		else  {

			fputc(Final_Byte,saida);
				bits_not_shifted = 8;
				Final_Byte = 0;
		}

	}
	fclose(entrada);
	fclose(saida);
	//fim da compressao
}
