#ifndef _DES_CALC_H_
#define _DES_CALC_H_

#include <stdio.h>
#include "des_key.h"

void initial_permutation(unsigned char * data);
unsigned char * select_extension();
unsigned char * xor_key(unsigned char * ext_data, unsigned char* key, unsigned char key_idx );
unsigned char * select_s(unsigned char * x_data);
#endif