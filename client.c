#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(argc, argv)
char **argv;
{
	struct hostent *gethostbyname();
	struct hostent *hp;
	struct sockaddr_in addr;
	int sock;
	int port;

	if ((hp = gethostbyname(argv[1])) == 0) {
		fprintf(stderr, "Unknown host: %s\n", argv[1]);
		exit(1);
	}
	port = atoi(argv[2]);

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}

	addr.sin_family = AF_INET;
	bcopy((char *)hp->h_addr, (char *)&addr.sin_addr, hp->h_length);
	addr.sin_port   = htons(port);

	if (connect(sock, (struct sockaddr *)&addr, sizeof addr) < 0) {
		perror("connect");
		exit(1);
	}

	/* work with sock */

	close(sock);

	return 0;
}
