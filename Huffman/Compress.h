#ifndef COMPRESS_H
#define COMPRESS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Heap.h"
#include "Hash.h"
#include "huffmantree.h"
#include "Compress_Hash.h"
unsigned char* Create_header(int trash_size,int tree_size);
int is_leaf(huffmanTree * bt);
void set (huffmanTree * bt,Comp_HT* ht,int height,unsigned char byte);
#endif
