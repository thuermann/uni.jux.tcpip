all: get_grade grade_svc

#CC = gcc
CFLAGS = -O

grade_svc: grade_svc.o grade_xdr.o
	$(CC) -o grade_svc grade_svc.o grade_xdr.o

get_grade: get_grade.o grade_xdr.o
	$(CC) -o get_grade get_grade.o grade_xdr.o

clean:
	rm -f core *.o

get_grade.o grade_svc.o grade_xdr.o: get_grade.h
