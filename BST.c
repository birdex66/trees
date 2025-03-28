#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//BST Node struct that stores a int
typedef struct Node{
	int key;
	struct Node* left;
	struct Node* right;
	//OPTIONAL:  struct Node* parent 
}Node;

// helper method for making new node
Node* new(int key){
	Node* root = malloc(sizeof(Node));
	root->key = key;
	root->left = NULL,root->right = NULL;
	return root;
}

Node* search(Node* root, int key){

	// Base Key is NULL:
	if(root == NULL || root->key == key) return root;

	//Current Key is greater than target key, recurse left
	if(root->key > key) return search(root->left,key);

	//Current Key is less than target key, recurse right
	else return search(root->right,key);
}

Node* insert(Node* root,int key){

	// If tree is empty, return a new node
	if(root == NULL){
		Node* root = new(key);
		return root;
	}

	// Current Key is greater than target key, recurse left
	// Assigns result of prev recursion layer to current node
	if(root->key > key) root->left = insert(root->left,key);

	// Current Key is less than target key, recurse right
	// Assigns result of prev recursion layer to current node
	else if(root->key < key) root->right = insert(root->right,key);

	//printf("Inserted: %i\n",root->key);
	// return the unchanged node pointer
	return root;
}

//helper method for deleting node
Node* minValueNode(Node* root){
	if(root->left == NULL) return root;
	else return minValueNode(root->left);
}

Node* delete(Node* root,int key){

	// find if key exists in BST from root. if true, return the root pointer to the Updated BST after removing key
	if(root == NULL) return root;

	// if root is bigger than key, recurse left
	if(root->key > key) root->left = delete(root->left,key);

	// else if root is smaller than key, recurse right
	else if (root->key < key) root->right = delete(root->right,key);

	// if key is equal to root...
	else{
		// node has one(only has a left or right child) or zero children:
		if(root->left == NULL){
			Node* temp = root->right; //from main, we set root=delete(root,root->key);
			free(root);
			return temp;
		}else if(root->right == NULL){
			Node* temp = root->left; //from main, we set root=delete(root,root->key);
			free(root);
			return temp;
		}

		// node has two children
		Node* temp = minValueNode(root->right); // can also be MAXvalueNode(root->left).we call this a inorder successor

		// copy inorder successor to root 
		root->key = temp->key;

		// delete inorder successor
		root->right = delete(root->right,temp->key);
	}
	return root;
}

/* modes of tree traversal */

// least to greatest key
void inorder(Node* root){
	if(root == NULL) return;
	else{
		inorder(root->left);

		if(root->left == NULL && root->right == NULL) printf("Leaf: %i\n",root->key);
		else printf("Parent: %i\n",root->key);

		inorder(root->right);
	}
}

// 
void preorder(Node* root){
	if(root == NULL) return;
	else{
		if(root->left == NULL && root->right == NULL) printf("Leaf: %i\n",root->key);
		else printf("Parent: %i\n",root->key);

		inorder(root->left);
		inorder(root->right);
	}
}

void postorder(Node* root){
	if(root == NULL) return;
	else{
		inorder(root->left);
		inorder(root->right);

		if(root->left == NULL && root->right == NULL) printf("Leaf: %i\n",root->key);
		else printf("Parent: %i\n",root->key);
	}
}

void freetree(Node* root){
	if(root == NULL) return;
	freetree(root->left);
	freetree(root->right);
	free(root);
}

int main(){
	int arr[] = {5, 2, 1, 7, 4, 6, 3};
	int i=0,len = sizeof(arr)/sizeof(arr[0]);

	Node* root = NULL;
	while(i < len) root = insert(root,arr[i++]);
	
	printf("Enter \"quit\" to exit.\n");
	redo:
	printf("\nChoose your method of traversal(in,pre,post): ");	

	char input[8];
        scanf("%s",input);

	if(!strcmp("in",input)){
		inorder(root);
	}else if(!strcmp("pre",input)){
		preorder(root);
	}else if(!strcmp("post",input)){
		postorder(root);
	}else if(!strcmp("quit",input)){
		freetree(root);
		return 0;
	}
	
	goto redo;	

	freetree(root);
	return 1;
}

