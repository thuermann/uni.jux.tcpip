#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(argc, argv)
char **argv;
{
	struct sockaddr_in addr;
	int port;
	int sock, msg_sock;
	int pid;

	port = atoi(argv[1]);

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}

	addr.sin_family      = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port        = htons(port);

	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind");
		exit(1);
	}

	listen(sock, 5);

	while (1) {
		struct sockaddr_in peer;
		int size = sizeof(peer);
		msg_sock = accept(sock, (struct sockaddr *)&peer, &size);
		if (msg_sock < 0) {
			perror("accept");
			continue;
		}
		if ((pid = fork()) < 0) {
			perror("fork");
			continue;
		}
		else if (pid == 0) {
			close(sock);

			/* work with msg_sock */

			close(msg_sock);
			exit(0);
		}
		else {
			close(msg_sock);
			waitpid(pid, NULL, WNOHANG);
		}
	}
}
