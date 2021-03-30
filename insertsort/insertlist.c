// C program for reading
// struct from a file
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <iostream>

// using namespace std;

//struct person{};// struct person with 3 fields
struct person
{
    int id;
      char fname[20];
        char lname[20];
};

// Node of a doubly linked list
  struct Node {
    int data;
    struct person p;
          struct Node* prev, *next;
              };

                 // function to create and return a new node
                     // of a doubly linked list
                         struct Node* getNode(int data)
                             {
                                  // allocate node
                                       struct Node* newNode =
                                           (struct Node*)malloc(sizeof(struct Node));

                                               // put in the data
                                                   newNode->data = data;
                                                       newNode->prev = newNode->next = NULL;
                                                           return newNode;
                                                               }

    // function to insert a new node in sorted way in
         // a sorted doubly linked list
             void sortedInsert(struct Node** head_ref, struct Node* newNode)
                 {
                     struct Node* current;

                         // if list is empty
                             if (*head_ref == NULL)
                                 *head_ref = newNode;

                                     // if the node is to be inserted at the beginning
                                         // of the doubly linked list
                                             else if ((*head_ref)->p.id >= newNode->p.id) {
                                                 newNode->next = *head_ref;
                                                     newNode->next->prev = newNode;
                                                         *head_ref = newNode;
                                                              }
                                                                  else {
                                                                      current = *head_ref;
                                                                          // locate the node after which the new node
                                                                              // is to be inserted
                                                                                  while (current->next != NULL &&
                                                                                      current->next->p.id < newNode->p.id)
                                                                                          current = current->next;
                                                                                              /*Make the appropriate links */
                                                                                                  newNode->next = current->next;
                                                                                                      // if the new node is not inserted
                                                                                                          // at the end of the list
                                                                                                              if (current->next != NULL)
                                                                                                                  newNode->next->prev = newNode;
                                                                                                                      current->next = newNode;
                                                                                                                          newNode->prev = current;
                                                                                                                              }
                                                                                                                                  }




    // function to sort a doubly linked list using insertion sort
         void insertionSort(struct Node** head_ref)
             {
                 // Initialize 'sorted' - a sorted doubly linked list
                     struct Node* sorted = NULL;

                         // Traverse the given doubly linked list and
                             // insert every node to 'sorted'
                                 struct Node* current = *head_ref;
                                     while (current != NULL) {

                                         // Store next for next iteration
                                             struct Node* next = current->next;
                                                 // removing all the links so as to create 'current'
                                                     // as a new node for insertion
                                                         current->prev = current->next = NULL;
                                                             // insert current in 'sorted' doubly linked list
                                                                 sortedInsert(&sorted, current);
                                                                     // Update current
                                                                         current = next;
                                                                             }
                                                                                 // Update head_ref to point to sorted doubly linked list
                                                                                     *head_ref = sorted;
                                                                                        }
                                                                                             // function to print the doubly linked list
                                                                                                void printList(struct Node* head)
                                                                                                     {
                                                                                                         while (head != NULL) {
                                                                                                            // cout << head->p.id << " ";
                                                                                                                 head = head->next;
                                                                                                                     }
                                                                                                                         }



   // function to insert a node at the beginning of
        // the doubly linked list
            void push(struct Node** head_ref, struct person new_data)
                {
                    /* allocate node */
                       struct Node* new_node =
                            (struct Node*)malloc(sizeof(struct Node));
                                /* put in the data */
                                    new_node->p = new_data;
                                        /* Make next of new node as head and previous as NULL */
                                            new_node->next = (*head_ref);
                                                new_node->prev = NULL;
                                                    /* change prev of head node to new node */
                                                        if ((*head_ref) != NULL)
                                                          (*head_ref)->prev = new_node;
                                                                /* move the head to point to the new node */
                                                                    (*head_ref) = new_node;
                                                                        }






// struct person with 3 fields
/*struct person
{
	int id;
	char fname[20];
	char lname[20];
};
*/
// Driver program
int main ()
{
	FILE *infile;
	struct person input, arr[4000];
//int k=0;
        clock_t t;

       // t = clock();



	// Open person.dat for reading
	infile = fopen ("person.dat", "r");
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}
    struct Node* head = NULL;

	// read file contents till end of file
	while(fread(&input, sizeof(struct person), 1, infile)) {
	 // Moving pointer to end
	 //      fseek(infile, sizeof(struct person)*2, 0);
	//fread(&input, sizeof(struct person), 1, infile);
	//	printf ("id = %d name = %s %s\n", input.id, input.fname, input.lname);

 push(&head, input);
 //arr[k]=input;

  //printf("%i ", arr[k].id);
 // k++;
  }


        t = clock();


                          //cout << "Doubly Linked List Before Sorting\n";
                            //  printList(head);
                                  insertionSort(&head);
                                      //cout << "\nDoubly Linked List After Sorting\n";
                                       //   printList(head);






  // close file
	fclose (infile);
                int n = sizeof(arr)/sizeof(arr[0]);








  //              for (int i=0;i<4000;++i)
    //                   printf("%i ", arr[i].id);
     //        printf("\n");


        t = clock() - t;

	printf (" time : %ld clicks (%f seconds).\n",t,((double)t)/CLOCKS_PER_SEC);

	return 0;
}
