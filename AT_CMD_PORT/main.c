/*
 * File: main.c
 * Brief:
 * -----
 * File Created: Monday, 11th February 2019 5:18:50 pm
 * Author: ldj
 * -----
 * Last Modified: Tuesday, 12th February 2019 9:40:47 am
 * Modified By: ldj
 * -----
 * Copyright (c) 2019
 */

#include "stdio.h"
#include "at.h"
#include "at_user_opt.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

//	#define AT_TEST_STR AT_STR_TEST
#define AT_TEST_STR AT_STR_TEST_INVALID

int main(int argc, char *argv[])
{
	AT_Module_Init();
	at_printf("test with str:AT_STR_TEST_AT\r\n");
	at_printf("-------------------------\r\n");
	AT_CMD_process(AT_STR_TEST_AT);
	at_printf("test with str:AT_STR_TEST\r\n");
	at_printf("-------------------------\r\n");
	AT_CMD_process(AT_STR_TEST);
	at_printf("test with str:AT_STR_READ\r\n");
	at_printf("-------------------------\r\n");
	AT_CMD_process(AT_STR_READ);
	at_printf("test with str:AT_STR_WRITE\r\n");
	at_printf("-------------------------\r\n");
	AT_CMD_process(AT_STR_WRITE);
	at_printf("test with str:AT_STR_EXECUT\r\n");
	at_printf("-------------------------\r\n");
	AT_CMD_process(AT_STR_EXECUT);
	at_printf("test with str:AT_STR_INVALID\r\n");
	at_printf("-------------------------\r\n");
	AT_CMD_process(AT_STR_INVALID);
	return 0;
}
