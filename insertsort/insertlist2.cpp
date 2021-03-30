#include <iostream>
struct person
{
      int id;
            char fname[20];
                    char lname[20];
};

class Node {
 public:
   Node *next;
   int data;
};

typedef Node * ListType;

void insertionSort(ListType &list) {
      ListType *p = &list;
    while ( (*p)->next && (*p)->next->data < (*p)->data)
       {
          ListType node= *p;
          *p=node->next;
          node->next=node->next->next;
          (*p)->next=node;
      p= &(*p)->next;
       }
}

int main()
{

 FILE *infile;
 struct person input ;
 //int k=0;
 clock_t t;

 t = clock();

// Open person.dat for reading
 infile = fopen ("person.dat", "r");
if (infile == NULL)
  {
 fprintf(stderr, "\nError opening file\n");
   exit (1);
  }
 Node* head = NULL;
  // read file contents till end of file
  while(fread(&input, sizeof(struct person), 1, infile)) {
 // Moving pointer to end
 //      fseek(infile, sizeof(struct person)*2, 0);
 //fread(&input, sizeof(struct person), 1, infile);
 //      printf ("id = %d name = %s %s\n", input.id, input.fname, input.lname);
//push(&head, input.id);
  //arr[k]=input;
 //printf("%i ", arr[k].id);
 // k++;
 //}
 // close file
// fclose (infile);

    //  Node *head=0;
   // push(&head, input.id);
//}
     int n;
    //while (std::cout << ">>> ", std::cin >> n)
  // {
   Node *p=new Node;
    p->data=input.id;
   p->next=head;
    head=p;
     insertionSort(head);
    for (p=head; p; p=p->next)
   // std::cout << p->data << " ";
    //std::cout << std::endl;
    ;; }
      fclose (infile);
        t = clock() - t;

                printf (" time : %ld clicks (%f seconds).\n",t,((double)t)/CLOCKS_PER_SEC);




}

