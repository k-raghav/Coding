#include<bits/stdc++.h>
using namespace std;
int check_rows_columns(const vector<string> &A) {
    cout << "Finished here " << endl;
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
    cout << "Finished here " << endl;
    return 1;
}
int check_boxes(const vector<string> &A) {
    cout << "Finished here " << endl;
    for(int r = 0 ; r < 9 ; r+=3) {
    	cout << "Finished here r " << r << endl;
        for(int c = 0 ; c < 9 ; c+=3) {
    	    cout << "Finished here c " << c << endl;
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
int main() {
    vector<string> A;
    A.push_back("....5..1.");
    A.push_back(".4.3.....");
    A.push_back(".....3..1");
    A.push_back("8......2.");
    A.push_back("..2.7....");
    A.push_back(".15......");
    A.push_back(".....2...");
    A.push_back(".2.9.....");
    A.push_back("..4......");
    cout << check_rows_columns(A) * check_boxes(A) << endl;
}
