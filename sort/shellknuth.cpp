#include <iostream>
using namespace std;
#include <string>
//mysqld -u root &
//mysql  -u root -ppassword -P 33060
//gii++ 1.c -lmysqlcppconn8
//#include <mysqlx/xdevapi.h>
//using namespace mysqlx;
#include <chrono>



struct person
{
        int id;
        char fname[20];
        char lname[20];
};

int main(){
//int n = 110031;


        FILE *infile;
        struct person input; 
int arr[40000], key;
int k=0;



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










       int n = sizeof(arr) / sizeof(arr[0]);



auto start = std::chrono::system_clock::now();
D1:;for(int s = n/2;s>0;s/=2+1){
D2:;for(int j=s+1;j<n;j++){
D3:;int i=j-s;int K=arr[j];
D4:;if ((K>arr[i])) goto D6;
D5:;arr[i+s]=arr[i];i=i-s;if (i>=0) goto D4;
D6:;arr[i+s]=K;
}}
auto end = std::chrono::system_clock::now();
std::chrono::duration<double> elapsed = end - start;
std::cout << "Elapsed time: " << elapsed.count() << "s"<<endl;


//for (int v=0;v<n;v++)
//cout  <<" " <<arr[v];
//cout<<endl;

return 0;
}



//анализ кнут 5.2.1
