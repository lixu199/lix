/*
 * File: at.c
 * Brief:
 * -----
 * File Created: Wednesday, 6th February 2019 11:29:24 pm
 * Author: ldj
 * -----
 * Last Modified: Tuesday, 12th February 2019 9:42:44 am
 * Modified By: ldj
 * -----
 * Copyright (c) 2019
 */

#include "at.h"

extern AT_cmd_handler_t cmd_handler[];
extern uint32_t get_cmd_handler_number(void);

uint8_t AT_cmd_buffer_temp[AT_CMD_LINE_LEN + 1] = {0};
uint8_t cmd_name_tmp[AT_CMD_CHAR_NUM_MAX + 2] = {0}; //+2 for "\r\n"
uint8_t current_opt_cut = 0;
uint8_t at_str_len = 0;
AT_str_t AT_str_temp;

static void AT_String_temp_init(void)
{
	memset(AT_cmd_buffer_temp, 0, AT_CMD_LINE_LEN + 1);
	memset(cmd_name_tmp, 0, AT_CMD_CHAR_NUM_MAX + 2);

	AT_str_temp.AT_cmd_str = AT_cmd_buffer_temp;
	AT_str_temp.AT_cmd_param = AT_cmd_buffer_temp;
	AT_str_temp.at_cmd_type = AT_INVALID_CMD;

	current_opt_cut = 0;
	at_str_len = 0;
}

static ATSta_t GetATCmdStr(char *input_str)
{
	uint8_t i;
	char *pTemp = input_str;
	AT_String_temp_init();

	AT_str_temp.AT_cmd_str[0] = *pTemp++;
	for (i = 1; i < AT_CMD_LINE_LEN; i++)
	{
		AT_str_temp.AT_cmd_str[i] = *pTemp++;
		if (AT_END_CHAR_LF == AT_str_temp.AT_cmd_str[i])
		{
			if (AT_END_CHAR_CR == AT_str_temp.AT_cmd_str[i - 1])
			{
				at_str_len = i + 1;
				return AT_STA_SUCCESS;
			}
		}
	}

	return AT_STA_ERROR_CAN_NOT_FIDN_END_CHAR;
}

static ATSta_t RemoveInvalidChar(void)
{
	uint8_t i;

	for (i = 0; i < at_str_len - 1 - 2; i++) //-2 for "AT"
	{
		if ((('A' == AT_str_temp.AT_cmd_str[i]) && ('T' == AT_str_temp.AT_cmd_str[i + 1])))
		{
			memcpy(AT_str_temp.AT_cmd_str, &AT_str_temp.AT_cmd_str[i], at_str_len - i);
			at_str_len -= i;
			AT_str_temp.AT_cmd_str[at_str_len] = '\0'; //add end of string
			if (at_str_len < 4)
			{
				return AT_STA_ERROR_LEN_SHORT; //can not execute this
			}
			else
			{
				return AT_STA_SUCCESS;
			}
		}
	}

	return AT_STA_ERROR_CAN_NOT_FIND_HEADER_CHAR;
}

static ATSta_t FindParamPoint(uint8_t *param_p)
{
	uint8_t i;

	for (i = 0; i < at_str_len - current_opt_cut; i++)
	{
		if (('=' == AT_str_temp.AT_cmd_str[current_opt_cut + i]) || ('?' == AT_str_temp.AT_cmd_str[current_opt_cut + i]) || ('\r' == AT_str_temp.AT_cmd_str[current_opt_cut + i]))
		{
			*param_p = i;
			return AT_STA_SUCCESS;
		}
	}

	return AT_STA_ERROR_CAN_NOT_FIND_PARAM_POINT;
}

static ATSta_t FindParamPoint_without_plus(uint8_t *param_p)
{
	uint8_t i;

	for (i = 0; i < at_str_len; i++)
	{
		if ('\r' == AT_str_temp.AT_cmd_str[current_opt_cut + i])
		{
			*param_p = i;
			return AT_STA_SUCCESS;
		}
	}

	return AT_STA_ERROR_CAN_NOT_FIND_PARAM_POINT;
}

static ATSta_t ATCmdNameGet(uint8_t *cmd_name_buf)
{
	uint8_t Param_point = 0;
	ATSta_t result;

	result = FindParamPoint(&Param_point);
	if (AT_STA_SUCCESS == result)
	{
		memcpy(cmd_name_buf, &AT_str_temp.AT_cmd_str[current_opt_cut], Param_point);
		current_opt_cut = current_opt_cut + Param_point;
	}

	return result;
}

static ATSta_t get_at_cmd_type(void)
{
	ATSta_t result = AT_STA_SUCCESS;

	switch (AT_str_temp.AT_cmd_str[current_opt_cut])
	{
	case '=':
		if ('?' == AT_str_temp.AT_cmd_str[current_opt_cut + 1])
			if('\r' == AT_str_temp.AT_cmd_str[current_opt_cut + 2] && 
			   '\n' == AT_str_temp.AT_cmd_str[current_opt_cut + 3])
			{
				current_opt_cut += 2;
				AT_str_temp.at_cmd_type = AT_TEST_CMD;
			}
			else
			{
				result = AT_STA_ERROR_PARAM_IVALID;
				AT_str_temp.at_cmd_type = AT_INVALID_CMD;
			}	
		else
		{
			current_opt_cut += 1;
			AT_str_temp.AT_cmd_param = &AT_str_temp.AT_cmd_str[current_opt_cut];
			AT_str_temp.at_cmd_type = AT_WRITE_CMD;
		}
		
		break;

	case '?':
		//current_opt_cut += 1;
		//AT_str_temp.at_cmd_type = AT_READ_CMD;

		if ('\r' == AT_str_temp.AT_cmd_str[current_opt_cut + 1] && 
			'\n' == AT_str_temp.AT_cmd_str[current_opt_cut + 2])
		{
			current_opt_cut += 1;
			AT_str_temp.at_cmd_type = AT_READ_CMD;
		}
		else
		{
			result = AT_STA_ERROR_PARAM_IVALID;
			AT_str_temp.at_cmd_type = AT_INVALID_CMD;
		}
		
		break;

	case '\r':
		if ('\n' == AT_str_temp.AT_cmd_str[current_opt_cut + 1])
			AT_str_temp.at_cmd_type = AT_EXECUT_CMD;
		else
		{
			result = AT_STA_ERROR_PARAM_IVALID;
			AT_str_temp.at_cmd_type = AT_INVALID_CMD;
		}
		break;

	default:
		result = AT_STA_ERROR_PARAM_IVALID;
		AT_str_temp.at_cmd_type = AT_INVALID_CMD;
		break;
	}

	return result;
}

static ATSta_t GetCMDIndex(uint8_t *cmd_name, uint8_t *cmd_index)
{
	uint8_t i;

	for (i = 0; i < get_cmd_handler_number(); i++)
	{
		if (0 == strcmp((const char *)cmd_name, (const char *)(&cmd_handler[i])))
		{
			*cmd_index = i;
			return AT_STA_SUCCESS;
		}
	}

	return AT_STA_ERROR_NOT_SUPPORT_CMD;
}

static void AT_print_cmdStr_info(void)
{
	at_printf("cmd string:%s", (char *)AT_str_temp.AT_cmd_str);
	at_printf("cmd name:%s\r\n", cmd_name_tmp);
	at_printf("cmd type:%d\r\n", AT_str_temp.at_cmd_type);
	if (AT_WRITE_CMD == AT_str_temp.at_cmd_type)
	{
		at_printf("cmd param:%s\r\n", AT_str_temp.AT_cmd_param);
	}
}

static ATSta_t ATCMDLineAnalyzer(void)
{
	uint8_t cmd_index = 0;
	ATSta_t result;

	at_debug_assert((('A' == AT_str_temp.AT_cmd_str[0]) && ('T' == AT_str_temp.AT_cmd_str[1])));

	if ('+' == AT_str_temp.AT_cmd_str[2])
	{
		current_opt_cut = 3;
		result = ATCmdNameGet(cmd_name_tmp);
	}
	else //AT cmd without '+'
	{
		current_opt_cut = 0;
		result = FindParamPoint_without_plus(&current_opt_cut);
		strcpy((char*)cmd_name_tmp, (const char*)AT_str_temp.AT_cmd_str);
		cmd_name_tmp[strlen((char*)cmd_name_tmp) - 2] = '\0'; //add end of string
	}

	if (AT_STA_SUCCESS == result)
	{
		result = GetCMDIndex(cmd_name_tmp, &cmd_index);
	}
	if (AT_STA_SUCCESS == result)
	{
		result = get_at_cmd_type();
	}
	if (AT_STA_SUCCESS == result)
	{
		AT_print_cmdStr_info();
		cmd_handler[cmd_index].cmd_handler(&AT_str_temp);
	}

	return result;
}

ATSta_t AT_CMD_process(char *at_cmd_str)
{
	ATSta_t result;

	result = GetATCmdStr(at_cmd_str);
	if (AT_STA_SUCCESS == result)
	{
		//at_printf("src cmd string:%s", (char *)AT_str_temp.AT_cmd_str);
		ATCharUpper(AT_str_temp.AT_cmd_str);
		result = RemoveInvalidChar();
	}
	if (AT_STA_SUCCESS == result)
	{
		result = ATCMDLineAnalyzer();
	}
	if (AT_STA_SUCCESS != result)
	{
		AT_RSP_process("ERR:%d\r\n", result);
	}

	return result;
}

void AT_Module_Init(void)
{
	AT_String_temp_init();
}
