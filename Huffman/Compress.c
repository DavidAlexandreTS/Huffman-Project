#include "Compress.h"
void bin(int x)
{
	if (x/2==0)
	{
		printf("%d",x%2);
	}
	else
	{
	bin(x/2);
	printf ("%d",x%2);
    }
}
unsigned char* Create_header(int trash_size,int tree_size)
{
	unsigned char *bytes = (unsigned char*) malloc(sizeof(3*sizeof(unsigned char)));
	bytes[0] =  trash_size<<5 | tree_size>>8;
	bytes[1] =  tree_size;
	return (bytes);
}
void set (huffmanTree * bt,Comp_HT* ht,int height,unsigned char byte)
{
	if(bt!=NULL)
	{
		if(isLeaf(bt)) put2(ht,&byte,height,bt->byte);
		 set(bt->left,ht,height+1,byte<<1);
		 set(bt->right,ht,height+1,(byte<<1)+1);
	}
}
int get_dot(char * s)
{
	int i,tam = strlen(s);
	for(i=0;i<tam;i++)
	{
		if(s[i]=='.') return i;
	}
	return -1;
}
void compress(char * name)
{
	hash_table * ht = create_hash();
	unsigned char byte;
	char exit[100];
	int i;
	short dot = get_dot(name);
	for(i=0;i<dot;i++) exit[i] = name[i];
	printf("%s\n",exit);
	exit[i]='.';
	exit[i+1] = 'h';
	exit[i+2] = 'u';
	exit[i+3] = 'f';
	exit[i+4] = 'f';
	exit[i+5] = '\0';
	//strcat(exit,".huff");
	FILE *entrada,*saida;
	entrada = fopen(name,"rb");
	saida = fopen(exit,"wb");
	fprintf(saida,"%c%c",0,0);
	int file_size=0;
	while(!feof(entrada)) {
	byte = fgetc(entrada);
	printf("%c ",byte);
	if(byte=='*') byte = '/';
		if(!feof(entrada))
		{
		file_size++;
		put(ht,&byte);
		}
	}
printf("\nAll the bytes of this archive are on the Hash\n");
Heap *heap = create_heap();
huffmanTree * new_node;
for(i=0;i<256;i++) {
	if(ht->table[i]!=NULL){
		new_node = createNODE(ht->table[i]->elemento,ht->table[i]->frequency);
		enqueue(heap,new_node);
	}
}
huffmanTree * arvore = createHTfromHEAP(heap);
puts("Created A HuffmanTree with the Hash");
Comp_HT* nometemp = create_Comp_HT();
printHTinFile(arvore,saida);
puts("Got all the compressed bits for the archive");
rewind(entrada);
set(arvore,nometemp,0,0);
unsigned char Final_Byte =0;
unsigned char bits;
short bits_not_shifted =8;
short bits_number;
i=0;
puts("Starting the compression of archive");
while(!feof(entrada)&&i<file_size) 	{
	byte = fgetc(entrada);
	if(byte =='*') byte = '/';
	bits_number = nometemp->table[byte]->number_of_bits;
	bits = *(unsigned char*)nometemp->table[byte]->byte;
	if(bits_not_shifted==0)  {
		bin(Final_Byte);
		printf("\n");
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
		bin(Final_Byte);
		printf("\n");
		fputc(Final_Byte,saida);
		bits_not_shifted = 8-(bits_number-bits_not_shifted);
		Final_Byte = 0;
		Final_Byte|= (bits<<bits_not_shifted);
	}
	i++;
}
puts("Compressed the archive");
printf("Byte with trash (last byte) : ");
bin(Final_Byte);
puts("");
fputc(Final_Byte,saida);
int trash = bits_not_shifted;
rewind(saida);
puts("Creating header");
unsigned char *cabecalho;
cabecalho = Create_header(trash,arvore->size);
fprintf(saida,"%s",cabecalho);
puts("End(closing the archives)");
fclose(entrada);
fclose(saida);
}
