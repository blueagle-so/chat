#include <iostream>
using namespace std;
#include <string>
//mysqld -u root &
//mysql  -u root -ppassword -P 33060
//g++ 1.c -lmysqlcppconn8
#include <mysqlx/xdevapi.h>
using namespace mysqlx;
#include <chrono>





int main(){
int n = 110031;
//int arr[n];
//for (int f=0;f<n;f++)
//arr[f]=rand() % 100;
         std::cout << "Creating session on " << "mysql"
                  << " ..." << std::endl;
                Session mySession("localhost",33060,"root","blueeagle");
                       mySession.sql("CREATE DATABASE IF NOT EXISTS test").execute();
                              mySession.sql("CREATE TABLE IF NOT EXISTS test.my_table (id MEDIUMINT NOT NULL AUTO_INCREMENT, name VARCHAR(20), birthday DATE, age INT, PRIMARY KEY (id))").execute();
                                     Schema myDb = mySession.getSchema("test");

                                             // Accessing an existing table
                                                       Table myTable = myDb.getTable("my_table");

RowResult myResult= myTable.select("age").execute();
int arr[110031];
for(int y = 0;y<110031;y++)
  arr[y] = {myResult.fetchOne().get(0)};


auto start = std::chrono::system_clock::now();
D1:;for(int s = n/2;s>0;s/=2){
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
