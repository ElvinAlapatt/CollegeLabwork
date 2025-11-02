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
	int s = socket(AF_INET,SOCK_DGRAM,0);
	error_check(s,"Socket created ....");
	
	//build server address
	struct sockaddr_in server_address = create_socket_address();
	socklen_t server_len = sizeof(server_address);
	
	//communicating..
	char buffer[BUFFER_SIZE] = "";
	char request[] = "Hello this is client i need greeting....";
	
	int status = sendto(s,request,strlen(request),0,(struct sockaddr *)&server_address,server_len);
	error_check(status,"Request sent to the server....");
	
	status = recvfrom(s,buffer,BUFFER_SIZE,0,(struct sockaddr *)&server_address,&server_len);
	error_check(status,buffer);
	
	close(s);
	return 0;
}
