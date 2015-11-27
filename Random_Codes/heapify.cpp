#include<bits/stdc++.h>
using namespace std;
#define MAX 200000
#define INF 1000000
int main() {
	vector<int> arr(MAX);
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> arr[i];
	bool extra = false;
	if(n&1 == 0) {
		arr[++n] = INF;
		extra = true;
	}
	// Heapify 
	for(int i = (n-1)/2; i >= 1; i--)  {
		int curr = i; 
		int rchild = 2*i+1;
		int lchild = 2*i;
		while(arr[curr] > min(arr[rchild],arr[lchild])) { // percolate down
			if(arr[lchild] < arr[rchild]) {
				swap(arr[curr],arr[lchild]);
				curr = lchild;
			}
			else {
				swap(arr[curr],arr[rchild]);
				curr = rchild;
			}
			if(curr > (n-1)/2) break;
		}
	}
	if(extra) n--;
	for(int i = 1 ; i <= n ; i++ ) cout << i << " "; 
	cout << endl;
	return 0;
}
