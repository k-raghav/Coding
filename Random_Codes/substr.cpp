#include<bits/stdc++.h>
using namespace std;
int main() {
	string str="abcdef";
	string str1 = str.substr(1);
	string str2 = str1.substr(1);
	cout << str << " " << str1 << " " << str2 << endl;
	int start = 0;
	for(int i = start ; i < str.size() ; i++) {
		cout << str.substr(start,i-start+1) << endl;
	}
	int A = 5;
	string s(A,'.');
	cout << s << endl;
}
