#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define LOCALHOST "127.0.0.1"
#define BUFFER_SIZE 256

#define TIMEOUT_SEC 2
#define MAX_RETRIES 5
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

struct sockaddr_in create_address()
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(LOCALHOST);

    return addr;
}

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

int main()
{
    // 1. Create client socket
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    error_check(s, "socket created!");

    // Set socket timeout
    struct timeval timeout = { TIMEOUT_SEC, 0 };
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    // 2. Build server address structure
    struct sockaddr_in server_address = create_address();
    socklen_t server_len = sizeof(server_address);

    // 3. Send packets
    for (int i = 1; i <= NUM_PACKETS; i++)
    {
        Packet packet;
        packet.seq_num = (i - 1) % 2;
        packet.data = i;

        int retries = 0;

        while (retries < MAX_RETRIES)
        {
            // Send
            printf("Sending Data %d (seq_num = %d, attempt %d)\n", packet.data, packet.seq_num, retries + 1);
            int status = sendto(s, &packet, sizeof(packet), 0, (struct sockaddr *)&server_address, server_len);
            if (status < 0)
            {
                perror("send failed!");
                retries++;
                continue;
            }

            // Wait
            ACK ack;

            status = recvfrom(s, &ack, sizeof(ack), 0, (struct sockaddr *)&server_address, &server_len);
            if (status < 0)
            {
                printf("Timeout! Retransmitting...\n");
                retries++;
            }
            else if (ack.ack_num == packet.seq_num)
            {
                printf("ACK received for Data %d\n", packet.data);
                break;
            }
        }
    }

    // 4. Close socket
    close(s);

    return 0;
}
