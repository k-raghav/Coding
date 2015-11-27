#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main() {
    vector<string> inter;
    // Intermediate product strings
    int max_string = 0;
    string A = "99";
    string B = "99";
    for(int i = B.size()-1 ; i >= 0 ; i--) {
        int extra_zeros=B.size()-i-1;
        string tmp(extra_zeros,'0');
        int carry = 0;
        int product = 1;
        for(int j = A.size()-1 ; j >= 0 ; j--) {
	    int val1 = B[i] -'0';
	    int val2 = A[j] -'0';
            product = (val1 * val2) + carry;
            carry = product / 10;
            int digit = product % 10;
            char dig_c = '0' + digit;
            tmp += dig_c;
//	    cout << product << " " << carry << " " << digit << " " << dig_c << endl;
        }
        if(carry) {
            char dig_c = carry + '0';
            tmp += dig_c;
        }
        inter.push_back(tmp);
        int len = tmp.size();
        max_string = max(max_string, len);
    }
    // Add intermediate product strings
    string result = "";
    int carry = 0; 
    int sum = 0;
    for (int i = 0 ; i < max_string; i++) {
        sum = 0;
        for (int j = 0 ; j < inter.size() ; j++) {
            if(i < inter[j].size()){
                sum += (inter[j][i] - '0');
            }
        }
        sum += carry;
        carry = sum / 10;
        int digit = sum % 10;
        char dig_c = digit + '0';
        result += dig_c;
    }
    if(carry) {
        char dig_c = carry + '0';
        result += dig_c;
    }
    reverse(result.begin(),result.end());
    cout << result << endl;
}
