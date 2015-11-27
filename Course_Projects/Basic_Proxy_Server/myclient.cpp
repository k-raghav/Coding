/* myclient.c */

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/sem.h>
#include <semaphore.h>

using namespace std;

#define USERAGENT "HTMLGET 1.0"


void header_parser(char *header){
	fprintf(stderr, "%s\n", header);
}

int main()
{

	int sock, bytes_recieved;  
	char send_data[1024],recv_data[1024];
	struct hostent *host;
	struct sockaddr_in server_addr;  

	int tmpres;
	char buf[BUFSIZ+1];

	host = gethostbyname("127.0.0.1");

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}

	struct timeval tv;

	tv.tv_sec = 1;  /* 1 Sec Timeout */

	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO,(char*)&tv,sizeof(struct timeval));

	server_addr.sin_family = AF_INET;     
	server_addr.sin_port = htons(5000);   
	server_addr.sin_addr = *((struct in_addr *)host->h_addr);
	bzero(&(server_addr.sin_zero),8); 

	if (connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) 
	{
		perror("Connect");
		exit(1);
	}


	while(1)
	{

		printf("\nSEND (q or Q to quit) : ");
		scanf("%[^\n]", send_data);
		getchar();
		printf("%s\n", send_data);

		int i;
		int conditional = 0;


		for(i=0; send_data[i]!='\0'; i++){
			send_data[i] = tolower(send_data[i]);
		}

		if (strcmp(send_data , "q") == 0 || strcmp(send_data , "Q") == 0){
			send(sock,send_data,strlen(send_data), 0); 
			close(sock);
			break;
		}


		char *ding = (char*)malloc(sizeof(char) * 100);
		memcpy (ding,send_data,strlen(send_data)+1);
		char *ping1, *ping2;
		ping1 = strtok(ding, " ");
		ping2 = strtok(NULL, " ");

		if(strcasecmp(ping1, "search") == 0 || strcasecmp(ping1, "print") == 0){
			send(sock,send_data,strlen(send_data), 0); 
			continue;
		}



		printf("Conditional Get? (Y/N) : ");char ch = getchar();
		conditional = (tolower(ch)=='y')?1:0;
		getchar();



		char *pch1=NULL, *pch2=NULL;
		char *pch3 = (char*)malloc(sizeof(char) * strlen(send_data));
		pch1 = strstr(send_data, "http://");
		if(pch1 != NULL){
			pch1 += 7;
			pch2 = strstr(pch1, "/");
		}
		else
			pch2 = strstr(send_data, "/");
		if(pch2 != NULL){

			strcpy(pch3, pch1?pch1:send_data);

			if(pch1)
				pch3[pch2-pch1] = '\0';
			else
				pch3[pch2-send_data] = '\0';

		}
		else{
			strcpy(pch3, pch1?pch1:send_data);
		}

		printf("host: %s\nresource: %s\n", pch3, pch2?pch2:(char*)"/");

		char *host = pch3;
		char *page = pch2?pch2:(char*)"/";


		char *pch4 = (char*)malloc(sizeof(char) * strlen(host));
		char *junk = NULL;
		junk = strstr(host, "http://");
		if(junk == NULL){
			strcpy(pch4, "http://");
			strcat(pch4, host);
			strcpy(host, pch4);
		}


		char *query;                     /// GET REQUEST CREATION
		char *getpage = page;
		if(getpage[0] == '/'){
			getpage = getpage + 1;
			//      fprintf(stderr,"Removing leading \"/\", converting %s to %s\n", page, getpage);
		}

		/*	if(strlen(last) && strlen(etag)){
		//char *tpl = "GET %s/%s HTTP/1.1\r\nHost: %s\r\nIf-Modified-Since: %s\r\nIf-None-Match: %s\r\nUser-Agent: %s\r\n\r\n";  // Conditional GET Request
		char *tpl = (char*)"GET %s/%s HTTP/1.1\r\nHost: %s\r\nIf-Modified-Since: %s\r\nIf-None-Match: %s\r\n\r\n";  // Conditional GET Request
		// -5 is to consider the %s %s %s in tpl and the ending \0
		query = (char *)malloc(strlen(host)+strlen(getpage)+strlen(USERAGENT)+strlen(tpl)+strlen(last)+strlen(etag)+strlen(host)-6+1);
		sprintf(query, tpl, host, getpage, host,last, etag);
		}
		else{
		 */	
		char *tpl = (char *)"GET %s/%s HTTP/1.1\r\nHost: %s\r\n";   // Regular GET
		// -5 is to consider the %s %s %s in tpl and the ending \0
		query = (char *)malloc(strlen(host)+strlen(getpage)+strlen(USERAGENT)+strlen(tpl)+strlen(host)-6+1);
		sprintf(query, tpl, host, getpage, host);
		if(conditional){
			strcat(query, "If-Modified-Since: junk\r\n");
		}
		else{
			strcat(query, "\r\n");
		}
		//	}
		char* get = query;

		fprintf(stderr, "\nQuery is:\n<<START>>\n\n%s<<END>>\n", get);





		if (strcmp(send_data , "q") != 0 && strcmp(send_data , "Q") != 0){
			send(sock,get,strlen(get), 0); 
		}

		memset(buf, 0, sizeof(buf));
		int htmlstart = 0;
		int pagelength = 0;
		char * htmlcontent;
		while((tmpres = recv(sock, buf, BUFSIZ, 0)) > 0){
			pagelength += strlen(buf); 
			if(htmlstart == 0) // Separate the response header
			{
				char *header = (char*)malloc(strlen(buf)*sizeof(char));
				htmlcontent = strstr(buf, "\r\n\r\n");
				strcpy(header, buf);
				header[htmlcontent - buf] = '\0';
				header_parser(header);	// Parse the response header

				if(htmlcontent != NULL){
					htmlstart = 1;
					htmlcontent += 4;
				}
			}else{
				htmlcontent = buf;
			}
			if(htmlstart){
				fprintf(stdout, "%s", htmlcontent);
			}
			memset(buf, 0, tmpres);
		}
		printf("Size of HTML Page Received: %d\n", pagelength);
		printf("\nPage Received\n");

	}   
	return 0;
}
