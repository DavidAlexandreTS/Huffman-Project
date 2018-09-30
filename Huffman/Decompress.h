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

unsigned char set_bit(unsigned char c, int i)
{
	unsigned char mask = 1 << i;
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
    unsigned int first_byte = fgetc(file_a) << 8;
    unsigned int second_byte = fgetc(file_a);
    first_byte |= second_byte;
    int tree_size = 0;
    for (int i = 0; i <13; i ++)
    {
        if (is_bit_i_set(first_byte, i))
        {
            tree_size = set_bit(tree_size, i);
        }
    }
    return tree_size;
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

void Decompress(FILE *file_a,FILE * file_e ,huffmanTree *actual, huffmanTree *root, unsigned char byte, int byte_actual,int trash,long long unsigned size)
{
    if(size>1){
    if(isLeaf(actual)) {
        printf("%c",*(unsigned char *)getBYTE(actual));
        fputc(*(unsigned char*)actual->byte,file_e);
        if(byte_actual>0)
        Decompress(file_a,file_e,root,root,byte,byte_actual,trash,size);
        else if (is_bit_i_set(byte,byte_actual))Decompress(file_a,file_e,root->right,root,fgetc(file_a),7,trash,size-1);
        else Decompress(file_a,file_e,root->left,root,fgetc(file_a),7,trash,size-1);
    }
    else {
       // bin(byte);
       // printf(" %d\n",byte_actual);
          if(byte_actual==0){
            if(is_bit_i_set(byte,byte_actual)) Decompress(file_a,file_e,actual->right,root,fgetc(file_a),7,trash,size-1);
            else Decompress(file_a,file_e,actual->left,root,fgetc(file_a),7,trash,size-1);
        }
        else if(is_bit_i_set(byte,byte_actual)) 
                Decompress(file_a,file_e,actual->right,root,byte,byte_actual-1,trash,size);
            else 
                Decompress(file_a,file_e,actual->left,root,byte,byte_actual-1,trash,size);
        }
    }
    else {
        if(byte_actual>=trash) {
        if(isLeaf(actual)) {
            fputc(*(unsigned char *)getBYTE(actual),file_e);
            Decompress(file_a,file_e,root,root,byte,byte_actual,trash,size);
            }
            else if(is_bit_i_set(byte,byte_actual)) Decompress(file_a,file_e,actual->right,root,byte,byte_actual-1,trash,size);
            else Decompress(file_a,file_e,actual->left,root,byte,byte_actual-1,trash,size);
        }
        if(byte_actual==trash-1&&isLeaf(actual))fputc(*(unsigned char *)getBYTE(actual),file_e);
    }
}
long long unsigned Get_FILE_size(FILE * A)
{
    long long unsigned i;
    for(i=0;!feof(A);i++) fgetc(A);
        return i-1;
}
void Decompress_File(char * nome)
{
 
    char exit[1000];
    int i,tam = strlen(nome)-6;
    for(i=0;i<=tam;i++) exit[i] = nome[i];
        exit[i] = '\0';
    FILE *fila_a = fopen(nome,"rb"),*file_e = fopen(exit,"wb");
    int trash_size = Trash_Size(fila_a);
    int tree_size = Tree_Size(fila_a);
    huffmanTree *huff_tree = Extract(fila_a);
    long long unsigned size= Get_FILE_size(fila_a);
    unsigned char byte;
    rewind(fila_a);
    tree_size = Tree_Size(fila_a);
    for(i=0;i<tree_size;i++) {
    byte = fgetc(fila_a);
    }
      puts("trash and tree size obtained");
   Decompress(fila_a,file_e,huff_tree,huff_tree,fgetc(fila_a),7,trash_size,size);

    return;    
}

#endif