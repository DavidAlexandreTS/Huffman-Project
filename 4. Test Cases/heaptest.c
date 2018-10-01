#include "CUnit/Basic.h"
#include "Hash.c"
#include "Heap.c"
#include "huffmantree.c"

//HEAP FUNCTIONS
void create_heap_test(){
	int i;
	 Heap * hp = create_heap();
	for (i=0;i<MAX_HEAP_SIZE;i++){
		CU_ASSERT_PTR_NULL(hp->data[i]);
	}	
	CU_ASSERT_PTR_EQUAL(hp->size, 0);
}

void is_empty_test(){
	Heap * hp = create_heap();
	CU_ASSERT_TRUE(is_empty(hp));
	//adiciona um item na heap agora,n sei como faz

	CU_ASSERT_FALSE(is_empty(hp));
}

void get_left_test(){
	//testa até onde ele pega um filho a esquerda
	int i=1;
	Heap * hp = create_heap();
	while(i<=256){
		CU_ASSERT_EQUAL(get_left_index(hp,i), 2*i);
		i=2*i;
	}
}

void get_right_test(){
	//testa até onde ele pega um filho a direita
	int i=1;
	Heap * hp = create_heap();
	while(i<=256){
		CU_ASSERT_EQUAL(get_right_index(hp,i), 2*i+1);
		i=2*i+1;
	}
}

void get_parent_test(){
	//testa até onde ele pega um pai
	int i=256;
	Heap * hp = create_heap();
	while(i!=1){
		CU_ASSERT_EQUAL(get_parent_index(hp,i), i/2);
		i=i/2;
	}
	i=255;
	while(i!=1){
		CU_ASSERT_EQUAL(get_parent_index(hp,i), i/2);
		i=i/2;
	}
}
/*
void item_of_test(){
	Heap * hp = create_heap();
	//dá enqueue em algo aqui, de preferencia: 
	//enqueue(hp,ht)		
	int i;
	i=52; //codigo na tabela ascii pro asterisco
	CU_ASSERT_PTR_EQUAL(hp->data[i]->byte, "*");
}*/

void swap_test(){
	//cria uma arvore com raiz e 2 nós e troca os nós
	//acho que isso deveria estar no teste das arvores mas ok

	unsigned char byteA='a',byteB='b';
	long long int freqA='1',freqB='2';
	
	huffmanTree * noA=createNODE(&byteA,freqA);
	huffmanTree * noB=createNODE(&byteB,freqB);
	
	//COMPARANDO ANTES DA TROCA	
	//nó A
	CU_ASSERT_PTR_EQUAL(noA->byte, byteA);
	CU_ASSERT_PTR_EQUAL(noA->frequency, freqA);
	//nó B
	CU_ASSERT_PTR_EQUAL(noB->byte, byteB);
	CU_ASSERT_PTR_EQUAL(noB->frequency, freqB);
	
	//faz o swap
	swap(noA,noB);

	//no A que agora deve ter o valor do no B
	CU_ASSERT_PTR_EQUAL(noA->byte, byteB);
	CU_ASSERT_PTR_EQUAL(noA->frequency, freqB);
	//no B que agora deve ter o valor do no A
	CU_ASSERT_PTR_EQUAL(noB->byte, byteA);
	CU_ASSERT_PTR_EQUAL(noB->frequency, freqA);

	//se quiser é só colar o codigo de novo e fazer a troca mais uma vez
}

void enqueue_test(){
	//da enqueue e checa o topo
	Heap * hp = create_heap();
	//huffmanTree *ht= create_huffmantree();

	//enqueue(hp,ht);
// DAR ENQUEUE, POR A HEAP PRA MOSTRAR O TOPO E DESCOMENTAR ESSES ASSERTS COM OS VALORES DO TOPO QUE VCS COLOCAREM
	//CU_ASSERT_PTR_EQUAL(heap retornando o byte no topo, byte esperado no topo);
	//CU_ASSERT_PTR_EQUAL(heap retornando a frequencia do byte no topo , frequencia do byte no topo esperada);
}

//SE QUISEREM ENCHAM A HEAP NO TESTE ACIMA /\ E ESVAZIEM TODA ABAIXO \/USANDO WHILE
void dequeue_test(){
	//da dequeue e checa o topo
	Heap * hp = create_heap();
	//huffmanTree *ht= create_huffmantree();

	//enqueue(hp,ht);
// DAR ENQUEUE, POR A HEAP PRA MOSTRAR O TOPO E DESCOMENTAR ESSES ASSERTS COM OS VALORES DO TOPO QUE VCS COLOCAREM
	//CU_ASSERT_PTR_EQUAL(heap retornando o byte no topo, byte esperado no topo);
	//CU_ASSERT_PTR_EQUAL(heap retornando a frequencia do byte no topo , frequencia do byte no topo esperada);

// AGORA DAR DEQUEUE E COMPARAR O PROCESSO A CADA PASSO, COMO ACIMA
}


void tree_size_test(){
	// adiciona varios numeros numa arvore e testa seu tamanho
// isso devia mesmo estar aqui tbm?

	unsigned char byte ='*';
	long long int freq=1;
	huffmanTree * ht= createNODE(&byte,freq);
	//CU_ASSERT_PTR_EQUAL(Tree_size(ht,0), 0);
// adicionar mais nós e ir checando tamanho a cada passo com o mesmo comando acima
}


/*
void min_heapify(Heap *hipi, int i);
void heapsort(Heap *hipi);
void print_heap(Heap *hipie, int aux);
huffmanTree* createHTfromHEAP(Heap *heap);*/
//END OF HEAP FUNCTIONS

int main(){
	//initialize test registry
	if(CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	CU_pSuite pSuite = NULL;

	
	//heap test
	pSuite = CU_add_suite("heap_test_suite",0,0);
	
	if (NULL == CU_add_test(pSuite,"create_hash test",create_heap_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}

	if (NULL == CU_add_test(pSuite,"is_empty test",is_empty_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}

		if (NULL == CU_add_test(pSuite,"get_left_index test",get_left_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}

	if (NULL == CU_add_test(pSuite,"get_right_index test",get_right_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}

	if (NULL == CU_add_test(pSuite,"get_parent_index test",get_parent_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}
	
/*	
	if (NULL == CU_add_test(pSuite,"item_of test",item_of_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}

	if (NULL == CU_add_test(pSuite,"swap test",swap_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}
*/
	if (NULL == CU_add_test(pSuite,"enqueue test",enqueue_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}

	if (NULL == CU_add_test(pSuite,"dequeue test",dequeue_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}

	if (NULL == CU_add_test(pSuite,"tree size test",tree_size_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}
	//end of heap test

	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_basic_run_tests();
	return CU_get_error();

}