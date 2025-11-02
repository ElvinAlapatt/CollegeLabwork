#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define LOCALHOST "127.0.0.1"
#define BUFFER_SIZE 256

#define WINDOW_SIZE 3
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

struct sockaddr_in create_socket_address()
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(LOCALHOST);
    addr.sin_port = htons(PORT);
    return addr;
}

int main()
{
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    error_check(s, "Server socket created");

    struct sockaddr_in server_address = create_socket_address();
    int b = bind(s, (struct sockaddr *)&server_address, sizeof(server_address));
    error_check(b, "Server binding successful");

    struct sockaddr_in client_address;
    socklen_t client_len = sizeof(client_address);

    int expected_seq = 0;
    int packets_received = 0;

    // Simulate loss for these data packets
    int drop_3 = 1;
    int drop_5 = 1;

    printf("\n==================== SERVER STARTED ====================\n");
    printf("Listening on %s:%d\n", LOCALHOST, PORT);
    printf("Expecting %d packets with window size %d\n", NUM_PACKETS, WINDOW_SIZE);
    printf("========================================================\n\n");

    while (packets_received < NUM_PACKETS)
    {
        Packet packet;
        ssize_t status = recvfrom(s, &packet, sizeof(packet), 0, (struct sockaddr *)&client_address, &client_len);

        if (status < 0)
        {
            perror("⚠️  recvfrom failed");
            continue;
        }

        // Simulate packet loss
        if (packet.data == 3 && drop_3 > 0)
        {
            printf("🚫 [LOSS] Simulated loss for DATA=%d (seq=%d)\n", packet.data, packet.seq_num);
            drop_3--;
            continue;
        }
        if (packet.data == 5 && drop_5 > 0)
        {
            printf("🚫 [LOSS] Simulated loss for DATA=%d (seq=%d)\n", packet.data, packet.seq_num);
            drop_5--;
            continue;
        }

        printf("\n📦 [RECEIVED] Data=%d | Seq=%d | Expected=%d\n", packet.data, packet.seq_num, expected_seq);

        if (packet.seq_num == expected_seq)
        {
            printf("✅ [ACCEPTED] Correct packet received.\n");

            ACK ack;
            ack.ack_num = packet.seq_num;
            sendto(s, &ack, sizeof(ack), 0, (struct sockaddr *)&client_address, client_len);
            printf("📤 [ACK SENT] ACK=%d\n", ack.ack_num);

            expected_seq++;
            packets_received++;
        }
        else
        {
            printf("⚠️ [OUT OF ORDER] Received seq=%d, expected seq=%d\n", packet.seq_num, expected_seq);
            if (expected_seq > 0)
            {
                ACK ack;
                ack.ack_num = expected_seq - 1;
                sendto(s, &ack, sizeof(ack), 0, (struct sockaddr *)&client_address, client_len);
                printf("↩️  [DUPLICATE ACK SENT] ACK=%d\n", ack.ack_num);
            }
        }
    }

    printf("\n🎉 [SERVER] All packets received successfully!\n");
    printf("========================================================\n");
    close(s);
    return 0;
}

