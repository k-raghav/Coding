#include<bits/stdc++.h>
using namespace std;
class MinStack() {
	public:
	stack<int> mintillnow;
	stack<int> mystack;
		
}
MinStack::MinStack() {
}
void MinStack::push(int x) {
    if(mystack.empty())
        mintillnow.push(x);
    else {
        int tmp = min(mintillnow.top(),x);
        mintillnow.push(tmp);
    }
    mystack.push(x);
}

void MinStack::pop() {
    if(mystack.empty()) return;
    mystack.pop();
    mintillnow.pop();
}

int MinStack::top() {
    if(mystack.empty()) return -1;
    return mystack.top();
}

int MinStack::getMin() {
    if(mintillnow.empty()) return -1;
    return mintillnow.top();
}
