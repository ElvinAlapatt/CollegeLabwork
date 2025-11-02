#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

#define PORT 8080
#define LOCALHOST "127.0.0.1"

#define NUM_PACKETS 5
#define WINDOW 3

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
	if (x < 0){
		perror("Something went wrong !");
		exit(1);
	}
	else
	{
		printf("%s\n",success);
	}
}

struct sockaddr_in csa()
{
	struct sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(LOCALHOST);
	sa.sin_port = htons(PORT);
	
	return sa;
}

int main()
{
	int s = socket(AF_INET, SOCK_DGRAM,0);
	error_check(s,"Socket created.....");
	
	struct sockaddr_in server_address = csa();
	int b = bind(s,(struct sockaddr *)&server_address,sizeof(server_address));
	error_check(b,"Binded..........");
	
	struct sockaddr_in client_address = csa();
	socklen_t client_len = sizeof(client_address);
	
	//set params
	int expected_seq = 1;
	int packets_recvd = 0;
	
	//set flags
	int drop3 = 1;
	int drop5 = 1;
	
	while(packets_recvd < NUM_PACKETS)
	{
		PACKET packet;
		int status = recvfrom(s,&packet,sizeof(packet),0,(struct sockaddr *)&client_address,&client_len);
		if (status > 0)
		{
			if(packet.seq_num == 3 && drop3 > 0)
			{
				printf("[simulating packet loss] losing data .... %d\n",packet.data);
				drop3 = 0;
				continue;
			}
			
			else if(packet.seq_num == 5 && drop5 > 0)
			{
				printf("[simulating packet loss] losing data .... %d\n",packet.data);
				drop5--;
				continue;
			}
			
			if(packet.seq_num == expected_seq)
			{
				printf("Packets Recieved for data %d\n",packet.data);
				ACK ack;
				ack.ack_num = expected_seq;
				status = sendto(s,&ack,sizeof(ack),0,(struct sockaddr *)&client_address,client_len);
				if (status > 0)
				{
					printf("[ACK SENT for data %d]\n",packet.data);
					packets_recvd++;
					//drop3 = 1;
					expected_seq++;
				}
			}
		}
	}
	close(s);
	return 0;
}
