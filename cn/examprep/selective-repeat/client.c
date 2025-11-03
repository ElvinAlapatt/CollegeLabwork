#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 8080
#define LOCALHOST "127.0.0.1"

#define NUM_PACKETS 5
#define WINDOW 3
#define TIMEOUT 2
#define MAX_RETRIES 5

typedef struct
{
	int seq_num;
	int data;
}PACKET;

typedef struct
{
	int ack_num;
}ACK;

void error_check(int x , char success[])
{
	if (x < 0){
		perror("Something went wrong...");
		exit(1);
	}
	else{
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
	int ackarr[NUM_PACKETS+1]={0};
	int s = socket(AF_INET,SOCK_DGRAM,0);
	error_check(s,"Socket Created...");

	struct timeval timeout = {TIMEOUT , 0};
	setsockopt(s,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));
	
	struct sockaddr_in server_address = csa();
	socklen_t server_len = sizeof(server_address);
	
	//set params
	int base = 1;
	int next = 1;
	int retries = 0;
	int status;
	PACKET packet;
	while(base <= NUM_PACKETS)
	{
		while(next < (base + WINDOW) && next <= NUM_PACKETS)
		{
			packet.seq_num = next;
			packet.data = next;
			status = sendto(s,&packet,sizeof(packet),0,(struct sockaddr *)&server_address,server_len);
			if (status > 0){
				printf("[PACKET] packet %d sent to server\n",packet.seq_num);
				next++;
			}
			
		}
		//wait for ack
		ACK ack;
		status = recvfrom(s,&ack,sizeof(ack),0,(struct sockaddr *)&server_address,&server_len);
		if (status > 0){
			printf("[ACK] recieved ack for frame %d\n",base);
			ackarr[ack.ack_num] = 1;
			while (ackarr[base] && base <= NUM_PACKETS){
				base++;
			}
		}
		else
		{
			printf(".............Timeout error ....\n");
			for (int i = base ; i < next ; i++){
				if (ackarr[i]==0){
					packet.seq_num = i;
					packet.data = i;
					status = sendto(s,&packet,sizeof(packet),0,(struct sockaddr *)&server_address,server_len);
					printf("Frame Sent ...%d\n",packet.seq_num);
				}

			}
		}
	}
	close(s);
	return 0;
}

