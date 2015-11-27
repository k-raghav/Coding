#include<bits/stdc++.h>
using namespace std;

int main() {
	static const int arr[] ={6,9};
	vector<int> A(arr, arr + sizeof(arr) / sizeof(arr[0]) );
	static const int arr1[] = {1,5,8};
	vector<int> B(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]) );
	int n = A.size();
	int m = B.size();
	A.resize(m+n);
	for(int i = 0 ; i < m+n ; i++) {
		cout << A[i] << " ";
	}
	cout << endl;
	int ptr1=n-1;
	int ptr2=m-1;
	int ptr=m+n-1;
	while(ptr1 >= 0 and ptr2 >= 0) {
		if(A[ptr1] > B[ptr2]) A[ptr--] = A[ptr1--];
		else A[ptr--] = B[ptr2--];
	}
	while(ptr2 >= 0) {
		A[ptr--] = B[ptr2--];
	}
	for(int i = 0 ; i < m+n ; i++) {
		cout << A[i] << " ";
	}
	cout << endl;
}
