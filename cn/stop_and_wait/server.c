#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define PORT 8080
#define BUFFER_SIZE 256
#define LOCALHOST "127.0.0.1"

#define NUM_PACKETS 5

typedef struct
{
    int seq_num;
    int data;
} Packet;

typedef struct
{
    int ack_num;
} ACK;

void error_check(int x, char success[])
{
    if (x < 0)
    {
        perror("something went wrong!");
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

int main()
{
    // 1. Create server socket
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    error_check(s, "socket created!");

    // 2. Bind the socket to the server address
    struct sockaddr_in server_address = create_socket_address();
    int b = bind(s, (struct sockaddr *)&server_address, sizeof(server_address));
    error_check(b, "binding successful!");

    // 3. Communication with client
    struct sockaddr_in client_address;
    socklen_t client_len = sizeof(client_address);

    int expected_seq = 0;
    int packets_received = 0;

    // Loss simulation counters
    int drop_3 = 1;
    int drop_5 = 1;

    while (packets_received < NUM_PACKETS)
    {
        Packet packet;

        int status = recvfrom(s, &packet, sizeof(packet), 0, (struct sockaddr *)&client_address, &client_len);
        if (status > 0)
        {
            // Simulate packet loss
            if (packet.data == 3 && drop_3 > 0)
            {
                printf(">>> Simulating packet loss for data 3\n");
                drop_3--;
                continue;
            }
            else if (packet.data == 5 && drop_5 > 0)
            {
                printf(">>> Simulating packet loss for data 5\n");
                drop_5--;
                continue;
            }

            if (packet.seq_num == expected_seq)
            {
                printf("Packet accepted (data = %d, seq_num = %d)\n", packet.data, packet.seq_num);

                // Send ACK
                ACK ack;
                ack.ack_num = packet.seq_num;

                status = sendto(s, &ack, sizeof(ack), 0, (struct sockaddr *)&client_address, client_len);
                if (status > 0)
                {
                    printf("ACK sent for data %d\n", packet.data);
                    packets_received++;
                    expected_seq = 1 - expected_seq;
                }
		
            }
        }
    }

    // 4. Close socket
    close(s);

    return 0;
}
