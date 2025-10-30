// receiver.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

typedef struct {
    int seq;
    char data[100];
} Frame;

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

    int expected_seq = 0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(1);
    }

    printf("Receiver is running on port %d...\n", PORT);

    while (1) {
        Frame f;
        memset(&f, 0, sizeof(f));
        int n = recvfrom(sockfd, &f, sizeof(f), 0, (struct sockaddr *)&cliaddr, &len);
        if (n <= 0) continue;

        printf("\nReceived Frame %d: %s\n", f.seq, f.data);

        if (f.seq == expected_seq) {
            printf("Accepted Frame %d\n", f.seq);
            sendto(sockfd, &f.seq, sizeof(f.seq), 0, (struct sockaddr *)&cliaddr, len);
            printf("sent ack %d\n", f.seq);
            expected_seq++;
        } else {
            int last_ack = expected_seq - 1;
            printf("Out-of-order Frame %d (expected %d). Discarded.\n", f.seq, expected_seq);
            printf("Re-sent ACK %d\n", last_ack);
            sendto(sockfd, &last_ack, sizeof(last_ack), 0, (struct sockaddr *)&cliaddr, len);
        }
    }

    close(sockfd);
    return 0;
}

