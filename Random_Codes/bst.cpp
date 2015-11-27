#include<bits/stdc++.h>
using namespace std;
struct TreeNode {
	int data;
	TreeNode* left;
	TreeNode* right;
	/*TreeNode(int val) {
		data=val;
		left=NULL;
		right=NULL;
	}*/
	TreeNode(int val): data(val),left(NULL),right(NULL) {}
};

TreeNode* Insert(TreeNode* root,int data){
	if(root==NULL) {
		TreeNode* newNode = new TreeNode(data);
		return newNode;
	}
	if(data <= root -> data) root -> left = Insert(root->left,data);
	else root -> right = Insert(root->right,data);
	return root;
}

bool Search(TreeNode* root, int data)  {
	if(root == NULL) return false;
	if(root->data == data) return true;
	return (data<root->data)?Search(root->left,data):Search(root->right,data);
}

void PrintBST(TreeNode* root) {
	if(!root) return;
	PrintBST(root->left);
	cout << root->data << " ";
	PrintBST(root->right);
}
	
int main() {
	TreeNode* root = NULL; // Only storing the address of the root 
	root = Insert(root,15);
	root = Insert(root,10);
	root = Insert(root,20);
	root = Insert(root,25);
	root = Insert(root,8);
	root = Insert(root,12);
	cout << Search(root,20) << endl;
	cout << Search(root,8) << endl;
	cout << Search(root,17) << endl;
	cout << "Tree Inorder" << endl;
	PrintBST(root);
	cout << endl;
}

