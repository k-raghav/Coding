#include<bits/stdc++.h>
using namespace std;
struct Node{
	int data;
	struct Node* next;
	struct Node* prev;
};
struct Node* GetNewNode(int x) {
	Node* newNode = new Node;
	newNode->data = x;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}
struct Node* InsertAtHead(struct Node* head, int x) {
	Node* temp = GetNewNode(x);
	if(head == NULL) 
		return temp;
	temp -> next = head;
	head -> prev = temp;
	return temp;
}
struct Node* InsertAtTail(struct Node* head, int x) {
	Node* temp = GetNewNode(x);
	if(head == NULL) 
		return temp;
	Node* beg = head;
	while(head -> next != NULL) {
		head = head -> next;
	}
	head -> next = temp;
	temp -> prev = head;
	return beg;
}
void PrintList(struct Node* head) {
	while(head != NULL) {
		cout << head->data << " ";
		head = head -> next;
	}
	cout << endl;
}
void PrintListReverse(struct Node* head) {
	if(head == NULL) return;
	while(head -> next != NULL) 
		head = head -> next;

	while(head != NULL) {
		cout << head->data << " ";
		head = head -> prev;
	}
	cout << endl;
}
int main() {
	Node* dll = NULL;
	dll = InsertAtHead(dll,1);
	dll = InsertAtHead(dll,2);
	dll = InsertAtTail(dll,4);
	dll = InsertAtTail(dll,5);
	PrintList(dll);
	PrintListReverse(dll);
}
