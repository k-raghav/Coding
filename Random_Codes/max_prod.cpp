#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main() {
    static const int arr[] = {-3,-2,1,3 , 2 , 5, 3, -3, 5};
    vector<int> A(arr, arr + sizeof(arr) / sizeof(arr[0]) );
    for (int i = 0 ; i < A.size() ; i++ ) {
    	cout << A[i] << " ";
    }
    cout << endl;
    int n = A.size();
    int ans = A[0];
    int max_now = A[0];
    int min_now = A[0];
    for(int i = 1 ; i < n ;i++ ) {
    	int tmp = max_now;
	max_now = max(max(max_now*A[i],A[i]),min_now*A[i]);
	min_now = min(min(min_now*A[i],A[i]),tmp*A[i]);
	ans = max(ans,max_now);
    }
    cout << ans << endl;
}
