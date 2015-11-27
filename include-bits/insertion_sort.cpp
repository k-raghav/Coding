#include<bits/stdc++.h>
using namespace std;

int main() {
	int arr[] = {5,1,2,7,3,6};
	int s = sizeof(arr)/sizeof(arr[0]);
	vector<int> A(arr,arr+s);
	for(int i = 0 ; i < A.size() ;i++ ) {
		cout << A[i] << " ";
	}
	cout << endl;
	for(int i = 1 ; i < A.size() ;i++ ) {
		for(int j = i ; j >= 1 ; j-- ){
			if(A[j] < A[j-1]) swap(A[j-1],A[j]);
			else break;
		}
	}
	for(int i = 0 ; i < A.size() ;i++ ) {
		cout << A[i] << " ";
	}
	cout << endl;
}
