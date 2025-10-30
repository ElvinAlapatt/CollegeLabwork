#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<time.h>

#define PORT 8080
#define BUFFER_SIZE 256
#define LOCALHOST "127.0.0.1"

void error_check(int x, char success[])
{
    if (x < 0)
    {
        perror("something went wrong");
        exit(1);
    }
    else
    {
        printf("%s\n", success);
    }
}

struct sockaddr_in create_socket_address()
{
    struct sockaddr_in socket_address;
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = inet_addr(LOCALHOST);
    socket_address.sin_port = htons(PORT);
    
    return socket_address;
}

char* get_time(){
	time_t t = time(NULL);
	return ctime(&t);
}

int main(){
	int  s = socket(AF_INET,SOCK_DGRAM,0);
	error_check(s,"Socket created");
	
	struct sockaddr_in server_address = create_socket_address();
	socklen_t server_len = sizeof(server_address);
	
	//bind
	int b = bind(s,(struct sockaddr *)&server_address,server_len);
	error_check(b,"Binded Success");
	
	struct sockaddr_in client_address;
	socklen_t client_len = sizeof(client_address);
	
	char buffer[BUFFER_SIZE] = "";
	//char reply[] = "\n...Hello this is server\n";
	char* reply = get_time();
	int status = recvfrom(s,buffer,BUFFER_SIZE,0,(struct sockaddr *)&client_address,&client_len);
	error_check(status,buffer);
	
	status = sendto(s,reply,strlen(reply),0,(struct sockaddr *)&client_address,client_len);
	error_check(status,"reply sent to client");
	
	close(s);
	
	return 0;
	
	
}
