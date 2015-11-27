#include<bits/stdc++.h>
using namespace std;

typedef vector<int> vi; 
typedef vector<vi> vvi; 
typedef pair<int,int> ii; 
#define sz(a) int((a).size()) 
#define pb push_back 
#define all(c) (c).begin(),(c).end() 
#define tr(container, it) for(typeof(container.begin()) it = container.begin(); it != container.end(); it++) 
#define present(c,x) ((c).find(x) != (c).end()) 
#define cpresent(c,x) (find(all(c),x) != (c).end()) 

int main()  {
	set< pair<int, pair< int, vector<int> > > > temp; 
	int total = 0; 
	tr(temp, it) { 
		total += it->second.first; 
	}
	vector<int> v(10,0);
	tr(v,it) {
		cout << *it << " ";
	}
	cout << endl;
	fill(all(v),10);
	tr(v,it) {
		cout << *it << " ";
	}
	cout << endl;
	cout << cpresent(v,5) << endl;
	cout << cpresent(v,10) << endl;
	cout << accumulate(all(v),(double)1, multiplies<double>() ) << endl;
}

