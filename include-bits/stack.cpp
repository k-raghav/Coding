#include<bits/stdc++.h>
using namespace std;

struct Student{
	int roll_no;
	string name;
	vector<string> books;
	Student(): roll_no(-1), name("") {}
	Student(int x,string y) : roll_no(x), name(y) {}
};

class Stack {
	int size;
	vector<Student*> array;
	public:
		Stack();
		void push(Student*);
		void pop();
		Student* top();
		bool isempty(); 
};

Stack::Stack() {
	size = 0;
	Student *newstudent = new Student(-1,"No Student");
	array.push_back(newstudent);
}

void Stack::push(Student *x) {
	if(size and size >= array.size()) {
		Student *newstudent = new Student(x->roll_no,x->name);
		array.push_back(newstudent);
		size++;
		return;
	}
	array[size]->roll_no = x->roll_no;
	array[size]->name = x->name;
	size++;
}
void Stack::pop() {
	if(size == 0){
		cout << "Stack empty" << endl;
		return;
	}
	size--;
}
Student* Stack::top() {
	if(size == 0){
		cout << "Stack empty" << endl;
		Student* mystudent = new Student();
		return mystudent;
	}
	return array[size-1];
}
bool Stack::isempty() {
	return (size == 0);
}

int main() {
	Stack mystack;
	Student *newstudent1 = new Student(1,"raghav"); 
	Student *newstudent2 = new Student(2,"vahgar"); 
	Student *newstudent3 = new Student(3,"zoro"); 
	mystack.push(newstudent1);
	Student *tmp = mystack.top();
	cout << tmp->roll_no << " " << tmp->name << endl;
	mystack.pop();
	tmp = mystack.top();
	cout << tmp->roll_no << " " << tmp->name << endl;
	mystack.push(newstudent1);
	tmp = mystack.top();
	cout << tmp->roll_no << " " << tmp->name << endl;
	mystack.push(newstudent2);
	tmp = mystack.top();
	cout << tmp->roll_no << " " << tmp->name << endl;
	mystack.push(newstudent3);
	tmp = mystack.top();
	cout << tmp->roll_no << " " << tmp->name << endl;
	//cout << mystack.top()->roll_no << " " << mystack.top()->name << endl;
	/*
	cout << mystack.top() << endl;
	mystack.push(1);
	mystack.push(2);
	mystack.push(3);
	cout << mystack.top() << endl;
	*/
}
