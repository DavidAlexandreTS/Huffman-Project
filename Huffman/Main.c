#include "Compress.h"
#include "Decompress.h"
int main()
{
	char name[100];
	int dec=0;
	//inicio da compressao
	puts("Type your file name");
	scanf("%[^\n]s",name);
	puts("type 1 if you want to compress this file");
	puts("or 2 if you want to decompress this file");
	while(dec<1||dec>2){
	if(scanf("%d",&dec)==1){
		if(dec ==1)
		compress(name);
		else if(dec==2){
			Decompress_File(name);
		}
		}
	}
	//fim da compressao
return 0;
}
