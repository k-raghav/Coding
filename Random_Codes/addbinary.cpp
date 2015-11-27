#include<bits/stdc++.h>
using namespace std;

int main() {
    string A = "1000011011000000111100110";
    string B = "1010110111001101101000";
    int diff = A.size() - B.size();
    for(int i = 0 ; i < diff ; i++)
        B = '0' + B;
    int carry = 0;
    string result = "";
    for(int i = A.size()-1 ; i >= 0 ;i--) {
        int sum = (A[i]-'0') + (B[i]-'0') + carry;
	carry = 0;
        if(sum == 0) 
            result = '0' + result;
        else if(sum == 1) 
            result = '1' + result;
        else if(sum == 2) {
            result = '0' + result;
            carry = 1;
        }
        else {
            result = '1' + result;
            carry = 1;
        }
    }
    if(carry) result = '1' + result;
    cout << A << endl;
    cout << B << endl;
    cout << result << endl;
    string actual = "1001110001111010101001110";
    cout << actual << endl;
}
