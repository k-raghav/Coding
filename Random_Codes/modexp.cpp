#include<iostream>
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

int main() {
	int base = 71045970;
	int exp = 41535484;
	int mod = 64735492;
	cout << exp_pow(base,exp,mod) << endl;
}
