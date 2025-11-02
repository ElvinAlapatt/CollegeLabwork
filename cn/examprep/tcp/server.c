#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<time.h>

#define PORT 8080
#define BUFFER_SIZE 256
#define LOCALHOST "127.0.0.1"
#define BACKLOG 5

void error_check(int x,char success[])
{
	if (x<0){
		perror("Somethinf went wrong in the error check");
	}
	else{
		printf("%s\n",success);
	}
}

struct sockaddr_in create_socket_address()
{
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr(LOCALHOST);
	server_address.sin_port = htons(PORT);
	
	return server_address;
}

int main()
{
	//socket
	int s = socket(AF_INET,SOCK_STREAM,0);
	error_check(s,"Socket created ....");
	
	//binding
	struct sockaddr_in server_address = create_socket_address();
	int b = bind(s,(struct sockaddr *)&server_address, sizeof(server_address));
	error_check(b,"Binded success....");
	
	//listening
	int l = listen(s,BACKLOG);
	
	//build the client address
	struct sockaddr_in client_address = create_socket_address();
	socklen_t client_len = sizeof(client_address);
	//accept the client
	int c = accept(s,(struct sockaddr *)&client_address,&client_len);
	error_check(c,"Client is Connected....");
	
	//communicating
	char buffer[BUFFER_SIZE] = "";
	char reply[] = "Hello this is server....";
	
	int status = recv(c,buffer,BUFFER_SIZE,0);
	error_check(status,buffer);
	
	status = send(c,reply,strlen(reply),0);
	error_check(status,"Reply sent to the client.....");
	
	close(c);
	close(s);
	
	return 0;
}
