/*
 * File: at_user_opt.c
 * Brief:
 * -----
 * File Created: Tuesday, 12th February 2019 7:23:33 pm
 * Author: ldj
 * -----
 * Last Modified: Tuesday, 12th February 2019 7:23:35 pm
 * Modified By: ldj
 * -----
 * Copyright (c) 2019
 */

#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "at.h"


//very important function must be creating for uer plantform
int user_put_char(int c) 
{
    //as user plantform
    printf("%c",c);
	return 0;
}

static void NULL_handler(AT_str_t *cmd_str)
{
	at_printf("NULL_handler\r\n");
}

static void at_str_handler(AT_str_t *cmd_str)
{
	at_printf("at_str_handler\r\n");
    AT_RSP_process("\r\nOK\r\n");
}

static void at_test_str_handler(AT_str_t *cmd_str)
{
	uint32_t test_data = 0x01234567;
	uint32_t rec_write_param1 = 0;
	uint32_t rec_write_param2 = 0;
	char *pTemp = NULL;
	char *param3 = NULL;
	uint32_t a[10] = {0};
	uint32_t b = 0;
	uint32_t c = 0;
	int d = 0;

	at_printf("cmd handler:at_test_str_handler\r\n");

	switch(cmd_str->at_cmd_type)
	{
	case AT_TEST_CMD:
		break;

	case AT_READ_CMD:
		AT_RSP_process("\r\n+TEST:%08x\r\n",test_data);
		break;

	case AT_WRITE_CMD:
		rec_write_param1 = strtol((const char*)cmd_str->AT_cmd_param,&pTemp,10);
		param3 = (char *)a;
		strncpy(param3,pTemp+1,1);
		//printf("param3 = %s\r\n",param3);
		//b [0] = param3;
		//b = strtoul(param3,0,10);
		//c = (uint32_t)param3;
		d = *param3 - '0';
		
        //printf("param3 = %d\r\n",b);
		//printf("param3 = %s\r\n",c);
		//printf("param3 = %d\r\n",d);
		rec_write_param2 = strtol((const char*)pTemp+1,&pTemp,16);
		printf("rec_write_param2 is %x\r\n",rec_write_param2);
	
		if(rec_write_param2 != 0)	
		{
			AT_RSP_process("\r\n+TEST:%d,%x\r\n",rec_write_param1,rec_write_param2);
			AT_RSP_process("\r\nOK\r\n");
		}
		else if(rec_write_param2 == 0 && d == 0)
		{
			AT_RSP_process("\r\n+TEST:%d,0",rec_write_param1);
			AT_RSP_process("\r\nOK\r\n");
		}
		else
		{
			printf("ERROR!\r\nPlease enter the correct format,such as 'AT+TEST=12,ae'\r\n");
		}	
		memset(param3,0,1);
		break;

	case AT_EXECUT_CMD:
		AT_RSP_process("\r\n+TEST:\r\n");
		AT_RSP_process("\r\nOK\r\n");
		break;

	case AT_INVALID_CMD:
		break;

	default:
		break;
	}
}

//user can add handler in this strcture
AT_cmd_handler_t cmd_handler[] = {
	{"AT",at_str_handler},
	{"TEST", at_test_str_handler},
	{"NULL", NULL_handler},
};

//do must not modify this function
uint32_t get_cmd_handler_number(void)
{
    return (sizeof(cmd_handler) / sizeof(AT_cmd_handler_t));
}
