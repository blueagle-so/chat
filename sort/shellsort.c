// C program for reading
// struct from a file
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mysql/mysql.h>
#include <iostream>
#include <vector>
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
  MYSQL *conn;
    MYSQL_RES *res;
      MYSQL_ROW row;

      //int arr[10]={0,0,0,0,0,0,0,0,0,0};
        std::vector<person> arr;
        conn = mysql_init(NULL);
          if(conn == NULL)
            {
              fprintf(stderr, "Error: can'tcreate MySQL-descriptor\n");
                }
                  if(!mysql_real_connect(conn, "localhost", "root", NULL, "test", NULL, NULL, 0)
                  ){
                    fprintf(stderr, "Error: can'tconnecttodatabase %s\n", mysql_error(conn));
                      }
                        else
                          {
                            fprintf(stdout, "Success!\n");
                              }

mysql_query(conn,"SELECT ProductCount  FROM Products");
person tmp;
   res = mysql_store_result(conn);
          while(row = mysql_fetch_row(res)){
                         for (int l=0 ; l <mysql_num_fields(res); l++){
                                             tmp.id=atoi(row[l]);

                arr.push_back(tmp);
               // std::cout<< arr[l]<<std::endl;
                                                                            }
                                      }

             //        } else fprintf(stderr, "%s\n", mysql_error(conn));

/*  FILE *infile;
	struct person input, arr[4000];
int k=0;
*/
      clock_t t;

        t = clock();


/*
	// Open person.dat for reading
	infile = fopen ("person.dat", "r");
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}

	// read file contents till end of file
	while(fread(&input, sizeof(struct person), 1, infile)) {
	 // Moving pointer to end
	 //      fseek(infile, sizeof(struct person)*2, 0);
	//fread(&input, sizeof(struct person), 1, infile);
	//	printf ("id = %d name = %s %s\n", input.id, input.fname, input.lname);

  arr[k]=input;

  //printf("%i ", arr[k].id);
  k++;
  }
	// close file
	fclose (infile);
  */
  int n = 7941;
   // Start with a big gap, then reduce the gap
       for (int gap = n/2; gap > 0; gap /= 2)
            {
                 // Do a gapped insertion sort for this gap size.
                 // The first gap elements a[0..gap-1] are already in gapped order
                // keep adding one more element until the entire array is
                // gap sorted
      for (int i = gap; i < n; i += 1)
        {
               // add a[i] to the elements that have been gap sorted
              // save a[i] in temp and make a hole at position i
              struct person temp = arr[i];
             // shift earlier gap-sorted elements up until the correct
             // location for a[i] is found
               int j;
             for (j = i; j >= gap && arr[j - gap].id > temp.id; j -= gap)
             {
             arr[j] = arr[j - gap];
            //  put temp (the original a[i]) in its correct location
             }
             arr[j] = temp;

             }
              }
               for (int i=0;i<n;++i)
                       printf("%i ", arr[i].id);
             printf("\n");


        t = clock() - t;

	printf (" time : %ld clicks (%f seconds).\n",t,((double)t)/CLOCKS_PER_SEC);
   mysql_close(conn);
	return 0;
}
