#include <stdio.h>
#include <rpc/rpc.h>

#include "get_grade.h"

main(argc, argv)
int argc;
char **argv;
{
	int status;
	char grade;
	char *host, *id;

	if (argc != 3)
	{
		fprintf(stderr, "usage: %s server_name id#\n", argv[0]);
		return 1;
	}

	host = argv[1];
	id   = argv[2];

	status = callrpc(host, GRADE_PROG, GRADE_VERS_1, GET_GRADE_PROC,
			 xdr_stu_id_num, id, xdr_char, &grade);
	if (status == 0)
	{
		if (grade != NO_GRADE)
		{
			printf("Your grade is a %c\n", grade);
			return 0;
		}
		else
		{
			fprintf(stderr, "Cannot find grade in grade file\n");
			return 1;
		}
	}
	else
	{
		fprintf(stderr, "Error: callrpc(); %s\n",
			clnt_sperrno((enum clnt_stat)status));
		return 1;
	}
}
