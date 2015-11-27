#include<bits/stdc++.h>
using namespace std;
void printvect(const vector<int> &A) {
	for(int i = 0 ; i < A.size() ; i++ ) 
		printf("%d%c",A[i],(i==A.size()-1)?'\n':' ');
}
int partition(vector<int> &A, int start, int end)  {
	int low = start; 
	int high = end-1;
	while(low <= high) {
		if(A[low] <= A[end]) low++;
		else {
			swap(A[low],A[high]);
			high--;
		}
	}
	swap(A[end],A[low]);
	return low;
}
void quick_sort(vector<int> &A, int start, int end) {
	if(start >= end) return;
	int pivot = start + (rand() % (end-start));
	swap(A[pivot],A[end]);
	pivot = partition(A,start,end);
	quick_sort(A,start,pivot-1);
	quick_sort(A,pivot+1,end);
}
int main() {
	int n;
	vector<int> A(10,0);
	for(int i = 0 ; i < 10 ; i++) {
		A[i] = rand() % 10;
	}
	n = A.size();
	printvect(A);
	quick_sort(A,0,n-1);
	printvect(A);


}
