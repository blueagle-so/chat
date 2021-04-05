// C program for reading
// struct from a file
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// struct person with 3 fields


#include <stdio.h>
#include <stdlib.h>
//#include <mysql.h>
#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <stack>
//mysqld -u root &
//mysql  -u root -ppassword -P 33060
//g++ 1.c -lmysqlcppconn8
//using namespace std;
//#include <mysqlx/xdevapi.h>
//using namespace mysqlx;
#include <chrono>











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

std::stack<std::pair<int,int>> s2,s;
int l,r,i,j,K;
Q1:;s.push(std::make_pair(0,n));
Q1a:;if(!s.empty()){l=s.top().first;r=s.top().second;s.pop();}
  Q2:;i=l;j=r;K=arr[(j-i)/2+i].id;
    Q3:;if(arr[i].id-K<0){i++;goto Q3;}
    Q4:;if(arr[j].id-K>0){j--;goto Q4;}
    Q5:;
    Q6:;if(i-j<=0){std::swap(arr[i],arr[j]);i++;j--;}
    Q6a:;if(i<=j)goto Q3;
    Q7:;if(r>i){s.push(std::make_pair(i,r));}
    Q7a:;if(j>l){s.push(std::make_pair(l,j));}
Q8:;if(!s.empty()) goto Q1a;

























/*
  int i, j;
      for (i = 1; i < n; i++)
          {
               key = arr[i];
                  j = i - 1;

                     * Move elements of arr[0..i-1], that are
                      *    greater than key, to one position ahead
                      *       of their current position 
                      while (j >= 0 && arr[j].id > key.id)
                            {
                                  arr[j + 1] = arr[j];
                                      j = j - 1;
                                          }
                          arr[j + 1] = key;
                              }

*/

        t = clock() - t;

	printf (" time : %ld clicks (%f seconds).\n",t,((double)t)/CLOCKS_PER_SEC);

	return 0;
}
