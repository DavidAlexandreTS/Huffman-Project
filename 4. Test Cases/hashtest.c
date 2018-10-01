#include "CUnit/Basic.h"
#include "Hash.c"
#include "Heap.c"
#include "huffmantree.c"

//HASH FUNCTIONS
void create_hash_test(){
	int i;
	hash_table * ht = create_hash();
	for (i=0;i<MAX_HASH_SIZE;i++){
		CU_ASSERT_PTR_NULL(ht->table[i]);
	}
}

void put_test(){
	hash_table * ht= create_hash();
	unsigned char byte = '*';
	put(ht,&byte);
	int key = byte%MAX_HASH_SIZE;
	CU_ASSERT_PTR_EQUAL(ht->table[key]->byte, 48);
	CU_ASSERT_PTR_EQUAL(ht->table[key]->frequency, 1);
}
//END OF HASH FUNCTIONS

int main(){
	//initialize test registry
	if(CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	CU_pSuite hash_creation = NULL;
	CU_pSuite element_creation = NULL;
	CU_pSuite put_test = NULL;

	//hash test
	hash_creation = CU_add_suite("Testing hash creation",0,0);
	element_creation = CU_add_suite("Testing hash elements",0,0);

	CU_add_test(hash_creation,"Testing 'create_hash' function",create_hash_test);
	CU_add_test(element_creation,"Testing 'put' function",put_test);


	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_basic_run_tests();
	return CU_get_error();

}
