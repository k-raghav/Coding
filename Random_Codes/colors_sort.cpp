#include<bits/stdc++.h>
using namespace std;

int main() {
    static const int arr[] ={ 0, 2, 0, 0, 1, 0, 1, 2, 0 };
    vector<int> A(arr, arr + sizeof(arr) / sizeof(arr[0]) );
    cout << A.size() << endl;
    int ptr1 = 0;
    int ptr2 = A.size() - 1;
    while(ptr1 < A.size() and A[ptr1] == 0) ptr1++;
    while(ptr2 >= 0 and A[ptr2] == 2) ptr2--;
    for (int i = ptr1 ; i <= ptr2 and ptr1 < ptr2; i++) {
        cout << ptr1 << " " << ptr2 << endl;
        if(A[i] == 0) {
            swap(A[i],A[ptr1]);
            ptr1++;
            i--;
        }
        else if(A[i] == 2) {
            swap(A[i],A[ptr2]);
            ptr2--;
            i--;
        }
	for(int j = 0 ; j < A.size() ; j++ ) 
		cout << A[j] << " ";
	cout << endl;
    }
   
}
