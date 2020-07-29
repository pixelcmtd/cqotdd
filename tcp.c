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

socklen_t socklen = sizeof(struct sockaddr_in);
char newline[1] = { '\n' };

int main(int argc, char **argv)
{
        int sockfd, len, connfd;
        struct sockaddr_in servaddr;
        struct sockaddr client;
        char quote[512];

        if (argc < 2) fail("no quote passed", -1);
        len = strlen(argv[1]);
        if (len > 511) fail("quote too long (max 511 bytes)", -2);
        memcpy(quote, argv[1], len);
        quote[len++] = '\n';

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) fail("socket creation failed...", 1);
        bzero(&servaddr, socklen);

        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(17);

        if (bind(sockfd, (struct sockaddr *)&servaddr, socklen))
                fail("socket bind failed...", 2);

        if (listen(sockfd, 5)) fail("Listen failed...", 3);

        for (;;) {
                connfd = accept(sockfd, &client, &socklen);
                if (connfd < 0) fail("accept failed...", 4);
                swr(connfd, quote, len);
                close(connfd);
        }
}
