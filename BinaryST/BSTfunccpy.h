#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {true=1,false=0}bool; 

static bool found = false;

//BST Node struct that stores a int
typedef struct Node{
   int key;
   struct Node* left;
   struct Node* right;
   char* color;
   //OPTIONAL:  struct Node* parent 
}Node;

typedef struct Queue{
   int size;
   Node** arr; 
}Queue;

Queue* newQueue();
void enqueue(Node* input,Queue* q);
Node* dequeue(Queue* q);
bool emptyQueue(const Queue* q);
void freeQueue(Queue* q);

//Not using the entire math library for one function lol
int sigfigs(int a);
Node* new(int key);

Node* search(Node* root, int key);
Node* insert(Node* root,int key);
Node* minValueNode(Node* root);
Node* delete(Node* root,int key);

void inorder(Node* root,bool colonize); 
void preorder(Node* root);
void postorder(Node* root);

void BFS(Node* root,int count);

Node* DFSinorder(Node* root,int key);
Node* DFSpreorder(Node* root,int key);
Node* DFSpostorder(Node* root,int key);

int depth(Node* root);
void freetree(Node* root);
#endif
