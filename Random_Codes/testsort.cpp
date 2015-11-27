#include<bits/stdc++.h>
using namespace std;
void printvect(const vector<int> &A) {
	for(int i = 0 ; i < A.size() ; i++ ) 
		printf("%d%c",A[i],(i==A.size()-1)?'\n':' ');
}
int main() {
	int n;
	vector<int> A(10,0);
	for(int i = 0 ; i < 10 ; i++) {
		//A[i] = rand() % 10;
		A[i] = 10-i;
	}
	printvect(A);
	sort(A.begin()+2,A.end());
	printvect(A);
	cout << *(A.begin()+1) << endl;
	cout << lower_bound(A.begin(),A.end(),21) - A.begin() << endl;
	cout << upper_bound(A.begin(),A.end(),-1) - A.begin() << endl;


}
