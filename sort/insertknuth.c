// C program for reading
// struct from a file
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
//#include <mysql.h>
#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <stack>


using namespace std;





// struct person with 3 fields
struct person
{
	int id;
	char fname[20];
	char lname[20];
};
void printArray(struct person A[], int size)
{
        for (int i = 0; i < size; i++)
                cout << A[i].id << " ";
}
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

//5.2.1 Knuth
int i=0,j=0;
struct person R;
S1:;if(j>=n)goto END;
S2:;i=j - 1;R=arr[j];
S3:;if(R.id>=arr[i].id)goto S5;
S4:;arr[i+1]=arr[i];i--;if(i>0)goto S3;
S5:;arr[i+1]=R;j++;goto S1;
END:;












/*

  int i, j;
      for (i = 1; i < n; i++)
          {
               key = arr[i];
                  j = i - 1;

                      while (j >= 0 && arr[j].id > key.id)
                            {
                                  arr[j + 1] = arr[j];
                                      j = j - 1;
                                          }
                          arr[j + 1] = key;
                              }

*/

        t = clock() - t;
//printArray(arr,40000);
	printf (" time : %ld clicks (%f seconds).\n",t,((double)t)/CLOCKS_PER_SEC);

	return 0;
}
