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

int main(){
	int s = socket(AF_INET,SOCK_STREAM,0);
	error_check(s,"Socket created successfuly\n");
	
	//Building server address
	struct sockaddr_in server_address = c_s_a();
	
	//connecting
	int c = connect(s,(struct sockaddr *)&server_address,sizeof(server_address));
	error_check(c,"\nConnected to Server....\n");
	
	//message
	char buffer[BUFFER_SIZE] = "";
	char request[] = "\nHello this is client\n";
	
	int status = send(s,request,strlen(request),0);
	error_check(status,"Request sent to server....\n");
	
	status = recv(s,buffer,BUFFER_SIZE,0);
	error_check(status,buffer);
	
	close(s);
	return 0;
}
