#include<bits/stdc++.h>
using namespace std;

void helper(int n, int k , string &curr) {
	if(n == 0) {
		cout << curr << endl;
		return;
	}
	for(int i = 0 ; i < k ; i++ ) { 
		char c = i + '0';
		curr.push_back(c);
		helper(n-1,k,curr);
		curr.pop_back();
	}
}

void nbinstrings(int n,int k) {
	string curr="";
	helper(n,k,curr);
}

int main() {
	nbinstrings(5,3);
}
