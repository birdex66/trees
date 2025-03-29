#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {true=1,false=0}bool; 

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

static bool found = false;

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

void menu(){
   Node* root = NULL;
   int count = 0;
   int height;

   while(true){
      printf("Interact with a BST!\n\n");
      printf("1: Insert\n");
      printf("2: Remove\n");
      printf("3: View\n");
      printf("4: Search\n");
      printf("5: Clear Tree\n");
      printf("6: Practice\n");
      printf("7: Learn\n");
      printf("8: Quit\n");

      printf("\nInput --> ");

      char* input;

      size_t leninput = 0;
      ssize_t read = getline(&input,&leninput,stdin);

      int conv,key;

      switch(atoi(input)){
         case 1:
c1:
            printf("Enter a value to insert (B to go back)--> ");
            read = getline(&input,&leninput,stdin);
            if(!strcmp("B\n",input)) break;
            conv = atoi(input);

            if(sigfigs(conv) != read-1){
               printf("Invalid Input.\n");
               goto c1;
            }

            root = insert(root,conv);
            ++count;
            goto c1;
         case 2:
c2:
            printf("Enter a value to remove (B to go back)--> ");
            read = getline(&input,&leninput,stdin);
            if(!strcmp("B\n",input)) break;
            conv = atoi(input);

            if(sigfigs(conv) != read-1){
               printf("Invalid Input.\n");
               goto c2;
            }

            root = delete(root,conv);
            if(found) --count;
            else printf("Value not found.\n");
            found = false;
            goto c2;
         case 3:
c3:
            printf("1: Display Tree\n");
            printf("2: Print Order\n");
            printf("3: Back\n");
            printf("\nInput --> ");
            read = getline(&input,&leninput,stdin);

            switch(atoi(input)){
               case 1:
                  printf("height: %i\n",depth(root));
                  break;
               case 2:
c3c2:
                  printf("1: Inorder Traversal\n");
                  printf("2: Preorder Traversal\n");
                  printf("3: Postorder Traversal\n");
                  printf("4: Back\n");
                  printf("\nInput --> ");

                  read = getline(&input,&leninput,stdin);

                  switch(atoi(input)){
                     case 1:
                        inorder(root);
                        break;
                     case 2:
                        preorder(root);
                        break;
                     case 3:
                        postorder(root);
                        break;
                     case 4:
                        goto c3;
                  }
                  goto c3c2;
            }

            break;
         case 4:
c4:
            printf("1: Depth First Search\n");
            printf("2: Breadth First Search\n");
            printf("3: Binary Search\n");
            printf("4: Back\n");
            printf("\nInput --> ");

            read = getline(&input,&leninput,stdin);

            switch(atoi(input)){
               case 1:
c4c1:
                  printf("1: Inorder Traversal\n");
                  printf("2: Preorder Traversal\n");
                  printf("3: Postorder Traversal\n");
                  printf("4: Back\n");
                  printf("\nInput --> ");

                  read = getline(&input,&leninput,stdin);
                  conv = atoi(input);
                  if(conv == 4) goto c4;

                  printf("\nLooking for --> ");
                  read = getline(&input,&leninput,stdin);

                  switch(conv){
                     case 1:
                        DFSinorder(root,atoi(input));
                        break;
                     case 2:
                        DFSpreorder(root,atoi(input));
                        break;
                     case 3:
                        DFSpostorder(root,atoi(input));
                        break;
                  }
                  goto c4c1;
               case 2:
                  //TODO
                  goto c4;
               case 3:
                  printf("\nLooking for --> ");
                  read = getline(&input,&leninput,stdin);
                  search(root,atoi(input));
                  goto c4;

            }
            break;
         case 5:
            printf("Clearing Tree..\n\n");
            if(root) freetree(root),root=NULL;
            break;
         case 6:
c6:
            //TODO
            printf("1: Insertion\n");
            printf("2: Removal\n");
            printf("3. Order of Traversal\n");
            printf("4: Back\n");

            printf("Select Practice Mode --> ");
            read = getline(&input,&leninput,stdin);
            int choice = atoi(input);
            if(choice == 4) break;

            printf("1: Use Current List\n");
            printf("2: Use Random List\n");
            printf("3: Back\n");
            printf("\nInput --> ");

            read = getline(&input,&leninput,stdin);
            if(atoi(input) == 3) goto c6;


            break;
         case 7:
            //TODO
            printf("Learning\n");
            break;
         case 8:
            printf("Quitting...\n");
            free(input);
            freetree(root);
            return;
         default:
            break;
      }
   }
}

int main(){
   menu();
   return 0;
}

