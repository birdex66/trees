#include "BSTfunc.h"

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
		  height = depth(root);
                  printf("height: %i\n",height);
             	  goto c3; 
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

