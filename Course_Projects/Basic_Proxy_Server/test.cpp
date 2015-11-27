#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>

using namespace std;

typedef struct node{
	int id;
	string last;
	string etag;
	string fname;
}url;


int main(){
	url myurl;
	map<string, url> mymap1;
	map<string, url> :: iterator it1;
	map<int , string> mymap2;
	map<int , string> :: iterator it2;
	
	/*
	mymap1[(char *)"Raghav"] = 100;
	mymap1[(char *)"IIIT"] = 200;
	mymap1[(char *)"Raghav"] = 300;
	for ( it1 = mymap1.begin(); it1 != mymap1.end(); it1++ ) {
		printf("%s == %d\n",(*it1).first,(*it1).second);
	}
	printf("\n");
	mymap2[100] = (char *)"Raghav";
	mymap2[200] = (char *)"IIIT";
	for ( it2 = mymap2.begin(); it2 != mymap2.end(); it2++ ) {
		printf("%d == %s\n",(*it2).first,(*it2).second);
	}
	printf("\n");
	map<int , char *> :: reverse_iterator rit2;
	for ( rit2 = mymap2.rbegin(); rit2 != mymap2.rend(); rit2++ ) {
		printf("%d == %s\n",(*rit2).first,(*rit2).second);
	}
	printf("Raghav: %d\n", mymap1.find((char*)"Raghav")->second);
	*/

	myurl.id = 1;
	myurl.last = "";
	myurl.etag = "";
	myurl.fname = "";


	mymap1["http://www.google.com"] = myurl;

//	mymap1["http://www.google.com"] = 1;
//	mymap1["http://www.espncricinfo.com/west-indies-v-australia-2012/content/current/story/560267.html"] = 2;
//	mymap1["http://www.espncricinfo.com/indian-premier-league-2012/content/current/story/560375.html"] = 3;

	mymap2[1] = "http://www.google.com";
	mymap2[2] = "http://www.espncricinfo.com";
	mymap2[3] = "http://www.espncricinfo.com";

	for ( it1 = mymap1.begin(); it1 != mymap1.end(); it1++ ) {
	//	printf("%s == %d\n",(*it1).first,(*it1).second);
	}
	printf("\n");

	int t=5;
	while(t--){
	/*	char in[50];
		scanf("%s", in);
		string query = in;
		it1 = mymap1.find(query);
		printf("%d\n", (*it1).second);
		if(it1 != mymap1.end()){
			printf("HIT\n");
		}
		else{
			printf("MISS\n");
		}
	*/
/*		char in[50];
		scanf("%s", in);
		string query = in;
		int arr[100];
		int index=0;
		for ( it2 = mymap2.begin(); it2 != mymap2.end(); it2++ ) {
			if(((*it2).second == query)){
				arr[index++] = (*it2).first;
			}
		}
		for(int i=0; i<index; i++){
			printf("%d\n", arr[i]);
		}
		for(int i=0; i<index; i++){
			for ( it1 = mymap1.begin(); it1 != mymap1.end(); it1++ ) {
				if(((*it1).second == arr[i])){
					cout << (*it1).first  << endl;
					break;
				}
			}
		}
*/


	}


	return 0;
}
