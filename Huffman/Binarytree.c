/*#include <stdio.h>
#include <stdlib.h>

typedef struct binary_tree
{
	int item;
	struct binary_tree *left;
	struct binary_tree *right;
} binary_tree;

binary_tree* create_empty_binary_tree()
{
	return NULL;
}

is_empty(binary_tree *bt)
{
	return bt == NULL;
}

binary_tree *create_binary_tree(int item, binary_tree* left, binary_tree *right)
{
	binary_tree* new_binary_tree = (binary_tree*) malloc(sizeof(binary_tree));
	new_binary_tree -> item = item;
	new_binary_tree -> left = left;
	new_binary_tree -> right = right;

	return new_binary_tree;
}

binary_tree* add(binary_tree *bt, int item)
{
	if (bt == NULL)
	{
		bt = create_binary_tree(item, NULL, NULL);
	} else if (bt -> item > item)
	{
		bt -> left = add(bt -> left, item);
	} else
	{
		bt -> right = add(bt -> right, item);
	}

	return bt;
}

binary_tree* search(binary_tree *bt, int item)
{
	if ((bt == NULL) || (bt -> item == item))
	{
		return bt;
	} else if (bt -> item > item)
	{
		return search(bt->left, item);
	} else
	{
		return search(bt->right, item);
	}
}

void print_in_order(binary_tree *bt)
{
	if (!is_empty(bt))
	{
		print_in_order(bt -> left);
		printf("%d ", bt -> item);
		print_in_order(bt -> right);
	}
}

void print_pre_order(binary_tree *bt)
{
	if (!is_empty(bt))
	{
		printf("%d ", bt -> item);
		print_pre_order(bt -> left);
		print_pre_order(bt -> right);
	}
}

void print_post_order(binary_tree *bt)
{
	if (!is_empty(bt))
	{
		print_post_order(bt -> left);
		print_post_order(bt -> right);
		printf("%d ", bt -> item);
	}
}

void main()
{
	binary_tree* arvore = create_empty_binary_tree();
	arvore = add(arvore, 40);
	arvore = add(arvore, 20);
	arvore = add(arvore, 10);
	arvore = add(arvore, 50);
	arvore = add(arvore, 100);
	arvore = add(arvore, 30);
	arvore = add(arvore, 9);
	arvore = add(arvore, 15);
	arvore = add(arvore, 1);
	arvore = add(arvore, 60);
	printf("Printando em Pre-Ordem:\n");
	print_pre_order(arvore);
	printf("\n");
	printf("Printando em Ordem:\n");
	print_in_order(arvore);
	printf("\n");
	printf("Printando em Pos-Ordem:\n");
	print_post_order(arvore);
	printf("\n");
}*/
