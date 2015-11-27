#include<bits/stdc++.h>
using namespace std;
void print(vector<string> current) {
    for(int i = 0 ; i < current.size(); i++) {
	    cout << current[i] << endl;
    }
    cout << endl;
}
bool isvalid(vector<string> current,int x,int y) {
    int n = current.size();
    for(int i = 0 ; i < n; i++) {
        for (int j = 0 ; j < n ; j++) {
            if(current[i][j] == 'Q') {
                if(x == i or y == j or (abs(x-i) == abs(y-j))) return false;
            }
        }
    }
    return true;
}
void nqueens(int A,int row,vector<vector<string> > &solution, vector<string> &current) {
    if(row >= A) {
        solution.push_back(current);
        return;
    }
    print(current);
    for(int i = 0 ; i < A ; i++) {
        if(isvalid(current,row,i)) {
            current[row][i] = 'Q';
            nqueens(A,row+1,solution,current);
            current[row][i] = '.';
        }
    }
}
int main() {
    // Do not write main() function.
    // Do not read input, instead use the arguments to the function.
    // Do not print the output, instead return values as specified
    // Still have a doubt. Checkout www.interviewbit.com/pages/sample_codes/ for more details
    int A = 4;
    vector<vector<string> > solution;
    string str(A,'.');
    vector<string> current(A,str);
    nqueens(A,0,solution,current);
    //cout << "hey";
    cout << solution.size() << endl;
}
