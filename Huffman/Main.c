#include "Compress.h"
int get_dot(char * s)
{
	int i,tam = strlen(s);
	for(i=0;i<tam;i++)
	{
		if(s[i]=='.') return i;
	}
	return -1;
}
int main()
{
	hash_table * ht = create_hash();
	char name[100],exit[100];
	unsigned char byte;
	//inicio da compressao
	printf("Type your file name\n");
	gets(name);
	short dot = get_dot(name);
	for(int i=0;i<dot;i++) exit[i] = name[i];
	strcat(exit,".huff");
	FILE *entrada,*saida;
	entrada = fopen(name,"rb");
	saida = fopen(exit,"wb");
	int file_size=0;
	while(!feof(entrada)) {
		byte = fgetc(entrada);
		if(byte=='*') byte = '/';
		if(!feof(entrada))
		{
		//	printf("%c",byte);
			file_size++;
		put(ht,&byte);
		}
	}
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
	puts("\nend");
	unsigned char Final_Byte =0;
	unsigned char bits;
	short bits_not_shifted =8;
	short bits_number;
	i=0;
	while(!feof(entrada)&&i<file_size) 	{
		byte = fgetc(entrada);
		if(byte =='*') byte = '/';
		bits_number = nometemp->table[byte]->number_of_bits;
		bits = *(unsigned char*)nometemp->table[byte]->byte;
		if(bits_not_shifted==0)  {
			fputc(Final_Byte,saida);
			bits_not_shifted = 8;
			Final_Byte = 0;
		}
		if(bits_not_shifted>=bits_number) {
				bits_not_shifted = bits_not_shifted - bits_number;
				Final_Byte |= (bits<<(bits_not_shifted));
			}
		else  {
			Final_Byte |= (bits>>(bits_number-bits_not_shifted));
			fputc(Final_Byte,saida);
			bits_not_shifted = 8-(bits_number-bits_not_shifted);
			Final_Byte = 0;
			Final_Byte|= (bits<<bits_not_shifted);
		}
		i++;
	}
	fputc(Final_Byte,saida);
	int trash = bits_not_shifted;
	rewind(saida);
	unsigned char *cabecalho;
	cabecalho = Create_header(trash,arvore->size);
	fprintf(saida,"%s",cabecalho);
	puts("Real end");
	fclose(entrada);
	fclose(saida);
	//fim da compressao
}
