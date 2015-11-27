#include<iostream>
#include<bits/stdc++.h>
using namespace std;
string build_last_string(vector<string> &A,int limit, int left, int right) {
    string result = "";
    int total_len = 0;
    for(int i = left ; i <= right ;i++) {
        result += A[i];
        if(i != right) result += " ";
        total_len += A[i].size() + 1;
    }
    total_len--;
    int diff = limit - total_len;
    for(int i = 0 ; i < diff ; i++) 
        result += " ";
    return result;
}
string build_string(vector<string> &A,int limit, int left,int right) {
    string result = "";
    int gaps = right-left;
    int extra_spaces = 0;
    int total_len = 0; 
    for(int i = left ; i <= right ; i++) {
        total_len += A[i].size() + 1;
    }
    total_len--;
    cout << limit << endl;
    extra_spaces = limit - total_len;
    if(gaps == 0) {
        result += A[left];
        for(int i = 0 ; i < extra_spaces; i++) {
            result += " ";
        }
        return result;
    }
    int eq = extra_spaces/gaps;
    cout << extra_spaces << " " << gaps << " " << eq << endl;
    vector<int> spaces(gaps,eq);
    cout << "Spaces " << endl;
    for(int i = 0; i < spaces.size() ; i++){
    	cout << spaces[i] << " ";
    }
    cout << endl;
    int rem = extra_spaces % gaps;
    for(int i = 0 ; i < spaces.size(); i++) {
        if(rem == 0) break;
        spaces[i]++;
        rem--;
    }
    int counter=0;
    cout << "Spaces " << endl;
    for(int i = 0; i < spaces.size() ; i++){
    	cout << spaces[i] << " ";
    }
    cout << endl;
    for(int i = left ; i <= right ; i++) {
        result += A[i];
        if(i != right) {
            int sz = spaces[counter++]+1;
	    cout << left << " " << right << " " << i << " " << sz << endl;
	    fflush(stdout);
            string tmp(sz,' ');
            result += tmp;
        }
    }
    return result;
}
//vector<string> Solution::fullJustify(vector<string> &A, int B) {
int main() {
    // Do not write main() function.
    // Do not read input, instead use the arguments to the function.
    // Do not print the output, instead return values as specified
    // Still have a doubt. Checkout www.interviewbit.com/pages/sample_codes/ for more details
//    string s[] = {"croozgmbvj", "ktr", "xcvcew", "uppfdpxa", "kjkrscvr", "uzbkzei", "bqo", "vhjimyfh", "vvlxnwmzr", "inaex", "wjphdy", "wbcoio", "uuwdy", "co", "dchkwzfz", "jsyirkvzhr", "potnkns", "wl", "dtfjy", "szh", "abuhkntr", "rntwaba", "tpg", "qb", "lhx", "rocahw", "ccwxjlrg", "oirdy", "wtcjhij", "mxnmhp", "jpqmxliqg", "mlvat", "tjn", "nont", "m", "m", "lxhlbb", "c", "xc", "ifwswsrg", "bjiaonhe", "mdtrfprhr", "focdohm"};
     string s[] = {"What" , "must" ,"be", "shall", "be."};
    vector<string> A; 
    for(int i = 0 ; i < 5 ; i++) {
	    A.push_back(s[i]);
    }
//    string tmp = "";
//    A.push_back(tmp);
/*    string tmp = "What";
    A.push_back(tmp);
    tmp = "must";
    A.push_back(tmp);
    tmp = "be";
    A.push_back(tmp);
    tmp = "shall";
    A.push_back(tmp);
    tmp = "be."; 
    A.push_back(tmp); */
    vector<string> result;
    int B = 12;
    if(A.size() == 0 or (A.size() == 1 and A[0] == "")) {
        result.push_back("");
	cout << "here" << endl; 
	exit(0);
    }
    int pos = 0;
    int currlen = 0;
    int leftpos = 0 ; 
    int rightpos = 0;
    cout << "A is of size " << A.size() << endl;
    while(pos < A.size()) {
        currlen += A[pos].size();
	cout << "Current Length " << pos << " " << currlen << endl;
        if(currlen < B) {
            currlen++;
            rightpos++;
        }
        else if(currlen > B) {
	    cout << leftpos << " " << rightpos <<  " " << A[leftpos] << " " << A[rightpos] << endl;
	    cout << pos << " " << A[pos] << " " << currlen << endl;
            string temp = build_string(A,B,leftpos,rightpos-1);
            result.push_back(temp);
            leftpos = pos;
            rightpos = pos;
            currlen = A[pos].size();
        }
	pos++;
    }
    cout << leftpos << " " << A.size()-1 <<  " "  << A[leftpos] << " " << A[A.size()-1] << endl;
    string temp = build_last_string(A,B,leftpos,A.size()-1);
    result.push_back(temp);
    for(int i = 0 ; i < result.size() ;i++) {
	    cout << result[i] << endl;
    }
}
