#include <iostream>
#include <chrono>
using namespace std;

int main(){
int n = 100000;
int arr[n];
for (int f=0;f<n;f++)
arr[f]=rand() % 100;
auto start = std::chrono::system_clock::now();
D1:;for(int s = n/2;s>0;s/=2){
D2:;for(int j=s;j<n;j++){
D3:;int i=j-s;int K=arr[j];
D4:;if ((K>arr[i])) goto D6;
D5:;arr[i+s] = arr[i];i=i-s;if (i>=0) goto D4;
D6:; arr[i+s]=K;
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
