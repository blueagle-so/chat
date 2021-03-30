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
#include <mysqlx/xdevapi.h>
using namespace mysqlx;
#include <chrono>



void printArray(int *array, int n)
{
        for (int i = 0; i < n; ++i)
        std::cout << array[i] << " ";
}


int main(int argc, const char* argv[])
   {
       std::cout << "Creating session on " << "mysql"
       << " ..." << std::endl;
       Session mySession("localhost",33060,"root","blueeagle");
       mySession.sql("CREATE DATABASE IF NOT EXISTS test").execute();
       mySession.sql("CREATE TABLE IF NOT EXISTS test.my_table (id MEDIUMINT NOT NULL AUTO_INCREMENT, name VARCHAR(20), birthday DATE, age INT, PRIMARY KEY (id))").execute();
       Schema myDb = mySession.getSchema("test");

        // Accessing an existing table
       Table myTable = myDb.getTable("my_table");
//mySession.sql("create table test.bar(age int) select age from test.my_table ORDER BY test.my_table.age").execute();
//std::vector<int> myvector;90
       RowResult myResult=myTable.select("age").execute();
//for(int y = 0;y<110031;y++)
//myvector.push_back(myResult.fetchOne().get(0));



  int n = 110;
  int arr[n];
  for(int i=0;i<n;i++)
  arr[i]=rand()%100;//myResult.fetchOne().get(0);




      auto start = std::chrono::system_clock::now();



std::stack<std::pair<int,int>> s2,s;
int l,r,i,j,K;
Q1:;s.push(std::make_pair(0,n));
Q1a:;if(!s.empty()){l=s.top().first;r=s.top().second;s.pop();}
  Q2:;i=l;j=r;K=arr[(j-i)/2+i];
    Q3:;if(arr[i]-K<0){i++;goto Q3;}
    Q4:;if(arr[j]-K>0){j--;goto Q4;}
    Q5:;
    Q6:;if(i-j<=0){std::swap(arr[i],arr[j]);i++;j--;}
    Q6a:;if(i<=j)goto Q3;
    Q7:;if(r>i){s.push(std::make_pair(i,r));}
    Q7a:;if(j>l){s.push(std::make_pair(l,j));}
Q8:;if(!s.empty()) goto Q1a;
//Recurence relations
//T(n) = 2 T(n/2) + O(n)
//2k T(n/2k) + k n
//log2 n = k
//O(n log n)

//taiking   delta stack
//x stack - x0 stack  = delta sort

//proof
//начиная с шага Q1a стек содержит A[1]...A[м] элементов,
//продседура в процессе выполнения шагов Q1a - Q8
//отсортирует подмассив и вернется на шаг Q1a,
//где стек будет содержать первоначальные величины A[1]...A[m].


//lim      my qsort O(n log n)
//x->inf   -----------------   = 0;
//         mysql qsort O(n^1.5)



//myTable.select("age").orderBy("age").execute();
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  printArray(arr,n);
  std::cout << "Elapsed time: " << elapsed.count() << "s"<<std::endl;
  return 0;
}

