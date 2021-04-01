// C++ program for Merge Sort
#include <iostream>
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


using namespace std;

void merge(int arr[], int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;

	// Create temp arrays
	int L[n1], R[n2];

	// Copy data to temp arrays L[] and R[]
	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	// Merge the temp arrays back into arr[l..r]

	// Initial index of first subarray
	int i = 1;

	// Initial index of second subarray
	int j = 1;

	// Initial index of merged subarray
	int k = l;
/*
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of
	// L[], if there are any
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of
	// R[], if there are any
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
*/
M1:;//int i=1,j=1;k=1;
M2:;if(L[i]>=R[j])goto M5;
M3:;arr[k]=R[i];k++;i++;if(i<n1)goto M2;
M4:;for(int l=j;l<=n2;l++){arr[k]=R[l];k++;}goto END;
M5:;arr[k]=R[j];k++;i++;if(j<n2)goto M2;
M6:;for(int l=i;l<=n1;l++){arr[k]=L[l];k++;}
END:;


}

// l is for left index and r is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(int arr[],int l,int r){
	if(l>=r){
		return;//returns recursively
	}
	int m =l+ (r-l)/2;
	mergeSort(arr,l,m);
	mergeSort(arr,m+1,r);
	merge(arr,l,m,r);
}













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
	struct person input, key;//arr[4000], key;
int k=0, arr[4000];
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

  arr[k]=input.id;

  k++;
  }
	// close file
       int n = sizeof(arr) / sizeof(arr[0]);

/*
int arr1[n/2];
for(int i=0;i<n/2;i++)
	arr1[i]=arr[i];
int arr2[n/2];
for (int i = n/2;i<4000;i++)
	arr2[i-n/2]=arr[i];
*/







mergeSort(arr, 0, n);











/*

M1:;int i=1,j=1;k=1;
M2:;if(arr1[i]>=arr2[j])goto M5;
M3:;arr[k]=arr1[i];k++;i++;if(i<=n/2)goto M2;
M4:;for(int l=j;l<=n/2;l++){arr[k]=arr2[l];k++;}goto END;
M5:;arr[k]=arr2[j];k++;i++;if(j<=n/2)goto M2;
M6:;for(int l=i;l<=n/2;l++){arr[k]=arr1[l];k++;}
END:;


*/











        t = clock() - t;

   printf (" time : %ld clicks (%f seconds).\n",t,((double)t)/CLOCKS_PER_SEC);

        return 0;
}
