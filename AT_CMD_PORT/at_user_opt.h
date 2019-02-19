/*
 * File: at_user_opt.h
 * Brief:
 * -----
 * File Created: Tuesday, 12th February 2019 7:23:48 pm
 * Author: ldj
 * -----
 * Last Modified: Tuesday, 12th February 2019 7:23:49 pm
 * Modified By: ldj
 * -----
 * Copyright (c) 2019
 */

#ifndef __USER_OPT_H__
#define __USER_OPT_H__

#define AT_STR_TEST_AT        "AT\r\n"
#define AT_STR_TEST           "AT+TEST?\r\n"
#define AT_STR_READ   "AT+TEST=?\r\n"
#define AT_STR_WRITE  "AT+TEST=12,ab\r\n"
#define AT_STR_EXECUT "AT+TEST\r\n"
#define AT_STR_INVALID "ATTEST\r\n"

uint32_t get_cmd_handler_number(void);
#endif
