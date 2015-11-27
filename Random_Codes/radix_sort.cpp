#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int num_digits(int a) {
	int count = 0;
	while(a) {
		a /= 10;
		count++;
	}
	return count;
}

void count_sort_digit(vector<int> &temp,int pos) {

	int div = pow(10,pos);
	int n = temp.size();
	vector<int> copy(n);
	vector<int> count(10);
	fill(count.begin(),count.end(),0);
	for(int i = 0 ; i < n ; i++ ) {
		int dig = (temp[i]/div) %10;
		count[dig]++;
	}
	for(int i = 1 ; i < 10 ; i++ ) 
		count[i] += count[i-1];
	for(int i = n-1 ; i >= 0 ;  i-- ) {
		int dig = (temp[i]/div) %10;
		copy[count[dig]-1] = temp[i];
		count[dig]--;
	}
	for(int i = 0 ; i < n ; i++ ) {
		temp[i] = copy[i];
	}
}

void radix_sort(vector<int> &temp, int max_bits) {
	for(int i = 0 ; i < max_bits; i++) {
		count_sort_digit(temp,i);
	}
}

int main() {
    bool found = false;
    //bool available = true;
//    static const int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    static const int arr[] = {1,10,5};
    vector<int> A(arr, arr + sizeof(arr) / sizeof(arr[0]) );
    int max_bits = 0;
    for (int i = 0 ; i < A.size() ; i++ ) {
	    max_bits = max(max_bits,num_digits(A[i]));
    }
    vector<int> copy(A.begin(),A.end());
    for (int i = 0 ; i < copy.size() ; i++ ) {
    	cout << copy[i] << " ";
    }
    cout << endl;
    cout << max_bits << endl;
    radix_sort(copy,max_bits);
    cout << "Sorted " << endl;
    for (int i = 0 ; i < copy.size() ; i++ ) {
    	cout << copy[i] << " ";
    }
    cout << endl;
    cout << max_bits << endl;
}
