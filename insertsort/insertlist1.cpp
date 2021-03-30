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
struct node {
      int data;
      struct person p;
          struct node *next;
};


void insertion(struct node **head) {
   if((*head)== NULL || (*head)->next == NULL)
      return;

     struct node *t1 = (*head)->next;
      while(t1) {
        int sec_data = t1->data;
         int found = 0;
        struct node *t2 = *head;
        while(t2 != t1) {
       if(t2->data > t1->data && found == 0) {
      // sec_data = t2->data;
      //t2->data = t1->data;



      found = 1;
      t2 = t2->next;
      } else {
      if(found == 1) {
      int temp = sec_data;
      sec_data = t2->data;
      t2->data = temp;
      }
      t2 = t2->next;
       }
    }
   t2->data = sec_data;
     t1 = t1->next;
     }
}


/* BELOW FUNCTIONS ARE JUST UTILITY TO TEST sortedInsert */

/* Function to print linked list */
void printList(struct node *head)
{
      struct node *temp = head;
          while(temp != NULL)
                {
                          printf("%d  ", temp->data);
                                  temp = temp->next;
                                      }
}

/* A utility function to insert a node at the beginning of linked list */
void push(struct node** head_ref, int new_data)
{
      /* allocate node */
      struct node* new_node = new node;

          /* put in the data  */
          new_node->data  = new_data;

              /* link the old list off the new node */
              new_node->next = (*head_ref);

                  /* move the head to point to the new node */
                  (*head_ref)    = new_node;
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
	struct person input ;
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
    struct node* head = NULL;

	// read file contents till end of file
	while(fread(&input, sizeof(struct person), 1, infile)) {
	 // Moving pointer to end
	 //      fseek(infile, sizeof(struct person)*2, 0);
	//fread(&input, sizeof(struct person), 1, infile);
	//	printf ("id = %d name = %s %s\n", input.id, input.fname, input.lname);

push(&head, input.id);
 //arr[k]=input;

  //printf("%i ", arr[k].id);
 // k++;
  }
 // close file
        fclose (infile);


        t = clock();


  struct node *a = NULL;
      push(&a, 5);
        push(&a, 20);
           push(&a, 4);
             push(&a, 3);
                 push(&a, 30);

                          printf("Linked List before sorting \n");
                             // printList(head);

                                  insertion(&head);

                                      printf("\nLinked List after sorting \n");
                                       //   printList(head); //cout << "Doubly Linked List Before Sorting\n";
                            //  printList(head);
                              //    insertionSort(&head);
                                      //cout << "\nDoubly Linked List After Sorting\n";
                                  //    printList(head);






  //             int n = sizeof(arr)/sizeof(arr[0]);






  //              for (int i=0;i<4000;++i)
    //                   printf("%i ", arr[i].id);
     //        printf("\n");


        t = clock() - t;

	printf (" time : %ld clicks (%f seconds).\n",t,((double)t)/CLOCKS_PER_SEC);

	return 0;
}
