#include<bits/stdc++.h>
using namespace std;

int main() {
    int mod = 1000000009;
    static const int arr[] = {1,2,3,4,5,6,7};
    vector<int> A(arr, arr + sizeof(arr) / sizeof(arr[0]) );
    long long count = 0;
    int n = A.size();
    vector<long long int> counts_1(33,0);
    vector<int> mask(32,0);
    for(int i = 0 ;i < 31 ; i++) {
        mask[i] = 1 << i;
    }
    for(int j = 0 ; j < n ; j++) {
        for(int i = 0 ; i < 31 ; i++) {
            if(A[j] & mask[i]) counts_1[i]++;
        }
    }
    for(int i = 0 ; i < 31 ; i++) {
        count = (count + (counts_1[i] * (n-counts_1[i]))%mod)%mod;
    }
    count = (count * 2LL) % mod;
    cout << count << endl;	
}
