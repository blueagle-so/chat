// C++ implementation of Shell Sort
 #include <iostream>
#include <math.h>
 using namespace std;

 /* function to sort arr using shellSort */
 int shellSort(int arr[], int n)
 {
  // Start with a big gap, then reduce the gap
  int s=0;
    for (int gap = n/2; gap > 0; gap /= 2)
    {
     // Do a gapped insertion sort for this gap size.
      // The first gap elements a[0..gap-1] are already in gapped order
      // keep adding one more element until the entire array is
       // gap sorted
     int k=0;
     printf("шаг(длинна группы) ls=%i \n",gap);
     int u=pow(2,(s+1))-1;
     printf("колл пар a =%i\n", u);
     for (int i = gap; i < n; i += 1)
    {
     // add a[i] to the elements that have been gap sorted
     // save a[i] in temp and make a hole at position i
     int temp = arr[i];

     // shift earlier gap-sorted elements up until the correct
     // location for a[i] is found
      int j;
      for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
      arr[j] = arr[j - gap];

     // put temp (the original a[i]) in its correct location
      k++;
      arr[j] = temp;
    }
     s++;
   printf("инверсии %i \n",k);
     }
       return 0;
                                                                                                      }

                                                                                                          void printArray(int arr[], int n)
    {
    for (int i=0; i<n; i++)
    cout << arr[i] << " ";
    printf("\n");
    }
   int main()
   {
   //int arr[] = {12, 34, 54, 2, 3, 8, 15, 4, 26, 31, 78, 52, 28, 45, 17, 10};
      int arr[] = {31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
     int n = sizeof(arr)/sizeof(arr[0]);
    cout << "Array before sorting: \n";
    printArray(arr, n);
     shellSort(arr, n);
    cout << "\nArray after sorting: \n";
    printArray(arr, n);
    return 0;
   }

