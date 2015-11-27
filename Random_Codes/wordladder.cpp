#include<bits/stdc++.h>
using namespace std;
bool CanReach(string s1, string s2) {
    int count = 0;
    for(int i = 0 ; i < s1.size() ; i++) {
        if(s1[i] != s2[i]) count++;
    }
    return (count == 1);
}
void BuildGraph(vector<vector<int> > &G, vector<string> &dict) {
    for(int i = 0 ; i < dict.size() ; i++) {
        for(int j = i+1 ; j < dict.size() ; j++) {
            if(CanReach(dict[i],dict[j])) {
                G[i].push_back(j);
                G[j].push_back(i);
            }
        }
    }
}
int main() {
    string start = "bb";
    string end = "ab";
    vector<string> dictV;
    dictV.push_back("bb");
    dictV.push_back("ab");
    int n = dictV.size();
    int l = start.size();
    vector<vector<int> > G(n);
    BuildGraph(G,dictV);
    vector<vector<int> > dist(n,vector<int> (n,INT_MAX));
    for(int i = 0 ; i < n ;i++) dist[i][i] = 0;
    int source = n-2;
    int dest = n-1;
    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < G[i].size() ; j++ ) {
            dist[i][G[i][j]] = 1;
        }
    }
    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < n ; j++) {
            for(int k = 0 ; k < n ; k++) {
                if(dist[i][k] != INT_MAX and dist[k][j] != INT_MAX)
                    dist[i][j] = min(dist[i][j],dist[i][k] + dist[k][j]);
            }
        }
    }
    if(dist[source][dest] == INT_MAX) cout<< 0 << endl;
    else cout << dist[source][dest]+1 << endl;
}
