#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 8080
#define LOCALHOST "127.0.0.1"

#define MAX_RETRIES 5
#define NUM_PACKETS 5
#define TIMEOUT 2

typedef struct
{
	int seq_num;
	int data;
}PACKET;

typedef struct
{
	int ack_num;
}ACK;

void error_check(int x,char success[])
{
	if(x < 0){
		perror("Something went wrong here...");
		exit(1);
	}
	else{
		printf("%s\n",success);
	}
}

struct sockaddr_in create_socket_address()
{
	struct sockaddr_in socket_address;
	socket_address.sin_family = AF_INET;
	socket_address.sin_port = htons(PORT);
	socket_address.sin_addr.s_addr = inet_addr(LOCALHOST);
	
	return socket_address;
}

int main()
{
	int s = socket(AF_INET,SOCK_DGRAM,0);
	error_check(s,"Socket created...");
	
	struct timeval timeout = {TIMEOUT , 0};
	setsockopt(s,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));
	
	struct sockaddr_in server_address = create_socket_address();
	socklen_t server_len = sizeof(server_address);
	
	for(int i = 1 ; i <= NUM_PACKETS ; i++)
	{
		PACKET packet;
		packet.seq_num = (i-1)%2;
		packet.data = i;
		
		int retries = 0;
		while (retries < MAX_RETRIES)
		{
			printf("Sending packet %d - (seq_num = %d ; times = %d)\n",packet.data,packet.seq_num,retries + 1);
			int status = sendto(s,&packet,sizeof(packet),0,(struct sockaddr *)&server_address,server_len);
			if (status < 0)
			{
				printf("packet is not sent packet -> %d\n",packet.data);
				retries++;
				continue;
			}
			//wait for ACK
			ACK ack;
			status = recvfrom(s,&ack,sizeof(ack),0,(struct sockaddr *)&server_address,&server_len);
			if (status < 0)
			{
				printf("Did not get an ACK for packet %d\n",packet.data);
				retries++;
			}
			else if(ack.ack_num == packet.seq_num)
			{
				printf("ACK recieved for packet - %d\n",packet.data);
				break;
			}
		}
	}
	close(s);
	return 0;
}
