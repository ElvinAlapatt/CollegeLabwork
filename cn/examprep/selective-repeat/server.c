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
    int buffer[NUM_PACKETS + 1] = {0};

	int s = socket(AF_INET,SOCK_DGRAM,0);
	error_check(s,"Socket Created...");
	
	struct sockaddr_in server_address = csa();
	int b = bind(s,(struct sockaddr *)&server_address,sizeof(server_address));
	error_check(b,"Binded....");
	
	struct sockaddr_in client_address = csa();
	socklen_t client_len = sizeof(client_address);
	
	int expected_seq = 1;
	int packets_recieved = 0;
	
	int drop3 = 1;
	int drop5 = 2;
	int status;
	PACKET packet;
	while(packets_recieved < NUM_PACKETS)
	{
		status = recvfrom(s,&packet,sizeof(packet),0,(struct sockaddr *)&client_address,&client_len);
		if (status > 0)
		{
			if(packet.seq_num == 3 && drop3 > 0)
			{
				printf("\nSimulating packet loss for frame %d\n",packet.seq_num);
				drop3--;
				continue;
			}
			else if(packet.seq_num == 5 && drop5 > 0)
			{
				printf("\nSimulating packet loss for frame %d\n",packet.seq_num);
				drop5--;
				continue;
			}
			
			if (buffer[packet.seq_num] == 0){
                buffer[packet.seq_num] = packet.data;
                packets_recieved++;
                printf("Frame Recieved...%d\n",packet.seq_num);
            }

            ACK ack;
            ack.ack_num = packet.seq_num;
            status = sendto(s,&ack,sizeof(ack),0,(struct sockaddr *)&client_address,client_len);
            if (status > 0){
                printf("ACK sent....");
            }
		}
	}
    for(int i = 1; i <= NUM_PACKETS ; i++)
    {
        printf("\n..........DATA IN THE BUFFER .......\n");
        printf("{%d , %d}",i,buffer[i]);
    }
	close(s);
	return 0;
}
