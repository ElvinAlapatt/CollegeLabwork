#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

#define PORT 8080
#define LOCALHOST "127.0.0.1"
#define BUFFER_SIZE 256

void error_check(int x , char success[]){
	if (x < 0){
		perror("Something Went Wrong!");
		exit(0);
	}
	else{
		printf("%s\n",success);
	}
}

struct sockaddr_in c_s_a(){
	struct sockaddr_in socket_address;
	socket_address.sin_family = AF_INET;
	socket_address.sin_addr.s_addr = inet_addr(LOCALHOST);
	socket_address.sin_port = htons(PORT);
	
	return socket_address;
}

char* read_file(){
	static char c[4096];
	
	FILE *f = fopen("sample.txt","r");
	sprintf(c,"Filename: sample.txt\n\n");
	
	size_t bytes_read = fread(c + strlen(c),1,4095 - strlen(c),f);
	c[strlen(c) + bytes_read] = '\0';
	fclose(f);
	
	return c;
	
	
}

int main(){
	int s = socket(AF_INET,SOCK_STREAM,0);
	error_check(s,"Socket created successfuly\n");
	
	//binding
	struct sockaddr_in server_address = c_s_a();
	socklen_t server_len = sizeof(server_address);
	int b = bind(s,(struct sockaddr *)&server_address,server_len);
	error_check(b,"Binded successfuly\n");
	
	//listening
	int l = listen(s,5);//5 is the backlog
	error_check(l,"\nListening.....\n");
	
	//accepting the client 
	struct sockaddr_in client_address;
	socklen_t client_len = sizeof(client_address);
	int c = accept(s,(struct sockaddr *)&client_address,&client_len);
	error_check(c,"Client connected!..\n");
	
	//communication
	char buffer[BUFFER_SIZE] = "";
	//char reply[] =  "\nHello this is server !!!";
	char *reply = read_file();
	int status = recv(c,buffer,BUFFER_SIZE,0);
	error_check(status,buffer);
	
	status = send(c,reply,strlen(reply),0);
	error_check(status,"Reply send to client");
	
	//closing
	close(c);
	close(s);
	return 0;
}
