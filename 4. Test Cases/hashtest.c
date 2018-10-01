#include "CUnit/Basic.h"
#include "Hash.c"
#include "Heap.c"
#include "huffmantree.c"

//HASH FUNCTIONS
//testa se todos os espaços do array foram criados corretamente e apontam pra null
void create_hash_test(){
	int i;
	hash_table * ht = create_hash();
	for (i=0;i<MAX_HASH_SIZE;i++){
		CU_ASSERT_PTR_NULL(ht->table[i]);
	}
}

//testa se um elemento foi criado corretamente
//passa se o simbolo do byte for igual a frequencia for igual a 1
void create_element_test(){
	element * testvar=create_element("*",sizeof(unsigned char));

	//nao sei se to colocando o elemento do jeito certo e ta dando erro na hora de comparar o byte, olha isso aqui
	//o comando funciona assim: CU_ASSERT_PTR_EQUAL(actual, expected)
	CU_ASSERT_PTR_EQUAL(testvar->byte, 52);
	CU_ASSERT_PTR_EQUAL(testvar->frequency, 1);
}

//testa se um elemento foi colocado na heap corretamente
void put_test(){
	hash_table * ht= create_hash();
	
	put(ht,"*");
//	nao sei como da o put tbm, ajeita pra mim na moral
	//key = (*(unsigned char *)data%MAX_HASH_SIZE);
//	key= numero que seria o caractere escolhido
// ta dando um errinho na hora de compilar pq nao ta achando a posição certa, é só ajeitar e tudo ok	
/* DESCOMENTAR AS 2 LINHAS ABAIXO DEPOIS DE RESOLVER O BUG DO PUT
	CU_ASSERT_PTR_EQUAL(ht->table[key]->byte, 52);
	CU_ASSERT_PTR_EQUAL(ht->table[key]->frequency, 1);*/
}
//END OF HASH FUNCTIONS




int main(){
	//initialize test registry
	if(CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	CU_pSuite pSuite = NULL;

	//hash test
	pSuite = CU_add_suite("hash_test_suite",0,0);

	if (NULL==pSuite){
		CU_cleanup_registry();
		return CU_get_error();	
	}

	if (NULL == CU_add_test(pSuite,"create_hash test",create_hash_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}


	if (NULL == CU_add_test(pSuite,"create_element test",create_element_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}
	
	if (NULL == CU_add_test(pSuite,"put test",put_test)){
		CU_cleanup_registry();
		return CU_get_error();	
	}
	//end of hash test
	
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
