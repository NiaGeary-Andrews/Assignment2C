#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>
#include "bst.h"

struct _Node {
  int data;
  Node * left, * right;
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* 
   Returns the parent of an either existing or hypotetical node with the given data  
 */
Node * find_parent(Node * root, int data) {
  assert(root != NULL);
  assert(data != root->data);

  Node * next = data < root->data ? root->left : root->right;

  if (next == NULL || next->data == data)
    return root;
  else
    return find_parent(next, data);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* 
   Constructs a new node
 */
Node * mk_node(int data) {
  Node * node = (Node *) malloc(sizeof(Node));
  node->data = data;
  node->left = node->right = NULL;
  return node;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
Node * insertNode(Node * root, int data) {
  if (root == NULL)
    return mk_node(data);

  if (data == root->data)
    return NULL;

  Node * parent = find_parent(root, data);
  Node * child = data < parent->data ? parent->left : parent->right;
  assert(child == NULL || child->data == data);

  if (child == NULL) {
    // data not found, then insert and return node   
    child = mk_node(data);
    if (data < parent->data)
      parent->left = child;
    else
      parent->right = child;

    //return child;
   //return parent;
   return root;
  } else {
    // data found, then return null
    return NULL;
  } 
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool is_ordered(Node * root) {
  if (root == NULL)
    return true;
  if (root->left && root->left->data > root->data)
    return false;
  if (root->right && root->right->data < root->data)
    return false;
  return true;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
Node * deleteNode(Node * root, int data) {
  assert(is_ordered(root));

  // empty tree
  if (root == NULL)
    return NULL;

  // find node with data 'data' and its parent node 
  Node * parent, * node;
  if (root->data == data) {
    parent = NULL;
    node = root;
  } else {
    parent = find_parent(root, data);
    node = data < parent->data ? parent->left : parent->right;
  }
  assert(node == NULL || node->data == data);

  // data not found
  if (node == NULL)
    return root;

  // re-establish consistency
  Node * new_node;
  if (node->left == NULL) {
    // node has only right child, then make right child the new node
    new_node = node->right;
  } else {
    // otherwise make right child the rightmost leaf of the subtree rooted in the left child
    // and make the left child the new node
    Node * rightmost = new_node = node->left;
    while (rightmost->right != NULL)
      rightmost = rightmost->right;
    rightmost->right = node->right;
  }

  free(node);

  Node * new_root;
  if (parent == NULL) {
    // if deleted node was root, then return new node as root 
    new_root = new_node;
  } else {
    // otherwise glue new node with parent and return old root
    new_root = root;
    if (data < parent->data) 
      parent->left = new_node;
    else 
      parent->right = new_node;
  }

  assert(is_ordered(new_root));

  return new_root;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
void printSubtree(Node * N) {
  if (N == NULL){
  	return;
  }
  printSubtree(N->left);
  printf("%d \n", N->data);
  printSubtree(N->right);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
int countLeaves(Node * N) {
  if (N == NULL)
    return 0;

  if (N->left == NULL && N->right == NULL)
    return 1;
  
  return countLeaves(N->left) + countLeaves(N->right);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* 
   Frees the entire subtree rooted in 'root' (this includes the node 'root')
 */
void free_subtree(Node * root) {
  if (root == NULL)
    return;

  free_subtree(root->left);
  free_subtree(root->right);
  free(root);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 The function freeSubtree returns the new root after freeing the tree, unlike in assignment 1 where no return value was required. After freeing the entire tree the new root is that of the empty tree, which is NULL. This is clear from test_bst.c at lines 27 and 28.
*/
Node* freeSubtree(Node *N){
  if (N == NULL)
    return NULL;

  freeSubtree(N->left);
  freeSubtree(N->right);
  free(N);
  return NULL;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* 
   Deletes all nodes that belong to the subtree (of the tree of rooted in 'root') 
   whose root node has data 'data'
 */
Node * deleteSubtree(Node * root, int data) {
  assert(is_ordered(root));

  // empty tree
  if (root == NULL)
    return NULL;

  // entire tree
  if (root->data == data) {
    free_subtree(root);
    return NULL;
  }

  // free tree rooted in the left or right node and set the respective pointer to NULL 
  Node * parent = find_parent(root, data);
  if (data < parent->data) {
    assert(parent->left == NULL || parent->left->data == data);
    free_subtree(parent->left);
    parent->left = NULL;
  } else {
    assert(parent->right == NULL || parent->right->data == data);
    free_subtree(parent->right);
    parent->right = NULL;
  }

  return root;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* 
   Compute the depth between root R and node N 

   Returns the number of edges between R and N if N belongs to the tree rooted in R,
   otherwise it returns -1
 */
int depth (Node * R, Node * N) {
  if (R == NULL || N == NULL)
    return -1;
  if (R == N)
    return 0;

  int sub_depth = depth(R->data > N->data ? R->left : R->right, N);

  if (sub_depth >= 0)
    return sub_depth + 1;
  else
    return -1;
}

//----------------------------------------------------------------------------------------------------------------------------------------------
//counts nodes, look further into this!!
int countNodes(Node* root){
	//TODO: write this function
}


// --------------------------------------------------------------------------------------------------------------------------------------------
// Sums together the nodes of the trees
int sumSubtree(Node *N)
{
  int sum;	
  if (N == NULL) {
  	return 0;
  }
	
  else{
        return((sumSubtree(N->left)) + (N->data) + (sumSubtree(N->right)));
  }

}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// For this part I am first going to do an inorder traversal of the tree and store the nodes in a dynamic array. Which I am going to create using pointers and the malloc function

//This is for working out the size of the tree so I know how big of an array to create
int sizeOfTree(Node* root){
	if (root == NULL){
		return 0;
	}
	else{
	     return(sizeOfTree(root->left) + 1 + sizeOfTree(root->right));
	}
}

int i = 0;

/*
//HAS SAME SUM EVERYTIME BUT FAILS IN SECOND PART
//---------------------------------------------------------------------------------------------------------------------------------------------------
//creates an in order array of elements. This returns a pointer to an array as C does not allow returning arrays from functiom
//TO DO WITH THIS FUNCTION AND THE WAY THE I IS BEING INCREMENTED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int * inOrder(Node* root, int arr[], int i){
	
	
  	//if the tree is empty it returns an empty list
  	if (root == NULL){
  		return NULL;
  	}
  	else{
  	  	//arr[i] = (root->data);
  		inOrder(root->left,arr,i++);
  		arr[i] = (root->data);
  		inOrder(root->right,arr,i++);
  		return arr;
  	}
}

*/

//SUPPOSEDLY PASSES EVERYTIME BUT HAS DIFFERENCE IN SUMS
//---------------------------------------------------------------------------------------------------------------------------------------------------
//creates an in order array of elements. This returns a pointer to an array as C does not allow returning arrays from functiom
//SORTED THIS OUT NOW, IT WORKS
int * inOrder(Node* root, int arr[]){
	
	
  	//if the tree is empty it returns an empty list
  	if (root == NULL){
  		return NULL;
  	}
  	else{
  	  	//arr[i] = (root->data);
  		inOrder(root->left,arr);
  		arr[i] = (root->data);
  		i++;
  		inOrder(root->right,arr);
  		return arr;
  	}
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------
//this sorts the array into the balanced subtree by getting the middle element and making it the root. Then recursively doing this for the left and right subtrees
//thinking I might need to use the insert node function here but not sure?

Node* sortArray(Node *root,int arr[], int start, int end){
    if (start > end){
       return NULL;
    }
    //think this code may be the problem, try taking root out an dthen just recalling everytime. Put it in the balance tree function
	
    //makes the middle element the root
    int mid = (start + end)/2; 
    //Node *root = mk_node(arr[mid]); 
    root = mk_node(arr[mid]);
  
    //uses recursion to get the next element in the array and makes it the left child of the current root
    root->left = sortArray(root->left, arr, start, mid-1); 
    //root->left = sortArray(arr, start, mid-1);
  
    //uses recursion to get the next element in the array and makes it the right child of the current root
    //root->right = sortArray(arr, mid+1, end); 
    root->right = sortArray(root->right, arr, mid+1, end);
    //free(arr);
    return root; 
}


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// This functions converts an unbalanced BST to a balanced BST 
// Goal: create an array and append the elements to the array in this order. I will get the size of this array by making a function that gets the size of the tree and a separate one that creates an in order traversal of the tree and stores it in a list. Then using this list I will do what the assignment spec says to make it into a balanced tree. Will have to create a new root node and tree so can still traverse the old one. Build new array then build tree in separate functions!!!

/*
 	1) Get the middle element of the sorted array and make it the root of the tree.
	2) Recursively do same for the left half and right half.
		a) Get the middle of the left half and make it the left child of the root created in step
		b) Get the middle of the right half and make it the right child of the root created in step 1. You might need helper functions during the implementation.
*/

Node* balanceTree(Node* root){
	//inOrder(root);
	int size = sizeOfTree(root);
	int * array_pointer;
	//int a =1;
	if((array_pointer = (int *)malloc(sizeof(int)*size)) == NULL){
		printf("Allocation failed");
		exit(-1);
	}
	
	
	//array_pointer = (int *)malloc(sizeof(int)*size);
	/*if (size == 1){
		a = 1;
	}
	else{
		a = size-1;
	}*/
	return sortArray(NULL,(inOrder(root,array_pointer)), 0, (size)-1);
}












