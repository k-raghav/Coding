#include<bits/stdc++.h>
using namespace std;

void helper(const vector<int> &A, int start, vector<bool> &inc, int k ) {
	if(start == A.size()) { // base case
		if(k == 0) {
			for(int i = 0 ; i < A.size() ; i++ ) {
				if(inc[i])
					cout << A[i] << " ";
			}
			cout << endl;
		}
		return;
	}
	if(k < 0) return;
	inc[start] = false;
	helper(A,start+1,inc,k);
	inc[start] = true;
	helper(A,start+1,inc,k-1);
}

void printksub(const vector<int> &A, int k) {
	int n = A.size();
	vector<bool> inc(n,false);
	helper(A,0,inc,k);
}

int main() {
	int arr[] = {1,2,3,4,5,6,7,8};
	vector<int> A(arr, arr+(sizeof(arr)/sizeof(arr[0])));
	printksub(A,3);
}
