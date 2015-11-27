#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <netdb.h>
#include <cstring>
#include <pthread.h>
#include <errno.h>
#include <map>
#include <semaphore.h>
#include <sys/sem.h>
#include <unistd.h>
#include <inttypes.h>


using namespace std;

#define PAGE "/"
#define PORT 8080
#define USERAGENT "HTMLGET 1.0"
#define SIZE 4096

char *last, *etag;

typedef struct node{
	int id;
	string last;
	string fname;
}url;


map<string, url> url2id;
map<int , string> id2host;
FILE *log = NULL;

sem_t map1_sem, map2_sem, log_sem, file_sem[105];
int sem_index;

void dummy(){
	last = (char*)malloc(100*sizeof(char));
	last[0] = '\0';
}

void header_parser(char *header){
	char *temp, *mod = NULL;
	temp = (char*)malloc(strlen(header)*sizeof(char));
	strcpy(temp, header);

	char *pch1 = NULL, *pch2 = NULL;


	// Response Code
	pch1 = strtok(temp, "\r\n");
	pch2 = strtok(pch1, " ");
	pch2 = strtok(NULL, " ");
	int code = atoi(pch2);
	printf("Response code: %d\n", code);
	if(code == 200){
		printf("code %d: Response OK\n", code);
	}
	else if(code == 304){
		printf("code %d: Not Modified\n", code);
	}

	// Last Modified Date
	strcpy(temp, header);
	mod = strstr(temp, "Last-Modified: ");
	if(mod != NULL){
		mod += strlen("Last-Modified: ");
		pch2 = strtok(mod, "\r");
		strcpy(last, pch2);
		printf("Last-Modified: %s\n", last);
	}

}


void* request_server(void* arg){

	map<string, url> :: iterator it1;
	map<int , string> :: iterator it2;
	url myurl;int urlindex = 1;

	int connected = *((int*)(&arg)), bytes_recieved;
	char send_data [SIZE] , recv_data[SIZE];
	char mainurl[150];
	char host[150];


	int flag=0;
	while(1){
		printf("\n\nWaiting to receive url\n");
		bytes_recieved = recv(connected,recv_data,SIZE,0);
		recv_data[bytes_recieved] = '\0';

		if (strcmp(recv_data , "q") == 0 || strcmp(recv_data , "Q") == 0){
			close(connected);
			break;
		}

		printf("\nRequest:\n%s\n" , recv_data);

	
		char *ding = (char*)malloc(sizeof(char) * 100);
		memcpy (ding,recv_data,strlen(recv_data)+1);
		char *ping1, *ping2;
		ping1 = strtok(ding, " ");
		ping2 = strtok(NULL, " ");

		if(strcasecmp(ping1, "search") == 0){

			strcpy(ping1, ping2);
			sprintf(ping2, "www.%s.com", ping1);

			int arr[100];
			int index=0;
			char pingu[strlen(ping2)+1];
			strcpy(pingu, ping2);
			string query = pingu;
			cout<<query<<endl;
			for ( it2 = id2host.begin(); it2 != id2host.end(); it2++ ) {
				if(((*it2).second == query)){
					arr[index++] = (*it2).first;
				}
			}
			printf("##########   SEARCH BY HOSTNAME   ###########\n");
			for(int i=0; i<index; i++){
				for ( it1 = url2id.begin(); it1 != url2id.end(); it1++ ) {
					if(((*it1).second.id == arr[i])){
						cout << (*it1).first  << endl;
						break;
					}
				}
			}

		fflush(stdout);
		recv_data[0] = '\0';
			continue;
		}
		else if(strcasecmp(ping1, "print") == 0){
			if(strcasecmp(ping2, "log") == 0){
				log = fopen("ProxyCache/Log.txt", "r");
				printf("##########   LOG FILE   ###########\n");
				char *ditchk = (char*)malloc(100*sizeof(char));
				while(fscanf(log, "%[^\n]", ditchk) != EOF){
					fgetc(log);
					printf("%s\n", ditchk);
				}
				free(ditchk);
				fclose(log);

			}
			else if(strcasecmp(ping2, "cache") == 0){
				printf("##########   CACHE   ###########\n");
				for ( it1 = url2id.begin(); it1 != url2id.end(); it1++ ) {
					cout<<(*it1).first<<endl;
				}

			}
		fflush(stdout);
		recv_data[0] = '\0';
			continue;
			
		}














		log = fopen("ProxyCache/Log.txt", "a");

		//////////////// header_parser function starts here  ///////////////////////

		char *orgurl2 = (char*)malloc(sizeof(char)*strlen(recv_data));
		char *orgurl = (char*)malloc(sizeof(char)*strlen(recv_data));
		memcpy (orgurl2,recv_data,strlen(recv_data)+1);

		char *pch1 = NULL, *pch2 = NULL;
		pch1 = strtok(orgurl2, "\r\n");
		pch2 = strtok(pch1, " ");
		pch2 = strtok(NULL, " ");

		memcpy (orgurl,pch2,strlen(pch2)+1);
		printf("\nurl: %s\n", orgurl);
		strcpy(mainurl, orgurl);


		char *ipch1=NULL, *ipch2=NULL;
		char *ipch3 = (char*)malloc(sizeof(char) * strlen(recv_data));
		ipch1 = strstr(recv_data, "http://");
		if(ipch1 != NULL){
			ipch1 += 7;
			ipch2 = strstr(ipch1, "/");
		}
		else
			ipch2 = strstr(recv_data, "/");
		if(ipch2 != NULL){

			strcpy(ipch3, ipch1?ipch1:recv_data);

			if(ipch1)
				ipch3[ipch2-ipch1] = '\0';
			else
				ipch3[ipch2-recv_data] = '\0';

		}
		else{
			strcpy(ipch3, ipch1?ipch1:recv_data);
		}

		strcpy(host, ipch3);
		printf("host: %s\nresource: %s\n", ipch3, ipch2?ipch2:(char*)"/");





		memcpy (orgurl2,recv_data,strlen(recv_data)+1);
		pch1 = strstr(orgurl2, "If-Modified-Since: ");
		int further = 0, hit=0;
		if(pch1 != NULL){
			further = 1;
		}

		string query = orgurl;
		it1 = url2id.find(query);

		if(it1 != url2id.end()){
			hit = 1;
			if(further){
				pch1 += strlen("If-Modified-Since: ");
				const char *lastmod;
				lastmod = (*it1).second.last.c_str();
				memcpy (pch1,lastmod,strlen(lastmod)+1);
				strcat(pch1, "\r\n\r\n");
				memcpy (recv_data,orgurl2,strlen(orgurl2)+1);
				printf("\nNew Request:\n%s\n" , recv_data);
			}
			else{
				printf("HIT\n");

				fprintf(log, "%s::served from cache\n", mainurl);

				const char *fname;
				fname = (*it1).second.fname.c_str();
				FILE* f = fopen(fname, "r");
				fseek (f , 0 , SEEK_END);
				long long int lSize = ftell (f);
				rewind(f);

				char *buffer = (char*)malloc(sizeof(char)*(lSize+1));
				fread(buffer, 1, lSize, f);
				printf("Page Size: %lld\n", lSize);
				int amt_sent=0;
				long long int bytes_read = lSize;
				while(bytes_read>amt_sent)
				{
					int sent=send(connected, buffer+amt_sent,bytes_read-amt_sent, 0);
					amt_sent+=sent;
					printf("Sent: %d\n", amt_sent);
				}
				fflush(stdout);
				recv_data[0] = '\0';
				free(buffer);
				fclose(f);
				fclose(log);
			}


		}
		else{
			if(further){
				strcpy(pch1, "\r\n\r\n");
				memcpy (recv_data, orgurl2, strlen(orgurl2)+1);
				printf("\nNew Request:\n%s\n" , recv_data);
			}
		}

		if(hit && !further){
			continue;
		}

		fprintf(log, "%s::contacted origin server\n", mainurl);


		//////////////// header_parser function ends here  ///////////////////////


		//////////////// request_server function starts here  ///////////////////////


		//request_server(pch3, pch2?pch2:(char*)"/", connected);

		struct sockaddr_in *remote;
		int sock_new;
		int tmpres;
		char *ip;
		char *get;
		char buf[SIZE+1];

		int client = connected;

		int status;
		struct addrinfo hints;
		struct addrinfo *servinfo,*p;   // will point to the results
		char ipstr[1000];
		memset(&hints, 0, sizeof(hints)); // make sure the struct is empty
		hints.ai_family = AF_UNSPEC;  // don't care IPv4 or IPv6
		hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
		status = getaddrinfo("proxy.iiit.ac.in", "8080", &hints, &servinfo);
		sock_new = socket(servinfo->ai_family,servinfo->ai_socktype,servinfo->ai_protocol);

		struct timeval tv;
		tv.tv_sec = 2;  /* 2 Sec Timeout */
		setsockopt(sock_new, SOL_SOCKET, SO_RCVTIMEO,(char*)&tv,sizeof(struct timeval));

		int ret_val;
		ret_val = connect(sock_new,servinfo->ai_addr,servinfo->ai_addrlen);
		if ( ret_val == -1)
		{
			printf("%d\n",errno);
			printf("Error Occured\n");
		}


		get = recv_data;  			// GET Request

		int bytes_sent;
		bytes_sent = send(sock_new,get, strlen(get),0);
		if ( bytes_sent == -1 )
		{
			perror("Can't send query");
			exit(1);
		}
		printf("Bytes Sent %d\n",bytes_sent);

		//receive and display the page
		int bytes_read=1, flag = 0;
		char *htmlcontent;
		FILE *f=NULL;int file_open=0;
		int pagelength = 0, not_modified = 0;
		printf("new url: %s\n", mainurl);
		while(bytes_read>0)
		{
			bytes_read = recv(sock_new, buf, sizeof(buf), 0);
			pagelength += strlen(buf);

			if(flag == 0){
				//////////////// header_parser function starts here  ///////////////////////

				htmlcontent = strstr(buf, "\r\n\r\n");
				char *header = (char*)malloc(strlen(buf)*sizeof(char));
				memcpy (header, buf, strlen(buf)+1);
				header[htmlcontent - buf] = '\0';
				printf("header: \n%s\n", header);


				char *temp, *mod = NULL;
				temp = (char*)malloc(strlen(header)*sizeof(char));
				memcpy (temp, header, strlen(header)+1);

				// Response Code
				pch1 = strtok(temp, "\r\n");
				pch2 = strtok(pch1, " ");
				pch2 = strtok(NULL, " ");
				int code = atoi(pch2);
				//printf("\nResponse code: %d\n", code);
				/*
				   if(code == 200){
				   printf("code %d: Response OK\n", code);
				   }
				   else if(code == 304){
				   printf("code %d: Not Modified\n", code);
				   }
				 */
				// Last Modified Date
				memcpy (temp, header, strlen(header)+1);
				mod = strstr(temp, "Last-Modified: ");
				if(mod != NULL){
					mod += strlen("Last-Modified: ");
					pch2 = strtok(mod, "\r");
					memcpy (last, pch2, strlen(pch2)+1);
					printf("Last-Modified: %s\n", last);
				}
				else{
					mod = strstr(temp, "Date: ");
					if(mod){
						mod += strlen("Date: ");
						pch2 = strtok(mod, "\r");
						memcpy (last, pch2, strlen(pch2)+1);
						printf("Date: %s\n", last);
					}

				}


				string query = mainurl;
				it1 = url2id.find(query);

				if(it1 == url2id.end()){
					char fname[50];
					sprintf(fname, "ProxyCache/%d", urlindex);
					if(urlindex == 101){
						urlindex = 1;

					}
					for ( it1 = url2id.begin(); it1 != url2id.end(); it1++ ) {
						if((*it1).second.id == urlindex){
							url2id.erase(it1);	
							break;
						}
					}
					for ( it2 = id2host.begin(); it2 != id2host.end(); it2++ ) {
						if((*it2).first == urlindex){
							id2host.erase(it2);	
							break;
						}
					}

					myurl.id = urlindex++;
					myurl.last = last;
					myurl.fname = fname;
					url2id[query] = myurl;

					string hname = host;
					id2host[myurl.id] = hname;

					file_open=1;
					f = fopen(fname, "w");
					fprintf(log, "%s::ProxyCache/%d %s ", mainurl, myurl.id, last);
				}
				else{

					myurl = (*it1).second;

					const char *fname;
					fname = (*it1).second.fname.c_str();

					printf("\nResponse code: %d\n", code);
					if(code == 200){
						myurl.last = last;
						fprintf(log, "%s::ProxyCache/%d %s ", mainurl, myurl.id, last);
						url2id[query] = myurl;
						file_open=1;
						f = fopen(fname, "w");
					}
					else if(code == 304){
						not_modified = 1;
						fprintf(log, "%s::served from cache\n", mainurl);

						FILE* f = fopen(fname, "r");
						fseek (f , 0 , SEEK_END);
						long long int lSize = ftell (f);
						rewind(f);
						char *buffer = (char*)malloc(sizeof(char)*(lSize+1));
						fread(buffer, 1, lSize, f);
						printf("Page Size: %lld\n", lSize);
						int amt_sent=0;
						long long int bytes_read = lSize;
						while(bytes_read>amt_sent)
						{
							int sent=send(connected, buffer+amt_sent,bytes_read-amt_sent, 0);
							amt_sent+=sent;
							printf("Sent: %d\n", amt_sent);
						}
						fclose(f);
						fflush(stdout);
						break;
					}
				}


				//////////////// header_parser function ends here  ///////////////////////
				if(htmlcontent != NULL){
					flag = 1;
					htmlcontent += 4;
				}

			}
			else{
				htmlcontent = buf;
			}

			char *check = strstr(buf, "</html>");
			if(check != NULL){
				buf[check-buf+7] = '\0';
			}

			if(file_open)
				fprintf(f, "%s", htmlcontent);


			int amt_sent=0;
			while(bytes_read>amt_sent)
			{
				int sent=send(client, buf+amt_sent,bytes_read-amt_sent, 0); 
				amt_sent+=sent;
			}
			if(check != NULL){
				break;
			}

		}

		if(file_open){
			file_open = 0;
			fclose(f);
		}

		printf("Size of HTML Page: %d\n", pagelength);

		if(!not_modified)
			fprintf(log, "%d\n", pagelength);


		fprintf(stderr, "TESTING\n");
		if(tmpres < 0)
		{
			perror("Error receiving data");
		}

		close(sock_new);
		fclose(log);


		//////////////// request_server function ends here  ///////////////////////

		printf("Page Sent\n");
		fflush(stdout);
		recv_data[0] = '\0';
	}
	close(connected);
	printf("Thread Exiting: %d\n", connected);

}

int main()
{
	pthread_t thread[1000];
	int t_count = 0;
	
//	sem_t map1_sem, map2_sem, log_sem, file_sem[105];
	sem_index = 0;
	sem_init(&map1_sem,0,1);
	sem_init(&map2_sem,0,1);
	sem_init(&log_sem,0,1);
	for(int i=0; i<105; i++){
		sem_init(&file_sem[i],0,1);
	}


	log = fopen("ProxyCache/Log.txt", "w");
	fclose(log);

	dummy();
	int sock, connected;

	struct sockaddr_in server_addr,client_addr;
	socklen_t sin_size;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}


	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5000);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(server_addr.sin_zero),8);

	if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))
			== -1) {
		perror("Unable to bind");
		exit(1);
	}

	if (listen(sock, 500) == -1) {
		perror("Listen");
		exit(1);
	}

	printf("\nTCPServer Waiting for client on port 5000\n");
	fflush(stdout);

	while(1){
		sin_size = sizeof(struct sockaddr_in);

		connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);

		printf("\n I got a connection from (%s , %d)",	inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

		pthread_create(&thread[t_count++], NULL, request_server, (void*)connected);

	}
	for(int i=0; i<1000; i++){
		pthread_join(thread[i], NULL);
	}
	close(sock);

	sem_destroy(&map1_sem);
	sem_destroy(&map2_sem);
	sem_destroy(&log_sem);
	for(int i=0; i<105; i++){
		sem_destroy(&file_sem[i]);
	}

	return 0;
}
