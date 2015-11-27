#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int num_digits(int val){
	int count = 0; 
	while(val) {
		val /= 10;
		count++;
	}
	return count;
}

void count_sort_digit(vector<int> &temp,int pos)  {
	vector<int> bucket[10];
	for(int i = 0 ; i < temp.size() ; i++ ) {
		int x = temp[i]/pow(10,pos); 
		int bucket_id = x % 10;
		bucket[bucket_id].push_back(temp[i]);
	}
	int k = 0; 
	for(int i = 0 ; i < 10 ; i++ ) 
		for(int j = 0 ; j < bucket[i].size(); j++) 
			temp[k++] = bucket[i][j];
	
}

void radix_sort(vector<int> &temp, int max_bits) {
	for(int i = 0 ; i < max_bits; i++) {
		count_sort_digit(temp,i);
	}
}

int main() {
    bool found = false;
    //bool available = true;
    static const int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    //static const int arr[] = {1,10,5};
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
