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
	
	unsigned char byte='*'
	long long int freq=1;
	Heap * hp = create_heap();
	huffmanTree *ht= createNODE(&byte,freq);
	enqueue(hp,ht);

	CU_ASSERT_FALSE(is_empty(hp));
}

void get_left_test(){
	int i=1;
	Heap * hp = create_heap();
	while(i<=256){
		CU_ASSERT_EQUAL(get_left_index(hp,i), 2*i);
		i=2*i;
	}
}

void get_right_test(){
	int i=1;
	Heap * hp = create_heap();
	while(i<=256){
		CU_ASSERT_EQUAL(get_right_index(hp,i), 2*i+1);
		i=2*i+1;
	}
}

void get_parent_test(){
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
	unsigned char byteA='a',byteB='b';
	long long int freqA='1',freqB='2';
	
	huffmanTree * noA=createNODE(&byteA,freqA);
	huffmanTree * noB=createNODE(&byteB,freqB);
	
	//BEFORE SWAP
	//node A
	CU_ASSERT_PTR_EQUAL(getBYTE(noA), byteA);
	CU_ASSERT_PTR_EQUAL(getFREQ(noA), freqA);
	//node B
	CU_ASSERT_PTR_EQUAL(getBYTE(noB), byteB);
	CU_ASSERT_PTR_EQUAL(getFREQ(noB), freqB);
	
	//swapping
	swap(noA,noB);

	//node A with values of node B
	CU_ASSERT_PTR_EQUAL(getBYTE(noA), byteB);
	CU_ASSERT_PTR_EQUAL(getFREQ(noA), freqB);
	//node B with values of node A
	CU_ASSERT_PTR_EQUAL(getBYTE(noB), byteA);
	CU_ASSERT_PTR_EQUAL(getFREQ(noB), freqA);
}

void enqueue_test(){
	//enqueue and check top
	unsigned char byte='*'
	long long int freq=1;
	Heap * hp = create_heap();
	huffmanTree *ht= createNODE(&byte,freq);
	enqueue(hp,ht);

	//CU_ASSERT_PTR_EQUAL(byte on top,byte);
}

void dequeue_test(){
	//da dequeue e checa o topo
	Heap * hp = create_heap();
	huffmanTree *ht= create_huffmantree();

	//enqueue(hp,ht);
	//CU_ASSERT_PTR_EQUAL(byte on top, byte );

}




//END OF HEAP FUNCTIONS

int main(){
	//initialize test registry
	if(CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	CU_pSuite heap_creation_TEST = NULL;
	CU_pSuite heap_features_TEST = NULL;

	
	//heap test
	heap_creation_TEST = CU_add_suite("Testing heap creation",0,0);
	heap_features_TEST = CU_add_suite("Testing heap features",0,0);
	
	CU_add_test(pSuite,"create_hash test",create_heap_test);	
	CU_add_test(pSuite,"is_empty test",is_empty_test);	
	CU_add_test(pSuite,"get_left_index test",get_left_test);	
	CU_add_test(pSuite,"get_right_index test",get_right_test);	
	CU_add_test(pSuite,"get_parent_index test",get_parent_test);	
	
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
	CU_add_test(pSuite,"enqueue test",enqueue_test);	
	CU_add_test(pSuite,"dequeue test",dequeue_test);	
	//end of heap test

	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_basic_run_tests();
	return CU_get_error();

}