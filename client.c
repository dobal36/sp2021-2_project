#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 8000

int main() {
        char buf[BUFSIZ] = {0,};
        struct sockaddr_in sin;
        int sock;
        int serverlen = sizeof(sin);

        if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
                perror("socket");
                exit(EXIT_FAILURE);
        }
        printf("Create Socket...\n");

        printf("building address...\n");
        memset((char *)&sin, '\0', serverlen);
        sin.sin_family = AF_INET;
        sin.sin_port = htons(PORT);
        sin.sin_addr.s_addr = inet_addr("127.0.0.1");

        if (connect(sock, (struct sockaddr *)&sin, serverlen)) {
                perror("connect");
                exit(EXIT_FAILURE);
        }
        printf("Now, connected to the server\n");
        printf("PLAYBALL!!!\n");

        close(sock);
}
