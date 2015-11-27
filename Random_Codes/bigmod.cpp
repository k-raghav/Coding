#include<bits/stdc++.h>
#include<string>
using namespace std;
int num(string &s, int A) {
    int n = s.size();
    int res=0;
    while(s.size() > 10) {
        long long int tmp = stoll(s.substr(0,10));
        n = s.size();
	cout << s << endl;
        s = s.substr(10,n-10);
	cout << tmp << endl;
	cout << s << endl;
        res = tmp % A;
	cout << res << endl;
        s = to_string(res) + s;
	cout << s << endl;
    }
    long long int ll = stoll(s);
    if(ll % A == 0) return 0;   
    return (int) ll % A;
}
int main() {
    string s = "10000000000011111";
    cout << num(s,6) << endl;
}
