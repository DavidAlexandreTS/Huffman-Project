#ifndef COMPRESS_H
#define COMPRESS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Heap.h"
#include "Hash.h"
#include "huffmantree.h"
#include "Compress_Hash.h"
int is_leaf(huffmanTree * bt);
void set (huffmanTree * bt,Comp_HT* ht,int height,unsigned char byte);
#endif
