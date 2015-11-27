#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
class heap {
	int arr[MAXN];
	int size = 0;
public:
	heap() {
		size=0;
	}
	int getSize() { return size; }
	int top() { return (size==0)?-1:arr[1]; }
	int push(int element) { //put element at end of the list and bubble up.
		arr[++size] = element;
		int curr = size;
		int parent = curr / 2; 
		while(curr > 1)  {
			if(arr[parent] > arr[curr]) 
				swap(arr[parent],arr[curr]);
			else 
				break;
			curr = parent;
			parent = curr / 2;
		}	
	}
	void pop() { //replace top element with last element and bubble down
		if(size==0) return; 
		arr[1] = arr[size];
		int curr = 1;
		size--;
		while(1) {
			int lchild = curr*2;
			int rchild = curr*2+1;
			if(rchild <= size) {
				if(min(arr[lchild],arr[rchild]) < arr[curr]) {
					if(arr[lchild] < arr[rchild]) {
						swap(arr[lchild],arr[curr]);
						curr = lchild;
					}
					else {
						swap(arr[rchild],arr[curr]);
						curr = rchild;
					}
					continue;
				}
			}
			else if(lchild <= size) {
				if(arr[lchild] < arr[curr]) {
					swap(arr[lchild],arr[curr]);
					curr = lchild;
					continue;
				}
			}
			break;
		}
	}
};
heap hp;
int main() {
	int n,num;
	cin >> n;
	for(int i = 0; i < n; i++) {
		cin >> num;
		hp.push(num);
	}

	while(hp.getSize() > 0) {
		cout << hp.top() << endl;
		hp.pop();
	}

	return 0;
}
