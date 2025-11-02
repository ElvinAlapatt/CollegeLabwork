#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 8080
#define LOCALHOST "127.0.0.1"

#define NUM_PACKETS 5

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
	
	struct sockaddr_in server_address = create_socket_address();
	int b = bind(s,(struct sockaddr *)&server_address , sizeof(server_address));
	error_check(b,"Binded ....");
	
	struct sockaddr_in client_address = create_socket_address();
	socklen_t client_len = sizeof(client_address);
	
	//set params
	int expected_seq = 0;
	int packets_recieved = 0;
	
	int drop3 = 1;
	int drop5 = 1;
	
	while(packets_recieved < NUM_PACKETS)
	{
		PACKET packet;
		int status = recvfrom(s,&packet,sizeof(packet),0,(struct sockaddr *)&client_address,&client_len);
		if (status > 0)
		{
			if(packet.data == 3 && drop3 > 0){
				printf("simulating packet loss for packet -> %d (seq_num = %d)\n",packet.data,packet.seq_num);
				drop3--;
				continue;
			}
			else if(packet.data == 5 && drop5 > 0)
			{
				printf("simulating packet loss for packet -> %d (seq_num = %d)\n",packet.data,packet.seq_num);
				drop5--;
				continue;
			}
			
			if (expected_seq == packet.seq_num)
			{
				printf("Packet recieved for the data -> %d\n",packet.data);
				ACK ack;
				ack.ack_num = packet.seq_num ;
				status = sendto(s,&ack,sizeof(ack),0,(struct sockaddr *)&client_address,client_len);
				if (status > 0)
				{
					printf("ACK sent to the client for the data -> %d\n",packet.data);
					packets_recieved++;
					expected_seq = 1 - expected_seq;
				}
			}
		}
	}
	
	close(s);
	return 0;
}
