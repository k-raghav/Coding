#include<bits/stdc++.h>
using namespace std;
bool comp(int a,int b) {
	return (a < b);
}
int main() {
	int t;
	cin >> t;
	for(int iter = 1 ; iter <= t ; iter++ ) {
		int n; 
		cin >> n;
		priority_queue<int, vector<int>, greater<int> > heap;
		int a;
		for(int i = 0 ; i < n ; i++) {
			cin >> a;
			if(heap.size() < 3) heap.push(a);
			else {
				if(a > heap.top()) {
					heap.pop();
					heap.push(a);
				}
			}
		}
		cout << "Case " << iter << ": ";
		int sum = 0;
		while(!heap.empty()){
			sum += heap.top();
			heap.pop();
		}
		cout << sum << endl;
	}
}
