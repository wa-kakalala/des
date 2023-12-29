#include "des_key.h"

//密钥置换表，将64位密钥置换压缩置换为56位
const static unsigned char key_table_1[56] = {
	57 , 49 , 41 , 33 , 25 , 17 , 9 ,  1  ,
	58 , 50 , 42 , 34 , 26 , 18 , 10 , 2  ,
	59 , 51 , 43 , 35 , 27 , 19 , 11 , 3  ,
	60 , 52 , 44 , 36 , 63 , 55 , 47 , 39 ,
	31 , 23 , 15 , 7  , 62 , 54 , 46 , 38 ,
	30 , 22 , 14 , 6  , 61 , 53 , 45 , 37 ,
	29 , 21 , 13 , 5  , 28 , 20 , 12 , 4
} ;

//每轮移动的位数
const static unsigned char bit_shift[16] = {
	1 , 1 , 2 , 2 , 2 , 2 , 2 , 2 , 1 , 2 , 2 , 2 , 2 , 2 , 2 , 1
} ;

//压缩置换表，56位密钥压缩位48位密钥s
const static unsigned char key_table_2[48] = {
	14 , 17 , 11 , 24 , 1  , 5  , 3  , 28 ,
	15 , 6  , 21 , 10 , 23 , 19 , 12 , 4  ,
	26 , 8  , 16 , 7  , 27 , 20 , 13 , 2  ,
	41 , 52 , 31 , 37 , 47 , 55 , 30 , 40 ,
	51 , 45 , 33 , 48 , 44 , 49 , 39 , 56 ,
	34 , 53 , 46 , 42 , 50 , 36 , 29 , 32
} ;

unsigned char key_56 [56] = {0};
unsigned char key_48 [48] = {0};

unsigned char * generate_key(unsigned char* key, unsigned char key_idx) {
    unsigned char rotate_left = 0;
    for(unsigned char idx = 0 ; idx < 56 ; idx ++){
		key_56[idx] = key[key_table_1[idx] - 1] ;   //密钥置换
    }

    for(unsigned char idx = 0 ; idx <= key_idx ; idx ++){  //  shift nums
        rotate_left += bit_shift[idx];
	}

    for(unsigned char idx = 0 ; idx < 48 ; idx ++){   
        
        if( key_table_2[idx]-1 < 28 ){
            // printf("%d\t", (key_table_2[idx]-1-rotate_left+28) % 28 );
            key_48[idx] = key_56[ (key_table_2[idx]-1-rotate_left+28) % 28 ];
        }else{
            // printf("%d\t", (key_table_2[idx]-1-rotate_left ) % 28 + 28 );
            key_48[idx] = key_56[ (key_table_2[idx]-1-rotate_left ) % 28 + 28 ];
        }

        // if( (idx+1)%8 == 0 ) printf("\r\n");
        
	}
    return key_48;
}

