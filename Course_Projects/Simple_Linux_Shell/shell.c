#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <wait.h>

typedef struct node{
	char command[100];
	int pid;
	struct node *next;
}node;

void child_handler(int  signum);   		//Signal Handlers
void sig_handler(int signum);

node* insert(node *q, char data[], int pid);
node* delete(node *q, pid_t pid);
void print_hist(node *q, int n);
void print_current(node *q);
void printall(node* q1, node* q2);

void printprompt();
void execute(char input[]);
void exec_nopipe(char input[]);
void exec_nopipe_for_pipe(char input[]);

char *init_input;
char **pipcmds;
char *ptr;
char *path;
char *user;
char hostname[20] = "";
char *home;
char *args[100];
node *current;
node *done;
node *history;

void sig_handler(int signum){
	if(signum == 2 || signum == 20){
		printf("Enter \"quit\" to terminate the program\n");
	}
	signal(SIGINT, sig_handler);
	signal(SIGTSTP, sig_handler);
	return;
}

void child_handler(int signum){
	int pid;
	pid = waitpid(WAIT_ANY, NULL, WNOHANG);
	if(pid != -1){
		current = delete(current, pid);
	}
	signal(SIGCHLD, child_handler);
	return;
}

node* insert(node *q, char data[], int pid){
	node* beg = q, *temp = (node*)malloc(sizeof(node));
	strcpy(temp->command, data);
	temp->pid = pid;
	temp->next = NULL;
	q = q->next;
	if(q == NULL){
		beg->next = temp;
		return beg;
	}
	while(q->next != NULL){
		q = q->next;
	}
	q->next = temp;
	return beg;
}

node* delete(node *q, int pid){
	node *beg = q, *prev = q;
	q = q->next;
	if(q == NULL){
		return beg;
	}
	while(q != NULL){
		if(q->pid == pid){
			done = insert(done, q->command, q->pid);
			printf("\ncommand %s pid %d exited\n", q->command, q->pid);
			prev->next = q->next;
		}
		prev = q;
		q = q->next;
	}
	return beg;
}

void print_hist(node *q, int n){
	if(n == -1)n = 100;
	q = q->next;
	if(q == NULL){
		printf("History Empty\n");
		return;
	}
	int count = 0;
	while(q != NULL && count < n){
		count++;
		printf("%d. %s\n", count, q->command);
		q = q->next;
	}
}

void print_current(node *q){
	printf("List of currently executing processes spawned from this shell:\n");
	q = q->next;
	if(q == NULL){
		printf("No background processes running\n");
		return;
	}
	while(q != NULL){
		printf("command name: %s process id: %d\n", q->command, q->pid);
		q = q->next;
	}
}

void print_all(node *q, node *p){
	printf("List of all processes spawned from this shell:\n");
	q = q->next;
	p = p->next;
	if(p == NULL && q == NULL){
		printf("No processes spawned yet\n");
		return;
	}
	while(q != NULL){
		printf("command name: %s process id: %d\n", q->command, q->pid);
		q = q->next;
	}
	while(p != NULL){
		printf("command name: %s process id: %d\n", p->command, p->pid);
		p = p->next;
	}
}

void exec_pipes(int no_of_pipes){
	int i, status;
	int pipes[no_of_pipes][2];
	for(i=0; i<no_of_pipes; i++){
		pipe(&pipes[i][0]);				// Sets up all the pipes
	}

	for(i=0; i<=no_of_pipes; i++){
		if(fork() == 0){
			if(i == 0){
				dup2(pipes[i][1], 1);
			}
			else if(i == no_of_pipes){
				dup2(pipes[i-1][0], 0);
			}
			else{
				dup2(pipes[i-1][0], 0);
				dup2(pipes[i][1], 1);
			}
			int j;
			for(j=0; j<no_of_pipes; j++){
				close(pipes[j][0]);
				close(pipes[j][1]);
			}
			
			exec_nopipe_for_pipe(pipcmds[i]);
			
			exit(0);
		}
	}
	int j;
	for(j=0; j<no_of_pipes; j++){
		close(pipes[j][0]);
		close(pipes[j][1]);
	}

	for(i=0; i<=no_of_pipes; i++){
		wait(&status);
	}

}

void exec_nopipe_for_pipe(char input[]){                                            //Function used only for executing commands in a pipe instruction
	int j=0, k=0;
	char *temp = (char*)malloc(50*sizeof(char));
	char *inpfname = (char*)malloc(50*sizeof(char));
	char *outfname = (char*)malloc(50*sizeof(char));

	if( !strchr(input, '<') && !strchr(input, '>')){
		char store[100];
		int arg_num = 0;
		strcpy(store, input);
		char *pch = strtok(input, " ");
		while(pch != NULL){
			args[arg_num] = (char*)malloc(100 * sizeof(char));
			strcpy(args[arg_num++], pch);
			pch = strtok(NULL, " ");
		}
		args[arg_num] = NULL;
		
		if(execvp(args[0], args) == -1){
			printf("%s: command does not exist\n", args[0]);
			exit(0);
		}
	}
	else if(  strchr(input, '>') && !strchr(input, '<') ){
		j = 0, k = 0;
		int arg_num = 0;
		while(input[j] != '>'){
			if(input[j] == ' ' || input[j] == '\t'){
				temp[k] = '\0';
				k=0;
				args[arg_num] = (char*)malloc(100 * sizeof(char));
				strcpy(args[arg_num++], temp);
				j++;
				continue;
			}					
			temp[k++] = input[j++];
		}
		args[arg_num] = NULL;
		j++;
		while(input[j] == ' ' || input[j] == '\t'){
			j++;
		}
		k=0;
		while(input[j] != '\0' && input[j] != ' '){
			outfname[k++] = input[j++];	
		}
		outfname[k] = '\0';
		
		int out = open(outfname, O_WRONLY | O_CREAT, S_IRWXU);
		dup2(out ,1);
		close(out);
		if(execvp(args[0], args) == -1){
		printf("%s: command does not exist\n", args[0]);
			exit(0);
		}
	}
	else if( strchr(input, '<') && !strchr(input, '>') ){
		j = 0, k = 0;
		int arg_num = 0;
		while(input[j] != '<'){
			if(input[j] == ' ' || input[j] == '\t'){
				temp[k] = '\0';
				k=0;
				args[arg_num] = (char*)malloc(100 * sizeof(char));
				strcpy(args[arg_num++], temp);
				j++;
				continue;
			}					
			temp[k++] = input[j++];
		}
		args[arg_num] = NULL;
		j++;
		while(input[j] == ' ' || input[j] == '\t'){
			j++;
		}
		k=0;
		while(input[j] != '\0' && input[j] != ' '){
			inpfname[k++] = input[j++];	
		}
		inpfname[k] = '\0';

		int in = open(inpfname, O_RDONLY, S_IRWXU);
		if(in == -1){
			printf("%s: File does not exist\n", inpfname);
		}
		dup2(in ,0);
		close(in);
		if(execvp(args[0], args) == -1){
			printf("%s: command does not exist\n", args[0]);
			exit(0);
		}
	}

	free(temp);
	free(inpfname);
	free(outfname);

}

void exec_nopipe(char input[]){                                                         //Function used to execute commands without pipes
	int j=0, k=0;
	char *temp = (char*)malloc(50*sizeof(char));
	char *inpfname = (char*)malloc(50*sizeof(char));
	char *outfname = (char*)malloc(50*sizeof(char));
	char store[100];

	if( !strchr(input, '<') && !strchr(input, '>')){
		int arg_num = 0;
		strcpy(store, input);
		char *pch = strtok(input, " ");
		while(pch != NULL){
			args[arg_num] = (char*)malloc(100 * sizeof(char));
			strcpy(args[arg_num++], pch);
			pch = strtok(NULL, " ");
		}
		args[arg_num] = NULL;
		if(!strcmp(args[0], "cd")){
			if(arg_num == 2){
				if(!strcmp(args[1], "~")){
					history = insert(history, store, getpid());
					sleep(0.5);
					chdir(home);
				}
				else if(args[1][0] == '~'){
					strcpy(temp, args[1] + 1);
					strcpy(args[1], home);
					strcat(args[1], temp);
					history = insert(history, store, getpid());
					sleep(0.5);
					chdir(args[1]);

				}
				else{
					history = insert(history, store, getpid());
					sleep(0.5);
					chdir(args[1]);
				}
			}
			else{
				history = insert(history, store, getpid());
				sleep(0.5);
				chdir(home);
			}
		}
		else if(!strcmp(args[0], "pid")){
			if(arg_num == 1){
				history = insert(history, store, getpid());
				sleep(0.5);
				printf("command name:./a.out process id:%d\n", getpid());
			}
			else if(!strcmp(args[1], "current")){
				history = insert(history, store, getpid());
				sleep(0.5);
				print_current(current);
			}
			else if(!strcmp(args[1], "all")){
				history = insert(history, store, getpid());
				sleep(0.5);
				print_all(done, current);
			}
		}
		else if(!strncmp(args[0], "hist", 4)){
			if(!strcmp(args[0], "hist")){
				history = insert(history, store, getpid());
				sleep(0.5);
			
				print_hist(history, -1);
			}
			else{
				history = insert(history, store, getpid());
				sleep(0.5);
				
				int n = atoi(args[0] + 4);
				print_hist(history, n);
				
			}
		}
		else if(!strncmp(args[0], "!hist", 5)){

			int n = atoi(args[0] + 5);
			node *q = history;
			q = q->next;
			int count = 0;
			while(q != NULL && count < n){
				count++;
				if(count == n){
					strcpy(init_input, q->command);
					execute(q->command);
				}
				q = q->next;
			}
			if(count > n){
				printf("%d commands have not been run yet", n);
			}
		}
		else if(strchr(store, '&')){

			args[arg_num - 1] = NULL;
			int pid = fork();
			if(pid == 0){
				if(execvp(args[0], args) == -1){
					printf("%s: command does not exist\n", args[0]);
					exit(0);
				}
			}
			else{
				history = insert(history, store, pid);
				current = insert(current, store, pid);
				printf("command: %s pid: %d\n", store, pid);
				sleep(0.5);
				//no waiting for background processes	
				return;
			}
		}
		else{
			int pid = fork();
			if(pid == 0){
				if(execvp(args[0], args) == -1){
					printf("%s: command does not exist\n", args[0]);
					exit(0);
				}
			}
			else{
				history = insert(history, store, pid);
				sleep(0.5);
				wait(NULL);
			}
		}
	}
	else if(  strchr(input, '>') && !strchr(input, '<') ){
		j = 0, k = 0;
		int arg_num = 0;
		while(input[j] != '>'){
			if(input[j] == ' ' || input[j] == '\t'){
				temp[k] = '\0';
				k=0;
				args[arg_num] = (char*)malloc(100 * sizeof(char));
				strcpy(args[arg_num++], temp);
				j++;
				continue;
			}					
			temp[k++] = input[j++];
		}
		args[arg_num] = NULL;
		j++;
		while(input[j] == ' ' || input[j] == '\t'){
			j++;
		}
		k=0;
		while(input[j] != '\0' && input[j] != ' '){
			outfname[k++] = input[j++];	
		}
		outfname[k] = '\0';

		int pid = fork();
		if(pid == 0){
			int out = open(outfname, O_WRONLY| O_TRUNC | O_CREAT, S_IRWXU);
			dup2(out ,1);
			close(out);
			if(execvp(args[0], args) == -1){
				printf("%s: command does not exist\n", args[0]);
				exit(0);
			}
		}
		else{
			history = insert(history, init_input, pid);
			sleep(0.5);
			wait(NULL);
		}
	}
	else if( strchr(input, '<') && !strchr(input, '>') ){
		j = 0, k = 0;
		int arg_num = 0;
		while(input[j] != '<'){
			if(input[j] == ' ' || input[j] == '\t'){
				temp[k] = '\0';
				k=0;
				args[arg_num] = (char*)malloc(100 * sizeof(char));
				strcpy(args[arg_num++], temp);
				j++;
				continue;
			}					
			temp[k++] = input[j++];
		}
		args[arg_num] = NULL;
		j++;
		while(input[j] == ' ' || input[j] == '\t'){
			j++;
		}
		k=0;
		while(input[j] != '\0' && input[j] != ' '){
			inpfname[k++] = input[j++];	
		}
		inpfname[k] = '\0';
		int pid = fork();
		if(pid == 0){
			int in = open(inpfname, O_RDONLY, S_IRWXU);
			if(in == -1){
				printf("%s: File does not exist\n", inpfname);
			}
			dup2(in ,0);
			close(in);
			if(execvp(args[0], args) == -1){
				printf("%s: command does not exist\n", args[0]);
				exit(0);
			}
		}
		else{		
			history = insert(history, init_input, pid);
			sleep(0.5);
			wait(NULL);
		}
	}
	else if( strchr(input, '<') && strchr(input, '>') ){
		j = 0, k = 0;
		int arg_num = 0;
		while(input[j] != '<'){
			if(input[j] == ' ' || input[j] == '\t'){
				temp[k] = '\0';
				k=0;
				args[arg_num] = (char*)malloc(100 * sizeof(char));
				strcpy(args[arg_num++], temp);
				j++;
				continue;
			}					
			temp[k++] = input[j++];
		}
		args[arg_num] = NULL;
		j++;
		while(input[j] == ' ' || input[j] == '\t'){
			j++;
		}

		k=0;
		while(input[j] != ' '){
			inpfname[k++] = input[j++];	
		}
		inpfname[k] = '\0';

		while(input[j] == ' ' || input[j] == '\t' || input[j] == '>'){
			j++;
		}

		k=0;
		while(input[j] != '\0' && input[j] != ' ' && input[j] != '\t'){
			outfname[k++] = input[j++];	
		}
		outfname[k] = '\0';

		int pid = fork();
		if(pid == 0){
			int in = open(inpfname, O_RDONLY, S_IRWXU);
			int out = open(outfname, O_WRONLY| O_TRUNC | O_CREAT, S_IRWXU);
			if(in == -1){
				printf("%s: File does not exist\n", inpfname);
			}
			if(out == -1){
				printf("%s: File does not exist\n", outfname);
			}
			dup2(in  ,0);
			dup2(out ,1);

			close(in);
			close(out);
			if(execvp(args[0], args) == -1){
				printf("%s: command does not exist\n", args[0]);
				exit(0);
			}
		}
		else{
			history = insert(history, init_input, pid);
			sleep(0.5);
			wait(NULL);
		}
	}

	free(temp);
	free(inpfname);
	free(outfname);

}


void printprompt(){									//Function which prints the user command prompt

	path = getcwd(NULL, 0);
	if(strcmp(home, path) == 0){
		printf("<%s@%s:~>$ ", user, hostname);
	}
	else if((ptr = strstr(path, home)) != NULL){
		printf("<%s@%s:~/%s>$ ", user, hostname, ptr+strlen(home)+1);
	}
	else{
		printf("<%s@%s:%s>$ ", user, hostname, path);
	}

}

void execute(char input[]){							//Function parses input to find presence of pipes in a command
	int no_of_pipes = 0, i = 0;
	
	pipcmds = (char **)malloc(10*sizeof(char*));
	for(i=0; i<10; i++){
		pipcmds[i] = (char*)malloc(25 * sizeof(char));
	}

	char store[100] = "";
	strcpy(store, input);

	char *pip = strtok(input, "|");
	while(pip != NULL){
		strcpy(pipcmds[no_of_pipes], pip);
		no_of_pipes++;
		pip = strtok(NULL, "|");
	}
	no_of_pipes--;

	if(no_of_pipes > 0){
		char temp[100];
		for(i=0; i<=no_of_pipes; i++){
			strcpy(temp, pipcmds[i]);
			int j=0, k=0, flag = 0;
			while(temp[j] != '\0'){
				if((temp[j] == ' ' || temp[j] == '\t') && (flag == 0)){
					j++;
					continue;
				}
				flag = 1;
				pipcmds[i][k++] = temp[j++];
				pipcmds[i][k] = '\0';
			}
			pipcmds[i][k] = '\0';
			k = 0;
			for(j = strlen(temp)-1; j>=0; j-- ){
				if(temp[j] != ' ' && temp[j] != '\t')break;
				else
					k++;
			}
			pipcmds[i][strlen(pipcmds[i]) - k] = '\0';

		}
		exec_pipes(no_of_pipes);
	}

	else{
		exec_nopipe(input);
	}
	
}

int main(){

	signal(SIGINT,  sig_handler);
	signal(SIGTSTP, sig_handler);
	signal(SIGCHLD, child_handler);


	printf("\t\t\t\t\t########## Starting Bash Shell ##########\n\n\n");

	home = getcwd(NULL, 0);
	user = getenv("USER");
	gethostname(hostname, sizeof(hostname));


	current = (node *)malloc(sizeof(node));
	done    = (node *)malloc(sizeof(node));
	history = (node *)malloc(sizeof(node));
	current->next = done->next = history->next = NULL;

	init_input = (char*)malloc(128 * sizeof(char));

	while(1){
		printprompt();
		scanf("%[^\n]", init_input);
		getchar();
		if(!strlen(init_input))continue;
		if(!strcmp(init_input, "quit")){
			printf("\t\t\t\t\t########## Exiting Bash Shell ##########\n\n\n");
			break;
		}
		execute(init_input);
		init_input[0] = '\0';
	}
	return 0;
}
