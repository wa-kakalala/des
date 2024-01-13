#ifndef _DES_CALC_H_
#define _DES_CALC_H_

#include <stdio.h>
#include "des_key.h"

unsigned char * des(unsigned char* data, unsigned char*key,unsigned char mode);
#endif