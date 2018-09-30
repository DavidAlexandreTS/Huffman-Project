#include "huffmantree.h"

/*DefiniÃ§Ã£o do conteÃºdo da Ã¡rvore huffman*/


/*FunÃ§Ã£o que cria uma "folha"(nÃ³ de uma Ã¡rvore sem filhos)
 *Recebe: byte(void) e frequÃªncia do byte (long long int)
 *Retorna: NÃ³ (huffmanTree)
 */
 huffmanTree* createNODE(void *byte, long long int frequency){
	huffmanTree *aux = (huffmanTree*) malloc(sizeof(huffmanTree));
	    aux->byte = malloc(sizeof(unsigned char));
    *(unsigned char * )aux->byte = *(unsigned char *) byte;
	aux->frequency = frequency;
	aux->left=NULL;
	aux->right=NULL;
	return(aux);
}
void Tree_size(huffmanTree * ht,int * size)
{
	if(ht!=NULL)
	{
		(*size)++;
		Tree_size(ht->left,size);
		Tree_size(ht->right,size);
	}
}
/*FunÃ§Ã£o que cria uma Ã¡rvore com filhos
 *Recebe: byte(void), frequÃªncia do byte (long long int) e
 *nÃ³s de esquerda e direita(huffmanTree)
 *Retorna: Ã�rvore (huffmanTree)
 */
huffmanTree* createTREE(void * byte, long long int frequency, huffmanTree *left, huffmanTree *right){
	huffmanTree *aux = (huffmanTree*) malloc(sizeof(huffmanTree));
	aux->byte = malloc(sizeof(unsigned char));
	*(unsigned char*)aux->byte = *(unsigned char*)byte;
	aux->frequency = frequency;
	aux->left=left;
	aux->right=right;
	return(aux);
}

/*Checa se um nÃ³ de uma Ã¡rvore estÃ¡ vazio
 *Recebe: Um nÃ³ da Ã¡rvore (huffmanTree)
 *Retorna: 1 se estiver vazio, 0 se nÃ£o estiver
 */
bool isHTempty(huffmanTree *ht){
	return (ht==NULL);
}

/*Checa se um nÃ³ de uma Ã¡rvore Ã© uma folha
 *Recebe: Um nÃ³ da Ã¡rvore (huffmanTree)
 *Retorna: 1 se for folha, 0 se nÃ£o for
 */
bool isLeaf(huffmanTree *ht){
	return (ht->left==NULL && ht->right==NULL);
}

/*Desloca-se para o filho a esquerda do nÃ³ recebido
 *Recebe: Um nÃ³ da Ã¡rvore (huffmanTree)
 *Retorna: nÃ³ da esquerda(huffmanTree), caso seja diferente de NULL
 */
huffmanTree* go_left(huffmanTree *ht){
	if (isHTempty(ht)) return NULL;
	
	return ht->left;
}

/*Desloca-se para o filho a direita do nÃ³ recebido
 *Recebe: Um nÃ³ da Ã¡rvore (huffmanTree)
 *Retorna: nÃ³ da direita (huffmanTree), caso seja diferente de NULL
 */
huffmanTree* go_right(huffmanTree *ht){
	if (isHTempty(ht)) return NULL;
	
	return ht->right;
}

/*FunÃ§Ã£o que retorna o byte do nÃ³ recebido
 *Recebe: Um nÃ³ da Ã¡rvore (huffmanTree)
 *Retorna: Byte(void) do nÃ³, caso o nÃ³ seja diferente de NULL ou
 * 0 caso seja NULL
 */
void * getBYTE(huffmanTree *ht){
	if (isHTempty(ht)) return NULL;
	return ht->byte;
}

/*FunÃ§Ã£o que retorna a frequÃªncia do nÃ³ recebido
 *Recebe: Um nÃ³ da Ã¡rvore (huffmanTree)
 *Retorna: FrequÃªncia(long long int) do nÃ³, caso o nÃ³ seja diferente de NULL,
 *menor inteiro caso seja NULL.
 */
long long int getFREQ(huffmanTree *ht){
	if (isHTempty(ht)) return LLONG_MIN;
	return ht->frequency;
}

/* cria a Ã¡rvore de fato, se baseando na heap que o David implementou
   como funciona: retira-se os 2 menores nÃ³s da nossa min-heap, criando
   um novo nÃ³ cujo caractere Ã© o '*' (ou '\' caso necessÃ¡rio) e seus
   filhos sÃ£o os 2 menores nÃ³s retirados a esquerda e direita, respect-
   tivamente.ApÃ³s a criaÃ§Ã£o, o nÃ³ Ã© recolocado na heap(em ordem). O processo Ã© repetido
   atÃ© que a heap esteja com apenas 1 elemento (que serÃ¡ a nossa Ã¡rvore).
*/

/*FunÃ§Ã£o que printa um nÃ³ da Ã¡rvore e sua frequÃªncia
 *Recebe: Um nÃ³ da Ã¡rvore (huffmanTree).
 *Retorna: Print do byte e da frequÃªncia do nÃ³ recebido.
 */
void printNODE(huffmanTree *ht){
	if (isHTempty(ht)) return;
	
	printf("letter: %c | freq.: %lld\n", *(char*)ht->byte, ht->frequency);
}

/*FunÃ§Ã£o que printa os nÃ³s da Ã¡rvore em prÃ©-ordem
 *Recebe: A raiz da Ã¡rvore (huffmanTree).
 *Retorna: Print da arvore em prÃ©-ordem.
 */
void printHTinFile (huffmanTree *ht,FILE *new){
	if (!isHTempty(ht)){
		fprintf(new,"%c",*(unsigned char *)ht->byte);
		printHTinFile(ht->left, new);
		printHTinFile(ht->right, new);
	}
}

/*FunÃ§Ã£o que libera os nÃ³s da Ã¡rvore de forma recursiva
 *Recebe: A raiz da Ã¡rvore (huffmanTree).
 *Retorna: nada, apenas libera o espaÃ§o alocado para os nÃ³s de toda a Ã¡rvore.
 */
void destroyHTREE (huffmanTree *ht){
	if(!isHTempty(ht)){
		destroyHTREE(ht->left);
		destroyHTREE(ht->right);
		free(ht);
	}
}
int max (int a,int b)
{
  return ( a > b ) ? a:b;
}
int height(huffmanTree * bt)
{
  if(bt==NULL)
  return -1;
  else
  {
    return 1+ max(height(bt->left),height(bt->right));
  }
}
