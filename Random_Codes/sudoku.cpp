#include<bits/stdc++.h>
using namespace std;
int check_rows_columns(vector<vector<char> > &A) {
    for(int i = 0 ; i < A.size() ; i++) {
        vector<int> count_r(10,0);
        vector<int> count_c(10,0);
        for(int j = 0 ; j < A[0].size() ; j++) {
            if(A[i][j] != '.') {
                int indr = A[i][j]-'0';
                count_r[indr]++;
                if(count_r[indr] > 1) return 0;
            }
            if(A[j][i] != '.') {
                int indc = A[j][i]-'0';
                count_c[indc]++;
                if(count_c[indc]>1) return 0;
            }
        }
    }
    return 1;
}
int check_boxes(vector<vector<char> > &A) {
    for(int r = 0 ; r < 9 ; r+=3) {
        for(int c = 0 ; c < 9 ; c+=3) {
            vector<int> count(10,0);
            for(int i = 0 ; i < 3 ; i++) {
                for(int j = 0 ; j < 3 ; j++) {
                    int row = r + i;
                    int col = c + j;
                    if(A[row][col] != '.') {
                        int indr = A[row][col]-'0';
                        count[indr]++;
                        if(count[indr] > 1) return 0;
                    }
                }
            }
        }
    }
    return 1;
}
bool isvalid(vector<vector<char> > &A) {
    return check_rows_columns(A) * check_boxes(A);
}
void print_sudoku(vector<vector<char> > &A) {
    for(int i = 0 ; i < 9 ; i++) {
	for(int j = 0 ; j < 9 ; j++ ) {
		cout << A[i][j];
	}
	cout << endl;
    }
}
void helper(vector<vector<char> > &A, vector<vector<char> > &solution) {
    bool flag=false;
    print_sudoku(A);
    cout << endl;
    for(int r = 0 ; r < 9 ; r++) {
        for(int c = 0 ; c < 9 ; c++) {
            if(A[r][c]  == '.') {
                for(int i = 1; i <= 9 ; i++) {
                    A[r][c] = i+'0';
                    if(isvalid(A))
                        helper(A,solution);
                    A[r][c] = '.';
                }
                flag = true;
            }
        }
    }
    if(flag == false and isvalid(A)) {
        cout << "here" << endl;
        for(int r = 0 ; r < 9 ; r++) 
            for(int c = 0 ; c < 9 ; c++) 
                solution[r][c] = A[r][c];
    }
}
void solveSudoku(vector<vector<char> > &A) {
    vector<vector<char> > solution(A.begin(),A.end());
    helper(A,solution);
    for(int r = 0 ; r < 9 ; r++) 
        for(int c = 0 ; c < 9 ; c++) 
            A[r][c] = solution[r][c];
    return;
}
int main() {
    vector<vector<char> > A;
    string str = "53..7....";
    string str1 = "6..195...";
    string str2 = ".98....6.";
    string str3 = "8...6...3";
    string str4 = "4..8.3..1";
    string str5 = "7...2...6";
    string str6 = ".6....28.";
    string str7 = "...419..5";
    string str8 = "....8..79";
    vector<char> charvect(str.begin(), str.end()); 
    vector<char> charvect1(str1.begin(), str1.end()); 
    vector<char> charvect2(str2.begin(), str2.end()); 
    vector<char> charvect3(str3.begin(), str3.end()); 
    vector<char> charvect4(str4.begin(), str4.end()); 
    vector<char> charvect5(str5.begin(), str5.end()); 
    vector<char> charvect6(str6.begin(), str6.end()); 
    vector<char> charvect7(str7.begin(), str7.end()); 
    vector<char> charvect8(str8.begin(), str8.end()); 
    A.push_back(charvect);
    A.push_back(charvect1);
    A.push_back(charvect2);
    A.push_back(charvect3);
    A.push_back(charvect4);
    A.push_back(charvect5);
    A.push_back(charvect6);
    A.push_back(charvect7);
    A.push_back(charvect8);
    
    print_sudoku(A); 
    cout << endl;
    solveSudoku(A);
    print_sudoku(A); 
}
