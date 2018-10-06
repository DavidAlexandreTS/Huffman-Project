#include "Compress.h"
#include "Decompress.h"

int main()
{
	char name[100];
	int dec = 0;
	puts("Type 1 if you want to compress this file");
	puts("or 2 if you want to decompress this file");
	while(dec < 1 || dec > 2)
	{
		if(scanf("%d",&dec) == 1)
		{
			getchar();
			puts("Type your file name");
			scanf("%[^\n]s",name);
			if(dec == 1)
				compress(name);
			else if(dec == 2)
			{
				Decompress_File(name);
			}
		}
	}
	return 0;
}
