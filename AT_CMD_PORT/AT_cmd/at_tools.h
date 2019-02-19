/*
 * File: at_tools.h
 * Brief:
 * -----
 * File Created: Monday, 11th February 2019 5:50:48 pm
 * Author: ldj
 * -----
 * Last Modified: Tuesday, 12th February 2019 9:43:39 am
 * Modified By: ldj
 * -----
 * Copyright (c) 2019
 */


#ifndef __AT_TOOLS_H__
#define __AT_TOOLS_H__

void ATCharUpper(uint8_t *at_string);
char hex2char(uint8_t data);
char *itoa(int num, char *str, int radix);

#endif
