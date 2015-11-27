#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<vector>

using namespace std;

void radix(int array[]) {
  int digit=1, times=3;
  vector<int> bucket[10];
  while(times) {
    for(int i=0; i<10; i++) {
      int b = (array[i]%(digit*10) - array[i]%digit)/digit;
      bucket[b].push_back(array[i]);
    }
    int k=0;
    for(int i=0; i<10; i++) {
      for(int j=0; j<bucket[i].size(); j++)
	array[k++] = bucket[i][j];
    }
    for(int i=0; i<10; i++) {
      cout<<array[i]<<" ";
      bucket[i].clear();
    }
    cout<<endl;
    digit *= 10;
    times--;
  }
}

int main() {
  int a[] = {849,770,67,347,201,618,66,495,13,45};
  radix(a);
  return 0;
}
