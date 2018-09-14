#include "Compress.h"
unsigned char* Create_header(int trash_size,int tree_size)
{
	unsigned char *bytes = (unsigned char*) malloc(sizeof(3*sizeof(unsigned char)));
	bytes[0] =  trash_size<<5 | tree_size>>8;
	bytes[1] =  tree_size;
	return (bytes);
}
