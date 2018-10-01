#include "CUnit/Basic.h"
#include "Hash.c"
#include "Heap.c"
#include "huffmantree.c"

//START OF TREE FUNCTIONS

void create_node_test(){
	unsigned char byte='*';
	long long int frequency = 1;
	huffmanTree * nodetest = createNODE(&byte,frequency);
	
	CU_ASSERT_PTR_EQUAL(nodetest->byte, byte);
	CU_ASSERT_PTR_EQUAL(nodetest->frequency, frequency);
	CU_ASSERT_PTR_NULL(nodetest->left);
	CU_ASSERT_PTR_NULL(nodetest->right);
}

void create_tree_test(){
	unsigned char byte='*';
	long long int frequency = 1;
	huffmanTree * nodeA=NULL;
	huffmanTree * nodeB=NULL;
	huffmanTree * treetest = createTREE(&byte,frequency,nodeA,nodeB);
	//caso com a arvore vazia
	CU_ASSERT_PTR_EQUAL(treetest->byte, byte);
	CU_ASSERT_PTR_EQUAL(treetest->frequency, frequency);
	CU_ASSERT_PTR_NULL(treetest->left);
	CU_ASSERT_PTR_NULL(treetest->right);
	destroyHTREE(treetest);
	//caso com a arvore "cheia"
	unsigned char byteA='a',byteB='b';
	long long int freqA=2,freqB=3;
	nodeA=createNODE(&byteA,freqA);
	nodeB=createNODE(&byteB,freqB);
	treetest = createTREE(&byte,frequency,nodeA,nodeB);
	
	//root
	CU_ASSERT_PTR_EQUAL(treetest->byte, byte);
	CU_ASSERT_PTR_EQUAL(treetest->frequency, frequency);
	//node da esquerda
	CU_ASSERT_PTR_EQUAL(treetest->left->byte, byteA);
	CU_ASSERT_PTR_EQUAL(treetest->left->frequency, freqA);
	//node da direita
	CU_ASSERT_PTR_EQUAL(treetest->right->byte, byteB);
	CU_ASSERT_PTR_EQUAL(treetest->right->frequency, freqB);
	
	destroyHTREE(treetest);
}

void isHTempty_test(){
	huffmanTree * treetest = NULL;
	//caso com a arvore realmente vazia
	CU_ASSERT_TRUE(isHTempty(treetest));
	
	//enchendo a arvore e testando
	unsigned char byte='*';
	long long int frequency = 1;
	createNODE(&byte,frequency);
	CU_ASSERT_FALSE(isHTempty(treetest));
	destroyHTREE(treetest);
}

void isLeaf_test(){
	
	unsigned char byte='*';
	long long int frequency = 1;
	huffmanTree * nodeA=NULL;
	huffmanTree * nodeB=NULL;
	huffmanTree * treetest = createTREE(&byte,frequency,nodeA,nodeB);
	//teste se um nó sem esquerda e direita é folha
	CU_ASSERT_TRUE(isLeaf(treetest));
	destroyHTREE(treetest);
	//caso com a arvore "cheia"
	unsigned char byteA='a',byteB='b';
	long long int freqA=2,freqB=3;
	nodeA=createNODE(&byteA,freqA);
	nodeB=createNODE(&byteB,freqB);
	treetest = createTREE(&byte,frequency,nodeA,nodeB);
	
	//root
	CU_ASSERT_FALSE(isHTempty(treetest));
	//node da esquerda
	CU_ASSERT_TRUE(isLeaf(treetest->left));
	//node da direita
	CU_ASSERT_TRUE(isLeaf(treetest->right));

	destroyHTREE(treetest);
}
void go_left_test(){
	
	huffmanTree * treetest = NULL;
	//teste com arvore vazia
	CU_ASSERT_PTR_NULL(go_left(treetest));

	//caso com a arvore "cheia"
	huffmanTree * nodeA=NULL;
	huffmanTree * nodeB=NULL;

	unsigned char byte='*';
	long long int frequency = 1;
	unsigned char byteA='a',byteB='b';
	long long int freqA=2,freqB=3;
	nodeA=createNODE(&byteA,freqA);
	nodeB=createNODE(&byteB,freqB);
	treetest = createTREE(&byte,frequency,nodeA,nodeB);
	
	//dá o get left e compara os valores, nao sei se fiz certo
	huffmanTree * test = go_left(treetest);
	CU_ASSERT_PTR_EQUAL(test->byte, byteA);
	CU_ASSERT_PTR_EQUAL(test->frequency, freqA);

	destroyHTREE(treetest);
}
void go_right_test(){
//mesma coisa do go left mas indo pra direita
	huffmanTree * treetest = NULL;
	//teste com arvore vazia
	CU_ASSERT_PTR_NULL(go_left(treetest));

	//caso com a arvore "cheia"
	huffmanTree * nodeA=NULL;
	huffmanTree * nodeB=NULL;

	unsigned char byte='*';
	long long int frequency = 1;
	unsigned char byteA='a',byteB='b';
	long long int freqA=2,freqB=3;
	nodeA=createNODE(&byteA,freqA);
	nodeB=createNODE(&byteB,freqB);
	treetest = createTREE(&byte,frequency,nodeA,nodeB);
	
	//dá o get left e compara os valores, nao sei se fiz certo
	huffmanTree * test = go_right(treetest);
	CU_ASSERT_PTR_EQUAL(test->byte, byteB);
	CU_ASSERT_PTR_EQUAL(test->frequency, freqB);

	destroyHTREE(treetest);
}
void get_byte_test(){
	unsigned char byte='*';
	long long int frequency = 1;
	huffmanTree * nodetest = createNODE(&byte,frequency);
	
	CU_ASSERT_PTR_EQUAL(nodetest->byte, byte);
	destroyHTREE(nodetest);
}
void get_freq_test(){
	unsigned char byte='*';
	long long int frequency = 1;
	huffmanTree * nodetest = createNODE(&byte,frequency);
	CU_ASSERT_PTR_EQUAL(nodetest->frequency, frequency);
	destroyHTREE(nodetest);
}

void max_test(){
	int a,b;
	a=35;
	b=29;
	CU_ASSERT_EQUAL(max(a,b),a);
	//fazer caso com a<bS
}
void height_test(){
		// adiciona varios numeros numa arvore e testa sua altura

	unsigned char byte ='*';
	long long int freq=1;
	huffmanTree * ht= NULL;
// a arvore nao ta sendo construida direito por causa do erro acima e essa função ta dando erro
//resolver a arvore resolve o problema
//caso com arvore vazia
	CU_ASSERT_PTR_EQUAL(height(ht), -1);
//caso só com a raiz
	ht= createNODE(&byte,freq);
	CU_ASSERT_PTR_EQUAL(height(ht), 0);
// adicionar mais nós e ir checando tamanho a cada passo com o mesmo comando acima

}

void printNODE_test(){
	unsigned char byte ='*';
	long long int freq=1;
	huffmanTree * ht= createNODE(&byte,freq);
	//CU_ASSERT_STRING_EQUAL(printNODE(ht), "letter: * | freq.: 1\n");
}

/*
void printHTinFile_test(){
	//preciso de um caso pra construir a arvore

	CU_ASSERT_STRING_EQUAL(printHTinFile(ht), "string da arvore aqui");
}*/

/*

void printHTinFile (huffmanTree * ht,FILE *new);
void destroyHTREE(huffmanTree *ht);
*/
//END OF TREE FUNCTIONS

int main(){
	//initialize test registry
	if(CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	CU_pSuite pSuite = NULL;

	//huffman tree test
	pSuite = CU_add_suite("huffman_tree_test_suite",0,0);
	
	if (NULL == CU_add_test(pSuite,"create_node test",create_node_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}
	if (NULL == CU_add_test(pSuite,"create_tree test",create_tree_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}
	if (NULL == CU_add_test(pSuite,"isHTempty test",isHTempty_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}
	if (NULL == CU_add_test(pSuite,"isLeaf test",isLeaf_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}
	if (NULL == CU_add_test(pSuite,"go_left test",go_left_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}
	if (NULL == CU_add_test(pSuite,"go_right test",go_right_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}
	
	if (NULL == CU_add_test(pSuite,"getBYTE test",get_byte_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}

	if (NULL == CU_add_test(pSuite,"getFREQ test",get_freq_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}
/*
	if (NULL == CU_add_test(pSuite,"printNODE test",printNODE_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}
	if (NULL == CU_add_test(pSuite,"printHTinfile test",printHTinFile_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}
*/
	if (NULL == CU_add_test(pSuite,"max test",max_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}

	if (NULL == CU_add_test(pSuite,"height test",height_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}

	//end of huffman tree test

	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_basic_run_tests();
	return CU_get_error();

}