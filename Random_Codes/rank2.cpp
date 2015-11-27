#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int exp_pow(int base, int exp,int mod) {
	long long int c = 1;
	long long int b = (long long) base;
	while(exp > 0 ) { // Modular Exponentiation
		if(exp == 1) 
			return (c * b)% mod;
		if(exp % 2 == 0) {
			b = (b * b) % mod;
			exp /= 2;
		}
		else {
			c = (c * b) % mod;
			exp--;
		}
	}
	return c;
}
int no_perm(vector<int> fact, vector<int> count,int mod) { // Number of permutations for each character less than this
    int n = 0;
    for(int i = 0 ; i < 256 ; i++) 
        if(count[i]) n+=count[i];
    long long int result = (long long)fact[n];
    for(int i = 0 ; i < 256 ; i++) {
        if(count[i] > 1) {
	    int mul = exp_pow(fact[count[i]],mod-2,mod);
	    //cout << i << " " << count[i] << " " << fact[count[i]] << " MUL " << mul << endl;
            result = (result * (long long)mul) % mod;
	}
    }
    return (int) result%mod;
   //  (1/A) % MOD = A ^ (MOD - 2) % MOD

}
int init(string A, char c, int pos, vector<int> fact,int mod) {
    vector<int> count(256);
    fill(count.begin(),count.end(),0);
    for(int i = pos; i < A.size() ; i++) {
        count[A[i]]++;
    }
    int temp = 0;
    for(int i = 0 ; i < c ; i++) {
	if(!count[i]) continue;
        count[i]--;
        temp = (temp + no_perm(fact,count,mod)) % mod;
        count[i]++;
	cout << "Char and perms " << i << " " << count[i] << " " <<  temp << endl;
    } 
    cout << "Char and perms " << c << " " << count[c] << endl;
    return temp;
}
void fill_fact(int A, vector<int> &fact, int mod) {
    fact.push_back(1);
    for(int i = 1 ; i < A ; i++) {
        long long int tmp = (i * fact[i-1]) % mod;
        fact.push_back(tmp%mod);
    }
}
int find_diff(string A,int pos) {
    vector<int> count(256);
    fill(count.begin(),count.end(),0);
    for(int i = pos; i < A.size() ; i++) {
        count[A[i]]++;
    }
    int tmp=0;
    for(int i = 0 ;i < 256 ; i++) {
        if(i == A[pos]) break;
        if(count[i]) tmp++;
    }
    return tmp;
}
bool all_same(string A, int pos) {
    for(int i = pos+1 ;i < A.size() ; i++) {
        if(A[i]!=A[i-1]) return false;
    }
    return true;
}
int main() {
    string A = "sadasdsasassasas";
    vector<int> fact;
    int mod = 1000003;
    int n = A.size();
    fill_fact(n,fact,mod);
    int result = 1; 
    for(int i = 0 ; i < n ; i++) {
        int diff = find_diff(A,i);
        //if(all_same(A,i)) break;
        result = (result + ((diff*init(A,A[i],i,fact,mod))% mod)) % mod;
        cout << diff << " " << result << endl;
    }
    cout << result << endl;
}

