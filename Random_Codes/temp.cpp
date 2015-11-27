#include<iostream>
using namespace std;
int main() {
	string a  = "303";
	string b  = "330";
	string c  = "304";
	cout << a << " " << b << " " << a.compare(b) << endl;
	cout << b << " " << c << " " << b.compare(c) << endl;
	cout << a << " " << c << " " << a.compare(c) << endl;

}
