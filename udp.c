#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

#define fail(msg, cde) { puts(msg); exit(cde); }
#define swr(f, b, l) if (write(f, b, l) == -1) \
        printf("[warning] write fail: %s\n", strerror(errno))

#define socklen_in sizeof(struct sockaddr_in)
socklen_t socklen = sizeof(struct sockaddr);

int main(int argc, char **argv)
{
        int sockfd, len, maxlen;
        struct sockaddr_in servaddr;
        struct sockaddr client;
        char *quote, buf[512];

        if (argc < 2) fail("no quote passed", -1);
        quote = argv[1];
        len = strlen(quote);
        if (len > 511) fail("quote too long (max 511 bytes)", -2);

        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd == -1) fail("socket creation failed...", 1);
        bzero(&servaddr, socklen);

        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(17);

        if (bind(sockfd, (struct sockaddr *)&servaddr, socklen_in))
                fail("socket bind failed...", 2);

        for (;;) {
                maxlen = recvfrom(sockfd, buf, 512,
                                  0, &client, &socklen);
                if (maxlen < 0) printf("[warning] recv fail: %s\n",
                                       strerror(errno));
                if (maxlen > len) maxlen = len + 1;
                memcpy(buf, quote, maxlen - 1);
                buf[maxlen - 1] = '\n';
                sendto(sockfd, buf, maxlen, 0, &client, socklen);
        }
}
