#include <stdio.h>

#include <string.h>

#ifndef USER_COM_ENA
	#define USER_COM_ENA
#endif

#include "exer_com.h"

int main(int argv, char *argc[])
{
	ST_EXER	st_val[2] = {{'1', '3', "Goog morning!"}, {'2', '4', "Goog afternoon!"}};
	ST_EXER *st_val_p[2] = {&st_val[0], &st_val[1]};

	printf("*** Init ****\n");

	printf("struct from=%c\n", st_val_p[0]->from);
	printf("struct to=%c\n", st_val_p[0]->to);
	printf("struct msg=%s\n", st_val_p[0]->msg);
	printf("struct from=%c\n", st_val_p[1]->from);
	printf("struct to=%c\n", st_val_p[1]->to);
	printf("struct msg=%s\n", st_val_p[1]->msg);

	st_val_p[1]->from = 'A';
	st_val_p[1]->to = 'B';

	strcpy(st_val_p[1]->msg, "This is a pen!");

	printf("*** Modify ****\n");

	printf("struct from=%c\n", st_val[0].from);
	printf("struct to=%c\n", st_val[0].to);
	printf("struct msg=%s\n", st_val[0].msg);
	printf("struct from=%c\n", st_val[1].from);
	printf("struct to=%c\n", st_val[1].to);
	printf("struct msg=%s\n", st_val[1].msg);

	return 0;
}
