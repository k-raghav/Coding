#include<iostream>
#include<bits/stdc++.h>
using namespace std;

void next_permutation(vector<int> &A) {
	int pivot = -1;
	int n = A.size();
	for(int i = n-2 ; i >= 0 ; i-- )  {
		if(A[i] < A[i+1]) {
			pivot = i;
			break;
		}
	}
	if(pivot == -1) {
		sort(A.begin(),A.end());
		return;
	}
	int pos = -1;
	for(int i = A.size() ; i >= pivot ; i-- ) {
		if(A[i] > A[pivot]) {
			pos = i;
			break;
		}
	}
	swap(A[pivot],A[pos]);
	if(pivot < A.size()-1)
		sort(A.begin()+pivot+1,A.end());
}

int main() {
	bool found = false;
	//bool available = true;
	//static const int arr[] = { 1,2,4,3,5};
	//static const int arr[] = { 1,2,4,3,5};
	static const int arr[] = { 1,4,3,2,5};
	vector<int> A(arr, arr + sizeof(arr) / sizeof(arr[0]) );
	for(int i = 0 ; i < A.size() ; i++ ) cout << A[i] << " "; 
	cout << endl;
	next_permutation(A);
	for(int i = 0 ; i < A.size() ; i++ ) cout << A[i] << " "; 
	cout << endl;
}
