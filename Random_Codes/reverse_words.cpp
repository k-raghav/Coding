#include<iostream>
#include<string>
using namespace std;
void reverse(string &str, int i , int j) {
    while(i < j) {
        swap(str[i],str[j]);
        i++;
        j--;
    }
}
int main ()
{
  string str = "i like this program very much";
  int n = str.size();
  cout << str << endl;
  int start=0;
  for(int i = 0 ; i <= n ; i++) {
      if(str[i] == ' ' or i == n) {
          reverse(str,start,i-1);
          start = i+1;
      }
  }
  reverse(str,0,n-1);
  cout << str << endl;
}