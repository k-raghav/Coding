#include<bits/stdc++.h>
using namespace std;

void compute_lps(string s, vector<int> &lps) {
	int n = s.size();
	lps[0] = -1;
	for(int i = 1 ; i <= n ; i++) {
		int pos = lps[i-1];
		while(pos != -1 and s[pos] != s[i-1]) 
			pos = lps[pos];
		lps[i] = pos + 1;
	}
}

void fill_matches(string S,string K,vector<int> &T, vector<int> &matches) {
	int sp = 0;
	int kp = 0;
	while(sp < S.size())
	{
		while(kp != -1 && (kp == K.size() || K[kp] != S[sp])) kp = T[kp];
		kp++;
		sp++;
		if(kp == K.size()) matches.push_back(sp - K.size());
	}
}

int main() {
	string s1 = "ABABABCAABAABCABABA";
	string s2 = "ABCA";
	int n = s2.size();
	vector<int> lps(n+1,-1);
	compute_lps(s2,lps);
	cout << s1 << endl;
	cout << s2 << endl;
	for(int i = 1 ; i <= s2.size() ; i++ ) cout << lps[i] ;
	cout << endl;
	vector<int> ans;
	fill_matches(s1,s2,lps,ans);
	for(int i = 0 ; i < ans.size() ; i++ ) cout << ans[i] << " ";
	cout << endl;
}
