#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define TIMEOUT 3
#define WINDOW_SIZE 2

typedef struct {
    int seq;
    char data[100];
} Frame;

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);

    int total_frames;
    printf("Enter the number of frames: ");
    scanf("%d", &total_frames);

    Frame *all_frames = malloc(sizeof(Frame) * total_frames);

    for (int i = 0; i < total_frames; i++) {
        all_frames[i].seq = i;
        printf("Enter message for Frame %d: ", i);
        scanf(" %[^\n]", all_frames[i].data);
    }

    Frame window[WINDOW_SIZE];
    int base = 0, next_seq = 0;
    int lost_frame3 = 0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) { perror("Socket creation failed"); exit(1); }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    fd_set readfds;
    struct timeval tv;

    while (base < total_frames) {
        
        while (next_seq < base + WINDOW_SIZE && next_seq < total_frames) {
            Frame f = all_frames[next_seq];
            window[next_seq % WINDOW_SIZE] = f;

            if (f.seq == 3 && lost_frame3 == 0) {
                printf("Simulating loss of Frame %d\n", f.seq);
                lost_frame3 = 1;
            } else {
                sendto(sockfd, &f, sizeof(f), 0, (struct sockaddr *)&servaddr, len);
                printf("Sent Frame %d: %s\n", f.seq, f.data);
            }

            if (base == next_seq) {
                tv.tv_sec = TIMEOUT;
                tv.tv_usec = 0;
            }

            next_seq++;
        }

        
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);
        int activity = select(sockfd + 1, &readfds, NULL, NULL, &tv);

        if (activity > 0 && FD_ISSET(sockfd, &readfds)) {
            int ack;
            recvfrom(sockfd, &ack, sizeof(ack), 0, NULL, NULL);
            printf("Received ACK %d\n", ack);
            base = ack + 1;
        } else {
          
            printf("Timeout\nResending frames from %d to %d\n", base, next_seq);
            for (int i = base; i < next_seq; i++) {
                sendto(sockfd, &window[i % WINDOW_SIZE], sizeof(Frame), 0, (struct sockaddr *)&servaddr, len);
                printf("Resent Frame %d: %s\n", window[i % WINDOW_SIZE].seq, window[i % WINDOW_SIZE].data);
            }
            tv.tv_sec = TIMEOUT;
            tv.tv_usec = 0;
        }
    }

    printf("All frames sent successfully!\n");
    free(all_frames);
    close(sockfd);
    return 0;
}