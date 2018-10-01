#include <stdio.h>
#include <stdlib.h>

long long int Comparations = 0, ComparationsAVL = 0;

typedef struct binary_tree
{
    int item;
    int h;
    struct binary_tree* left;
    struct binary_tree* right;
}binary_tree;

binary_tree* create_empty_binary_tree()
{
    return NULL;
}

binary_tree *create_binary_tree(int item, binary_tree* left, binary_tree* right)
{
    binary_tree* new_binary_tree = (binary_tree*) malloc(sizeof(binary_tree));
    new_binary_tree -> item = item;
    new_binary_tree -> left = left;
    new_binary_tree -> right = right;

    return new_binary_tree;
}

int is_empty(binary_tree* bt)
{
    return bt == NULL;
}

int is_balanced(binary_tree* bt)
{
    int bf = h(bt -> left) - h(bt -> right);
    return ((-1 <= bf) && (bf <= 1));
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int h(binary_tree* bt)
{
    if (bt == NULL)
        return -1;
    else
        return 1 + max(h(bt -> left), h(bt -> right));
}

int balance_factor(binary_tree* bt)
{
    if (bt == NULL)
    {
        return 0;
    }else if ((bt -> left != NULL) && (bt -> right != NULL))
    {
        return (bt -> left -> h - bt -> right -> h);
    }else if ((bt -> left != NULL) && (bt -> right == NULL))
    {
        return ( 1 + bt -> left -> h);
    }else
    {
        return (-bt -> right -> h - 1);
    }
}

binary_tree *rotate_left(binary_tree* bt)
{
    binary_tree *subtree_root = NULL;

    if (bt != NULL && bt -> right != NULL)
    {
        subtree_root = bt -> right;
        bt -> right = subtree_root -> left;
        subtree_root -> left = bt;
    }

    subtree_root -> h = h(subtree_root);
    bt -> h = h(bt);

    return subtree_root;
}

binary_tree *rotate_right(binary_tree* bt)
{
    binary_tree *subtree_root = NULL;

    if (bt != NULL && bt -> left != NULL)
    {
        subtree_root = bt -> left;
        bt -> left = subtree_root -> right;
        subtree_root -> right = bt;
    }

    subtree_root -> h = h(subtree_root);
    bt -> h = h(bt);

    return subtree_root;
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

binary_tree *Add_AVL(binary_tree* bt, int item)
{
    if (bt == NULL)
    {
        return create_binary_tree(item, NULL, NULL);
    }else if (bt -> item > item)
    {
        bt -> left = Add_AVL(bt -> left, item);
    }else
    {
        bt -> right = Add_AVL(bt -> right, item);
    }

    bt -> h = h(bt);
    binary_tree* child;

    if (balance_factor(bt) == 2 || balance_factor(bt) == -2)
    {
        if (balance_factor(bt) == 2)
        {
            child = bt -> left;
            if (balance_factor(child) == -1)
            {
                bt -> left = rotate_left(child);
            }
            bt = rotate_right(bt);
        }else if (balance_factor(bt) == -2)
        {
            child = bt -> right;
            if (balance_factor(child) == 1)
            {
                bt -> right = rotate_right(child);
            }
            bt = rotate_left(bt);
        }
    }

    return bt;
}

binary_tree* search(binary_tree *bt, int item)
{
    if ((bt == NULL) || (bt -> item == item))
    {
        if (bt -> item == item)
        {
            Comparations ++;
            return bt;
        }
    } else if (bt -> item > item)
    {
        Comparations ++;
        return search(bt->left, item);
    } else
    {
        Comparations ++;
        return search(bt->right, item);
    }
}

binary_tree* searchavl(binary_tree *bt, int item)
{
    if ((bt == NULL) || (bt -> item == item))
    {
        if (bt -> item == item)
        {
            ComparationsAVL ++;
            return bt;
        }
    } else if (bt -> item > item)
    {
        ComparationsAVL ++;
        return searchavl(bt->left, item);
    } else
    {
        ComparationsAVL ++;
        return searchavl(bt->right, item);
    }
}

void main()
{
    binary_tree* arvore = create_empty_binary_tree();
    binary_tree* avl = create_empty_binary_tree();
    int size;
    long long int i, qtd;
    printf("Enter the quantity of Data(Numbers) you want to insert into the Tree and AVL:\n");
    scanf("%lld", &qtd);
    int Numbers[qtd], StepsTree[qtd], StepsAVL[qtd];
    printf("Mounting the Tree...\n");
    for (i = 0; i <= qtd; i ++)
    {
        arvore = add(arvore, i);
    }
    printf("Tree Mounted with Sucess!\n");
    i = 0;
    printf("Mounting the AVL...\n");
    while (i <= qtd)
    {
        avl = Add_AVL(avl, i);
        i ++;
    }
    printf("AVL is Mounted\n");
    long long int var, result, result2;
    FILE* arch;
    arch = fopen("Graficos.txt", "w");
    int tam;
    printf("How many random numbers do you want to generate?\n");
    scanf("%d", &tam);
    srand (time(NULL));
    for (i = 0; i < tam; i ++)
    {
        var = rand()%qtd;
        Numbers[i] = var;
        result = search(arvore, var);
        StepsTree[i] = Comparations;
        result2 = searchavl(avl, var);
        StepsAVL[i] = ComparationsAVL;
        fprintf(arch, "%lld\n", Numbers[i]);
        fprintf(arch, "%lld\n", StepsTree[i]);
        fprintf(arch, "%lld\n", StepsAVL[i]);
        Comparations = ComparationsAVL = 0;
    }
    fclose(arch);
}