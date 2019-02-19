/*
 * File: at_debug.h
 * Brief:
 * -----
 * File Created: Monday, 11th February 2019 5:45:30 pm
 * Author: ldj
 * -----
 * Last Modified: Tuesday, 12th February 2019 9:42:27 am
 * Modified By: ldj
 * -----
 * Copyright (c) 2019
 */


#ifndef __AT_DEBUG_H__
#define __AT_DEBUG_H__

#define AT_DEBUG_EN 1

#if AT_DEBUG_EN
#define at_printf printf
#define at_debug_assert(x) while(!x);
#else
#define at_printf(...) 
#endif

#endif
