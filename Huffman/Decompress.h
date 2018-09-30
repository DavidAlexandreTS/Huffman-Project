#ifndef DECOMPRESS_AHRT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffmantree.h"
#include "Compress.h"
#define DECOMPRESS_AHRT

int is_bit_i_set(unsigned char c, int i)
{
	unsigned char mask = 1 << i;
	return mask & c;
}

unsigned short set_bit(unsigned short c, int i)
{
	unsigned short mask = 1 << i;
	return c | mask;
}

int Trash_Size(FILE *file_a)
{
    rewind(file_a);
    int trash_size = fgetc(file_a) >> 5;
    return trash_size;
}

int Tree_Size(FILE *file_a)
{
    rewind(file_a);
    unsigned short first_byte = fgetc(file_a) << 11;
    first_byte = first_byte>>3;
    unsigned short second_byte = fgetc(file_a);
    first_byte |= second_byte;
    return first_byte;
}
void PT_AR(huffmanTree * ht )
{
    printf("(");
    if(ht!=NULL)
    {
        printf("%c",*(unsigned char*)ht->byte );
        PT_AR(ht->left);
        PT_AR(ht->right);
    }
    printf(")");
}
huffmanTree *Huffman_Tree(FILE *file_a, unsigned char key)
{
    huffmanTree *new_tree_node = createNODE(&key,0);
    if (key == '\\')
    {
        *(unsigned char*)new_tree_node -> byte = fgetc(file_a);
    }
    if (key == '*')
    {
        new_tree_node -> left = Huffman_Tree(file_a, fgetc(file_a));
        new_tree_node -> right = Huffman_Tree(file_a, fgetc(file_a));
    }
    return new_tree_node;
}

huffmanTree *Extract(FILE *fila_a)
{           
    huffmanTree *huff_tree = NULL;
    huff_tree = Huffman_Tree(fila_a, fgetc(fila_a));

    return huff_tree;
}
long long unsigned Get_FILE_size(FILE * file)
{
    long long unsigned i;
    for(i=0;!feof(file);i++) fgetc(file);
        return i-1;
}
void Decompress(FILE * enter,FILE * exit,huffmanTree *Tree,int trash,long long unsigned size)
{
    unsigned char byte;
    int actual;
    huffmanTree * H_A = Tree;
    long long unsigned i=0;
    while(i<size)
    {
        byte = fgetc(enter);
        actual=7;
        if(i<size-1)
        {
            while(actual>=0)
            {
                if(isLeaf(H_A)) {
                    fputc(*(unsigned char*)getBYTE(H_A),exit);
                    H_A = Tree;
                }
                if(is_bit_i_set(byte,actual)) H_A = go_right(H_A);
                else H_A = go_left(H_A);
                actual--;
            }
        }
        else
        {
            printf("%x\n",byte);
            bin(byte);
            puts("");
            while(actual>=trash)
            {
                    if(isLeaf(H_A)) {
                    fputc(*(unsigned char*)getBYTE(H_A),exit);
                    H_A = Tree;
                }
                if(is_bit_i_set(byte,actual)) H_A = go_right(H_A);
                else H_A = go_left(H_A);
                actual--;
            }
            if(isLeaf(H_A)) fputc(*(unsigned char *)getBYTE(H_A),exit);
        }
        i++;
    }
    printf("%llu\n",i);
}
void Decompress_File(char * nome)
{
 
    FILE *fila_a = fopen(nome,"rb");
    while(fila_a==NULL){
        puts("Invalid File name\nType other");
        gets(nome);
        fila_a = fopen(nome,"rb");
    }
    char exit[1000];
    long long unsigned i,tam = strlen(nome)-6;
    for(i=0;i<=tam;i++) exit[i] = nome[i];
        exit[i] = '\0';
    FILE *file_e = fopen(exit,"wb");
    if(fila_a!=NULL){
    int trash_size = Trash_Size(fila_a);
    int tree_size = Tree_Size(fila_a);
    huffmanTree *huff_tree = Extract(fila_a);
    puts("");
    long long unsigned size= Get_FILE_size(fila_a);
    tree_size = Tree_Size(fila_a);
    for(i=0;i<tree_size;i++) fgetc(fila_a);
    Decompress(fila_a,file_e,huff_tree,trash_size,size);
    }
    return;    
}

#endif