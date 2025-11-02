#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define LOCALHOST "127.0.0.1"
#define TIMEOUT_SEC 2
#define MAX_RETRIES 5
#define NUM_PACKETS 5
#define WINDOW_SIZE 3

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
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(LOCALHOST);
    return addr;
}

void error_check(int x, const char *msg)
{
    if (x < 0)
    {
        perror("❌ Error");
        exit(1);
    }
    else
    {
        printf("✅ %s\n", msg);
    }
}

int main()
{
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    error_check(s, "Client socket created");

    struct timeval timeout = {TIMEOUT_SEC, 0};
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    struct sockaddr_in server_address = create_address();
    socklen_t server_len = sizeof(server_address);

    int base = 0;
    int next_seq = 0;
    int retries = 0;

    printf("\n==================== CLIENT STARTED ====================\n");
    printf("Sending %d packets with window size %d\n", NUM_PACKETS, WINDOW_SIZE);
    printf("========================================================\n\n");

    while (base < NUM_PACKETS)
    {
        // Send packets in the window
        while (next_seq < base + WINDOW_SIZE && next_seq < NUM_PACKETS)
        {
            Packet packet;
            packet.seq_num = next_seq;
            packet.data = next_seq + 1;

            printf("📤 [SEND] Data=%d | Seq=%d\n", packet.data, packet.seq_num);
            ssize_t sent = sendto(s, &packet, sizeof(packet), 0, (struct sockaddr *)&server_address, server_len);
            if (sent < 0)
            {
                perror("send failed");
                break;
            }
            next_seq++;
        }

        // Wait for ACK
        ACK ack;
        ssize_t r = recvfrom(s, &ack, sizeof(ack), 0, (struct sockaddr *)&server_address, &server_len);

        if (r < 0)
        {
            printf("⏰ [TIMEOUT] No ACK received for base=%d → Retransmitting window...\n", base);
            retries++;
            if (retries >= MAX_RETRIES)
            {
                printf("❌ [ABORT] Exceeded %d retries. Stopping.\n", MAX_RETRIES);
                break;
            }
            next_seq = base;
        }
        else
        {
            printf("📩 [ACK RECEIVED] ACK=%d (Base=%d)\n", ack.ack_num, base);
            retries = 0;

            if (ack.ack_num >= base)
            {
                base = ack.ack_num + 1;
                if (next_seq < base)
                    next_seq = base;
                printf("✅ [WINDOW SLIDE] Base moved to %d\n", base);
            }
        }
    }

    printf("\n🎉 [CLIENT] All packets sent successfully!\n");
    printf("========================================================\n");
    close(s);
    return 0;
}

