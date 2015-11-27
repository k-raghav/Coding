#include<bits/stdc++.h>
using namespace std;

int main() {
    int dividend = INT_MIN;
    int divisor = 2;
    if(divisor == 0) return INT_MAX;
    if(divisor == 1) return dividend;
    int sign=1;
    if((dividend ^ divisor) & (1 << 31)) sign = -1;
    long long int tmp = abs(divisor);
    long long divid = (long long)dividend;
    divid = abs(divid);
    long long count = 0;
    while(count < divid) {
        tmp += (long long) abs(divisor);
        count++;
	cout << tmp << " " << divid << " " << count << endl;
    }
    cout << sign*count << endl;
}
