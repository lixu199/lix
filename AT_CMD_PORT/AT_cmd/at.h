/*
 * File: at.h
 * Brief:
 * -----
 * File Created: Wednesday, 6th February 2019 11:29:24 pm
 * Author: ldj
 * -----
 * Last Modified: Tuesday, 12th February 2019 9:43:59 am
 * Modified By: ldj
 * -----
 * Copyright (c) 2019
 */


#ifndef __AT_H__
#define __AT_H__

#include <stdio.h>
#include "string.h"
#include "stdint.h"
#include "at_errors.h"
#include "at_debug.h"

#define AT_CMD_LINE_LEN 128 //max length per AT cmd string
#define AT_CMD_CHAR_NUM_MAX 10

#define AT_STA_STR "AT"
#define AT_END_CHAR_CR '\r'
#define AT_END_CHAR_LF '\n'

typedef enum
{
	//confirm the cmd be supported
	AT_TEST_CMD, 
	//read value
	AT_READ_CMD,
	//wite value 
	AT_WRITE_CMD,
	//execute cmd
	AT_EXECUT_CMD,
	//invalid cmd
	AT_INVALID_CMD
} AT_cmd_t;

typedef struct
{
	uint8_t *AT_cmd_str;
	uint8_t *AT_cmd_param;
	AT_cmd_t at_cmd_type;
}AT_str_t;

typedef struct
{
	uint8_t cmd_name[12];
	ATSta_t (*cmd_handler)(AT_str_t *);
	//int (*cmd_responser)(void);
} AT_cmd_handler_t;

void AT_RSP_process(char *format, ...);
ATSta_t AT_CMD_process(char *at_cmd_str);
void AT_Module_Init(void);
#endif
