#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

#define PORT 8080
#define LOCALHOST "127.0.0.1"
#define BUFFER_SIZE 256

void error_check(int x,char success[]){
	if (x<0){
		perror("Something went wrong");
		exit(0);
	}
	else{
		printf("%s\n",success);
	}
}

struct sockaddr_in create_socket_address(const char *server_ip,int port){
	struct sockaddr_in socket_address;
	socket_address.sin_family = AF_INET;
	socket_address.sin_addr.s_addr = inet_addr(LOCALHOST);
	socket_address.sin_port = htons(PORT);
	
	return socket_address;
}

int main(){
	int c = socket(AF_INET,SOCK_DGRAM,0);
	error_check(c,"socket created");
	
	struct sockaddr_in server_address = create_socket_address(LOCALHOST,PORT);
	socklen_t server_len = sizeof(server_address);
	
	char buffer[BUFFER_SIZE] = "";
	char request[] = "\nHello this is client";
	
	int status = sendto(c,request,strlen(request),0,(struct sockaddr *)&server_address,server_len);
	error_check(status,"Message sent to client");
	
	status = recvfrom(c,buffer,BUFFER_SIZE,0,(struct sockaddr *)&server_address,&server_len);
	error_check(status,buffer);
	
	close(c);
}
