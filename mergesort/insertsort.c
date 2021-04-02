// C program for reading
// struct from a file
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// struct person with 3 fields
struct person
{
	int id;
	char fname[20];
	char lname[20];
};

// Driver program
int main ()
{
	FILE *infile;
	struct person input, arr[40000], key;
int k=0;
        clock_t t;

        t = clock();



	// Open person.dat for reading
	infile = fopen ("person.dat", "r");
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}

	// read file contents till end of file
	while(fread(&input, sizeof(struct person), 1, infile)) {

  arr[k]=input;

  k++;
  }
	// close file
       int n = sizeof(arr) / sizeof(arr[0]);

  int i, j;
      for (i = 1; i < n; i++)
          {
               key = arr[i];
                  j = i - 1;

                     /* Move elements of arr[0..i-1], that are
                      *    greater than key, to one position ahead
                      *       of their current position */
                      while (j >= 0 && arr[j].id > key.id)
                            {
                                  arr[j + 1] = arr[j];
                                      j = j - 1;
                                          }
                          arr[j + 1] = key;
                              }



        t = clock() - t;

	printf (" time : %ld clicks (%f seconds).\n",t,((double)t)/CLOCKS_PER_SEC);

	return 0;
}
