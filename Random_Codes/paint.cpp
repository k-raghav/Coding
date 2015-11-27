#include<iostream>
#include<bits/stdc++.h>
using namespace std;
bool isPossible(vector<int> array,long long int unit,int no_painters,long long int curr_val) {
    long long int curr_sum = 0;
    long long int limit = curr_val;
    cout << "HERE " << curr_val << endl;
    for(int i = 0 ; i < array.size() ; i++) {
        long long int temp = (long long)array[i]*unit;
        if( temp > limit) {
           return false; 
        }
        else {
            if(curr_sum + temp > curr_val) {
                if(no_painters == 1) return false;
                no_painters--;
                curr_sum = temp;
            }
            else curr_sum += temp;
	    cout << temp << " " << limit  << " " << curr_sum  <<  " " << no_painters << endl;
        }
    }
    return true;
}
int main() {
    static const int arr[] = {1000000, 1000000 };
    vector<int> C(arr, arr + sizeof(arr) / sizeof(arr[0]) );
    for (int i = 0 ; i < C.size() ; i++ ) {
    	cout << C[i] << " ";
    }
    cout << endl;
    int A = 1, B = 1000000;

    int mod = 10000003;
    long long int max_time_possible = 0;
    for(int i = 0 ; i < C.size() ; i++) {
        max_time_possible+=C[i]*(long long)B;
    }
    cout << max_time_possible << endl;
    long long int start = 0, end = max_time_possible;
    long long int mid=0;
    long long int ans = LLONG_MAX; 
    while(start <= end) {
        mid = ((end-start) / 2) + start; 
        cout << start << " " << mid << " " << end << endl;
        if (isPossible(C,(long long) B, A, mid)) {
            ans = min(ans, mid);
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }
    cout << ans%mod << endl;
}
