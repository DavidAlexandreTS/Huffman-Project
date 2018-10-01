#include "CUnit/Basic.h"
#include "Hash.c"
#include "Heap.c"
#include "huffmantree.c"

//START OF TREE FUNCTIONS

void create_node_test(){
	unsigned char byte='*';
	long long int frequency = 1;
	huffmanTree * nodetest = createNODE(&byte,frequency);
	
	CU_ASSERT_PTR_EQUAL(getBYTE(nodetest), byte);
	CU_ASSERT_PTR_EQUAL(getFREQ(nodetest), frequency);
	CU_ASSERT_PTR_NULL(go_left(nodetest));
	CU_ASSERT_PTR_NULL(go_right(nodetest))
	destroyHTREE(nodetest);
}

void create_tree_test(){
	unsigned char byte='*';
	long long int frequency = 1;
	huffmanTree * nodeA=NULL;
	huffmanTree * nodeB=NULL;
	huffmanTree * treetest = createTREE(&byte,frequency,nodeA,nodeB);
	
	//empty tree
	CU_ASSERT_PTR_EQUAL(getBYTE(nodetest), byte);
	CU_ASSERT_PTR_EQUAL(getFREQ(nodetest), frequency);
	CU_ASSERT_PTR_NULL(go_left(nodetest));
	CU_ASSERT_PTR_NULL(go_right(nodetest));
	
	//"full" tree
	unsigned char byteA='a',byteB='b';
	long long int freqA=2,freqB=3;
	nodeA=createNODE(&byteA,freqA);
	nodeB=createNODE(&byteB,freqB);
	treetest = createTREE(&byte,frequency,nodeA,nodeB);
	
	//root
	CU_ASSERT_PTR_EQUAL(getBYTE(treetest), byte);
	CU_ASSERT_PTR_EQUAL(getFREQ(treetest), frequency);
	
	//left node
	CU_ASSERT_PTR_EQUAL(getBYTE(go_left(treetest)), byteA);
	CU_ASSERT_PTR_EQUAL(getFREQ(go_left(treetest)), freqA);
	
	//right node
	CU_ASSERT_PTR_EQUAL(getBYTE(go_right(treetest)), byteB);
	CU_ASSERT_PTR_EQUAL(getFREQ(go_right(treetest)), freqB);
	
	destroyHTREE(treetest);
}

void isHTempty_test(){
	huffmanTree * treetest = NULL;
	
	//really empty tree
	CU_ASSERT_TRUE(isHTempty(treetest));
	
	//not empty tree
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
	
	//root only
	CU_ASSERT_TRUE(isLeaf(treetest));
	
	//root with 2 leafs
	unsigned char byteA='a',byteB='b';
	long long int freqA=2,freqB=3;
	nodeA=createNODE(&byteA,freqA);
	nodeB=createNODE(&byteB,freqB);
	treetest = createTREE(&byte,frequency,nodeA,nodeB);
	
	//root
	CU_ASSERT_FALSE(isHTempty(treetest));
	
	//left node
	CU_ASSERT_TRUE(isLeaf(go_left(treetest)));
	
	//right node
	CU_ASSERT_TRUE(isLeaf(go_right(treetest)));

	destroyHTREE(treetest);
}
void go_left_test(){
	
	huffmanTree * treetest = NULL;

	//empty tree case
	CU_ASSERT_PTR_NULL(go_left(treetest));

	//"full" tree case
	huffmanTree * nodeA=NULL;
	huffmanTree * nodeB=NULL;

	unsigned char byte='*';
	long long int frequency = 1;
	unsigned char byteA='a',byteB='b';
	long long int freqA=2,freqB=3;
	nodeA=createNODE(&byteA,freqA);
	nodeB=createNODE(&byteB,freqB);
	treetest = createTREE(&byte,frequency,nodeA,nodeB);
	
	huffmanTree * test = go_left(treetest);
	CU_ASSERT_PTR_EQUAL(getBYTE(test), byteA);
	CU_ASSERT_PTR_EQUAL(getFREQ(test), freqA);

	destroyHTREE(treetest);
}
void go_right_test(){
	huffmanTree * treetest = NULL;
	
	//empty tree
	CU_ASSERT_PTR_NULL(go_left(treetest));

	//"full" tree
	huffmanTree * nodeA=NULL;
	huffmanTree * nodeB=NULL;

	unsigned char byte='*';
	long long int frequency = 1;
	unsigned char byteA='a',byteB='b';
	long long int freqA=2,freqB=3;
	nodeA=createNODE(&byteA,freqA);
	nodeB=createNODE(&byteB,freqB);
	treetest = createTREE(&byte,frequency,nodeA,nodeB);
	
	huffmanTree * test = go_right(treetest);
	CU_ASSERT_PTR_EQUAL(getBYTE(test), byteB);
	CU_ASSERT_PTR_EQUAL(getFREQ(test), freqB);

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
}

void height_test(){

	unsigned char byte ='*';
	long long int freq=1;
	huffmanTree * ht= NULL;

	//empty tree
	CU_ASSERT_PTR_EQUAL(height(ht), -1);
	
	//tree with root only
	ht= createNODE(&byte,freq);
	CU_ASSERT_PTR_EQUAL(height(ht), 0);
	//adding more nodes

}

void tree_size_test(){
	unsigned char byte ='*';
	long long int freq=1;
	huffmanTree * ht= createNODE(&byte,freq);
	//CU_ASSERT_PTR_EQUAL(Tree_size(ht,0), 0);
// add more nodes and check
}

//END OF TREE FUNCTIONS

int main(){

	//initialize test registry
	if(CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	CU_pSuite creating_root_TEST = NULL;
	CU_pSuite creating_tree_TEST = NULL;
	CU_pSuite tree_features_TEST = NULL;

	//adding suites
	creating_root_TEST= CU_add_suite("Testing root creation",0,0);
	creating_tree_TEST= CU_add_suite("Testing tree creation",0,0);
	tree_features_TEST = CU_add_suite("Testing tree features",0,0);

	//huffman tree test
	CU_add_test(creating_root_TEST,"Testing 'create_node' function",create_node_test);
	CU_add_test(creating_tree_TEST,"Testing 'create_tree' function",create_tree_test);	
	CU_add_test(tree_features_TEST,"Testing 'isHTempty' function",isHTempty_test);	
	CU_add_test(tree_features_TEST,"Testing 'isLeaf' function",isLeaf_test);	
	CU_add_test(tree_features_TEST,"Testing 'go_left'function",go_left_test);
	CU_add_test(tree_features_TEST,"Testing 'go_right' function",go_right_test);	
	CU_add_test(tree_features_TEST,"Testing 'getBYTE' function",get_byte_test);	
	CU_add_test(tree_features_TEST,"Testing 'getFREQ' function",get_freq_test);	
	CU_add_test(tree_features_TEST,"Testing 'max test' function",max_test);
	CU_add_test(tree_features_TEST,"Testing 'height' function",height_test);
	CU_add_test(tree_features_TEST,"Testing 'tree_size' function",height_test);	

	//end of huffman tree test

	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_basic_run_tests();
	return CU_get_error();

}