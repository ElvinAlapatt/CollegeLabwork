#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<time.h>

#define PORT 8080
#define LOCALHOST "127.0.0.1"
#define BUFFER_SIZE 256
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

void error_check(int x, char success[]){
	if (x < 0){
		perror("Something went wrong!!..");
		exit(1);
	}
	else{
		printf("%s\n",success);
	}
}

struct sockaddr_in create_socket_address(){
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr(LOCALHOST);
	server_address.sin_port = htons(PORT);
	
	return server_address;
}

int main()
{
	int s = socket(AF_INET , SOCK_DGRAM , 0);
	error_check(s,"Socket created successfull......");
	
	struct sockaddr_in server_address = create_socket_address();
	int b = bind(s,(struct sockaddr *)&server_address , sizeof(server_address));
	error_check(b,"Binded Successfully....");
	
	struct sockaddr_in client_address ;
	socklen_t client_len = sizeof(client_address);
	
	int expected_seq = 0;
	int packets_received = 0;
	
	int drop3 = 0;
	int drop5 = 0;
	
	while (packets_received < NUM_PACKETS)
	{
		PACKET packet;
		int status = recvfrom(s,&packet , sizeof(packet),0,(struct sockaddr *)&client_address,&client_len);
		
		if (status > 0)
		{
			if (packet.data == 3 && drop3 > 0){
				printf("Simulating packet loss for 3rd frame....");
				drop3--;
				continue;
			}
			else if (packet.data == 5 && drop3 > 0){
				printf("Simulating packet loss for 5th frame....");
				drop5--;
				continue;
			}
			if(packet.seq_num == expected_seq){
				printf("Packets accepted........");
				packets_received++;
				
				ACK ack;
				ack.ack_num = packet.seq_num;
				status = sendto(s,&ack,sizeof(ack),0,(struct sockaddr *)&client_address,client_len);
				
			if (status > 0)
			{
				printf("ACK sent fot the data");
			}
			
			expected_seq = 1 - expected_seq;
			
				
			}
		}
	}
close(s);
return 0;
}
