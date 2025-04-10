#include "BSTfunc.h"

//Not using the entire math library for one function lol
int sigfigs(int a){
   if(a == 0) return 1;
   int sigfigs = 0;
   while(a > 0){
      a/=10;
      ++sigfigs;
   }
   return sigfigs;
}

// helper method for making new node
Node* new(int key){
   Node* root = malloc(sizeof(Node));
   root->key = key;
   root->left = NULL,root->right = NULL;
   root->color = "white";
   return root;
}

// initalizes queue
Queue* newQueue(){
   Queue* q = malloc(sizeof(Queue)); 
   q->size = 0;
   q->arr = NULL;
   return q;
}

// adds element to back of queue
void enqueue(Node* input,Queue* q){
   q->arr = (Node**)realloc(q->arr,((q->size)+1)*sizeof(Node*)); //reallocating q->arr for additional element
   ++(q->size);
   for(int i=q->size-1; i>0; --i){ //shifts all elements right
      q->arr[i] = q->arr[i-1];
   }
   q->arr[0] = input; // adds at index 0
}

//removes element from front of queue
Node* dequeue(Queue* q){
   if(q->size == 0) return NULL;

   Node* n = q->arr[q->size-1];
   q->arr[q->size-1] = NULL; 
   q->arr = (Node**)realloc(q->arr,((q->size)-1)*sizeof(Node*)); //reallocating q->arr for one less element
   --(q->size);
   return n; // returns removed element for comparison
}

// if queue is empty
bool emptyQueue(const Queue* q){ return q->size==0;}

//frees content of queue, then struct
void freeQueue(Queue* q){
   free(q->arr);
   free(q);
}

Node* search(Node* root, int key){

   // Base Key is NULL:
   //if(root == NULL || root->key == key) return root;

   if(root == NULL){
      printf("Found nothing...\n\n");
      return root;
   }else if(root->key == key){
      printf("Found %i!!\n\n",key);
      return root;
   }
   printf("At %i",root->key);
   printf("...traveling left!\n");
   //Current Key is greater than target key, recurse left
   if(root->key > key) return search(root->left,key);

   printf("...traveling right!\n");
   //Current Key is less than target key, recurse right
   return search(root->right,key);
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
      found = true;
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

// least to greatest key, also resets tree colors if needed
void inorder(Node* root, bool colonize){
   if(root == NULL) return;
   else{
      if(colonize) root->color = "white";
      inorder(root->left,colonize);

      if(root->left == NULL && root->right == NULL && !colonize) printf("Leaf: %i\n",root->key);
      else if(!colonize) printf("Parent: %i\n",root->key);

      inorder(root->right,colonize);
   }
}

// 
void preorder(Node* root){
   if(root == NULL) return;
   else{
      if(root->left == NULL && root->right == NULL) printf("Leaf: %i\n",root->key);
      else printf("Parent: %i\n",root->key);

      preorder(root->left);
      preorder(root->right);
   }
}

void postorder(Node* root){
   if(root == NULL) return;
   else{
      postorder(root->left);
      postorder(root->right);

      if(root->left == NULL && root->right == NULL) printf("Leaf: %i\n",root->key);
      else printf("Parent: %i\n",root->key);
   }
}



void BFS(Node* root,int count){
   if(root == NULL) return;
   inorder(root,true);

   root->color = "gray";
   Queue* q = newQueue();
   enqueue(root,q);

   int arr[count];
   int i = 0;

   while(!emptyQueue(q)){
      Node* u = dequeue(q);
      Node* uleft = u->left;
      Node* uright = u->right;

      if(uleft && !strcmp(uleft->color,"white")){
         uleft->color = "gray";
         enqueue(uleft,q);
      }

      if(uright && !strcmp(uright->color,"white")){
         uright->color = "gray";
         enqueue(uright,q);
      }

      u->color = "black";
      arr[i++] = u->key;
   }

   int height = depth(root)+1;
   int base = (height*2)-1;
   int spaces = base/2;
   
   int treeIndex = 0;
   int spacesPerLevel = height * 3;
   spaces += spacesPerLevel;
   for(int j=0; j<height; ++j){
      int nodesLevel = 1 << j;
      int nodesPrinted = 0;
      
      int k =0;// !j ? 0-spacesPerLevel:0;
      for(;k<spaces; ++k){
            printf(" ");
      }

      int s=0;
      while(nodesPrinted < nodesLevel && treeIndex < count){
         printf("%i",arr[treeIndex++]);
         while(s<spacesPerLevel){
            printf(" ");
            ++s;
         }
         s=0;
         ++nodesPrinted;
      }
      spacesPerLevel -= 3;
      spaces -= 3;
      printf("\n");
   }

   freeQueue(q);
}

Node* BFSsearch(Node* root, int count){
   if(root == NULL) return NULL;
   inorder(root,true);

   root->color = "gray";
   Queue* q = newQueue();
   enqueue(root,q);

   int arr[count];
   int i = 0;

   while(!emptyQueue(q)){
      Node* u = dequeue(q);
      Node* uleft = u->left;
      Node* uright = u->right;

      if(uleft && !strcmp(uleft->color,"white")){
         uleft->color = "gray";
         enqueue(uleft,q);
      }

      if(uright && !strcmp(uright->color,"white")){
         uright->color = "gray";
         enqueue(uright,q);
      }

      u->color = "black";
      arr[i++] = u->key;
   }

   int height = depth(root)+1;
   int base = (height*2)-1;
   int spaces = base/2;
   
   int treeIndex = 0;
   int spacesPerLevel = height * 3;
   spaces += spacesPerLevel;
   for(int j=0; j<height; ++j){
      int nodesLevel = 1 << j;
      int nodesPrinted = 0;
      
      int k =0;// !j ? 0-spacesPerLevel:0;
      for(;k<spaces; ++k){
            printf(" ");
      }

      int s=0;
      while(nodesPrinted < nodesLevel && treeIndex < count){
         printf("%i",arr[treeIndex++]);
         while(s<spacesPerLevel){
            printf(" ");
            ++s;
         }
         s=0;
         ++nodesPrinted;
      }
      spacesPerLevel -= 3;
      spaces -= 3;
      printf("\n");
   }

   freeQueue(q);



}

Node* DFSinorder(Node* root,int key){
   if(root == NULL){
      printf("...found nothing\n");
      return root;
   } 

   printf("Checking left tree...\n");
   Node* temp = DFSinorder(root->left,key);
   if(temp) return temp;

   if(root->key == key){ 
      printf("Found %i!!\n",key);
      return root;
   }

   if(root->left == NULL && root->right == NULL) printf("Leaf: %i\n",root->key);
   else printf("Parent: %i\n",root->key);

   printf("Checking right tree...\n");
   return DFSinorder(root->right,key);
}


Node* DFSpreorder(Node* root,int key){
   if(root == NULL){
      printf("...found nothing\n");
      return root;
   }else if(root->key == key){ 
      printf("Found %i!!\n",key);
      return root;
   }

   if(root->left == NULL && root->right == NULL) printf("Leaf: %i\n",root->key);
   else printf("Parent: %i\n",root->key);

   printf("Checking left tree...\n");
   Node* temp = DFSpreorder(root->left,key);
   if(temp) return temp;

   printf("Checking right tree...\n");
   return DFSpreorder(root->right,key);
}

Node* DFSpostorder(Node* root,int key){
   if(root == NULL){
      printf("Found nothing...\n");
      return root;
   }else if(root->key == key){ 
      printf("Found %i!!\n",key);
      return root;
   }
   printf("Checking left tree...\n");
   Node* temp =  DFSpostorder(root->left,key);
   if(temp) return temp;

   printf("Checking right tree...\n");
   temp=DFSpostorder(root->right,key);
   if(temp) return temp;

   if(root->left == NULL && root->right == NULL) printf("Leaf: %i\n",root->key);
   else printf("Parent: %i\n",root->key);
   return temp;
}

int depth(Node* root){
   if(root == NULL) return -1;

   int depthL = depth(root->left);
   int depthR = depth(root->right);

   return ((depthL > depthR) ? depthL:depthR)+1;
}

void freetree(Node* root){
   if(root == NULL) return;
   freetree(root->left);
   freetree(root->right);
   free(root);
}


