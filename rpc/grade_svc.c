#include <stdio.h>
#include <rpc/rpc.h>

#include "get_grade.h"

#define GRADE_FILE "grades"
#define NO         0
#define YES        1

main()
{
	char *get_grade_1();

	if (registerrpc(GRADE_PROG, GRADE_VERS_1, GET_GRADE_PROC,
			get_grade_1, xdr_stu_id_num, xdr_char)
	    == -1)
	{
		fprintf(stderr, "Error: cannot register service.\n");
		return 1;
	}
	svc_run();
}

char *get_grade_1(id_num)
char *id_num;
{
	static char grade;
	FILE *fp;
	char tmp_id_num[ID_NUM_SIZE + 1];
	int done;

	done = NO;
	if ((fp = fopen(GRADE_FILE, "r")) != NULL)
	{
		while (done == NO
		       && fscanf(fp, "%s %c", tmp_id_num, &grade) != EOF)
		{
			if (strncmp(id_num, tmp_id_num, ID_NUM_SIZE) == 0)
				done = YES;
		}
		fclose(fp);
	}
	else
		fprintf(stderr, "Error: cannot open file: %s\n", GRADE_FILE);

	if (done == NO)
		grade = NO_GRADE;

	return &grade;
}
