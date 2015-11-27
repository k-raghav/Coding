#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main() {
    static const int arr[] = { 2, 1, -9, -7, -8, 2, -8, 2, 3, -8 };
    vector<int> A(arr, arr + sizeof(arr) / sizeof(arr[0]) );
    for (int i = 0 ; i < A.size() ; i++ ) {
    	cout << A[i] << " ";
    }
    cout << endl;
    int B = -1;
    int n = A.size();
    sort(A.begin(),A.end());
    for (int i = 0 ; i < A.size() ; i++ ) {
    	cout << A[i] << " ";
    }
    cout << endl;
    int min_diff = INT_MAX;
    int min_diff_sum = 0;
    for(int i = 0 ; i < A.size() ; i++) {
        int ptr1 = i+1;
        int ptr2 = A.size()-1;
        int target = B - A[i];
        cout << i << " " << target << endl;
        while(ptr1 < ptr2) {
            int tmp = A[ptr1] + A[ptr2] + A[i];
            if(abs(B-tmp) < min_diff) {
                min_diff = abs(B-tmp);
                min_diff_sum = tmp;
            }
            if(A[ptr1] + A[ptr2] == target) return B;
            else if(A[ptr1] + A[ptr2] < target) ptr1++;
            else ptr2--;
        }
    }
    cout << min_diff_sum << endl;
}
