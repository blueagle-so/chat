// C program for writing
// struct to file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// a struct to read and write
struct person
{
	int id;
	char fname[20];
	char lname[20];
};

int main ()
{
	FILE *outfile;

	// open file for writing
	outfile = fopen ("person.dat", "w");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opend file\n");
		exit (1);
	}

	struct person input1 = {1, "rohan", "sharma"};
	struct person input2 = {2, "mahendra", "dhoni"};

	 struct person input3 = {3, "roh", "srma"};
   struct person input4 = {4, "ndra", "dhi"};
	// write struct to file
	for(int i=0;i<10000;i++){
	fwrite (&input1, sizeof(struct person), 1, outfile);
	fwrite (&input2, sizeof(struct person), 1, outfile);


	fwrite (&input3, sizeof(struct person), 1, outfile);
	fwrite (&input4, sizeof(struct person), 1, outfile);
	}

	if(fwrite != 0)
		printf("contents to file written successfully !\n");
	else
		printf("error writing file !\n");

	// close file
	fclose (outfile);

	return 0;
}
