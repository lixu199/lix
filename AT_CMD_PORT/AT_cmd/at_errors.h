/*
 * File: at_errors.h
 * Brief:
 * -----
 * File Created: Monday, 11th February 2019 5:32:01 pm
 * Author: ldj
 * -----
 * Last Modified: Tuesday, 12th February 2019 9:44:12 am
 * Modified By: ldj
 * -----
 * Copyright (c) 2019
 */


#ifndef __AT_ERRORS_H__
#define __AT_ERRORS_H__

#define ATSta_t uint32_t 

#define AT_STA_SUCCESS 0
#define AT_STA_FAIL 1

#define AT_STA_ERROR_LEN_SHORT 2
#define AT_STA_ERROR_CAN_NOT_FIDN_END_CHAR 3
#define AT_STA_ERROR_CAN_NOT_FIND_HEADER_CHAR 4
#define AT_STA_ERROR_CAN_NOT_FIND_PARAM_POINT 5
#define AT_STA_ERROR_NOT_SUPPORT_CMD 6
#define AT_STA_ERROR_PARAM_IVALID 7

#define AT_STA_CODE_MAX AT_STA_ERROR_NOT_SUPPORT_CMD

#endif
