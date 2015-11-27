#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
int main ()
{
   unordered_map<int,int> A;
   for(int i = 0 ; i < 5 ; i++) {
   	A.insert(make_pair(i,i*5));
   }
   cout << A[3] << endl;
   //cout << A[6] << endl;
   if(A.find(6) == A.end()) {
	   cout << "NOT FOund" << endl;
   }
}
