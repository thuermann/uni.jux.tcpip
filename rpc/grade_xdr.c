#include <rpc/rpc.h>

#include "get_grade.h"

bool_t xdr_stu_id_num(xdr_handle, obj)
XDR *xdr_handle;
char *obj;
{
	return xdr_string(xdr_handle, &obj, ID_NUM_SIZE);
}
