#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>

#define PORT 8000

int main() {
	char buf[BUFSIZ];
	struct sockaddr_in sin, cli;
	int access_socket, comm_socket;
	int clientlen = sizeof(cli);
	int serverlen = sizeof(sin);
	
	printf("creating a socket...\n");
	if ((access_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	printf("building address...\n");
	memset((char *)&sin, '\0', serverlen);
	sin.sin_family = AF_INET;
        sin.sin_port = htons(PORT);
        sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	printf("building address...\n");
        if (bind(access_socket, (struct sockaddr *)&sin, serverlen)) {
                perror("bind");
                exit(EXIT_FAILURE);
        }

	printf("listen...\n");
        if (listen(access_socket, 5)) {
                perror("listen");
                exit(EXIT_FAILURE);
        }

	printf("accept...\n");
        if ((comm_socket = accept(access_socket, (struct sockaddr *)&cli, &clientlen))==-1){
                perror("accept");
                exit(EXIT_FAILURE);
        }
	
	printf("client is now accepted\n");
	printf("PLAYBALL!!!\n");

	int answer[3];
	srand((unsigned)time(NULL));
	
	do {
		answer[0] = rand() % 10;
		answer[1] = rand() % 10;
		answer[2] = rand() % 10;
	} while (
		(answer[0] == answer[1]) | (answer[1] == answer[2]) | (answer[2] == answer[0])
	);
	printf("Answer: %d %d %d\n", answer[0], answer[1], answer[2]);	
	
	close(comm_socket);	
}
