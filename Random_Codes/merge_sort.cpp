#include<bits/stdc++.h>
using namespace std;
void printvect(const vector<int> &A) {
	for(int i = 0 ; i < A.size() ; i++ ) 
		printf("%d%c",A[i],(i==A.size()-1)?'\n':' ');
}
void merge_sort(vector<int> &A, int start, int end) {
	if(start >= end) return;
	int mid = (start + end) / 2;
	merge_sort(A,start,mid);
	merge_sort(A,mid+1,end);
	vector<int> copy(end-start+1);
	int i = start; 
	int j = mid+1;
	int k = 0;
	while(i <= mid and j <= end)  {
		if(A[i] <= A[j]) copy[k++] = A[i++];
		else copy[k++] = A[j++];
	}
	while(i <= mid) 
		copy[k++] = A[i++];
	while(j <= end) 
		copy[k++] = A[j++];
	for(int i = start ; i <= end ; i++ ) {
		A[i] = copy[i-start];
	}
}
int main() {
	int n;
	vector<int> A(10,0);
	for(int i = 0 ; i < 10 ; i++) {
		A[i] = rand() % 10;
	}
	n = A.size();
	printvect(A);
	merge_sort(A,0,n-1);
	printvect(A);


}
