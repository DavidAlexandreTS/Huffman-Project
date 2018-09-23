#include "Compress.h"
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
