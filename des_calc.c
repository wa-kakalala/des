#include "des_calc.h"

unsigned char left_data[ 32] = {0};
unsigned char right_data[32] = {0};

//初始置换表
const static unsigned char ip_table[64] = {
	58 , 50 , 42 , 34 , 26 , 18 , 10 , 2 , 60 , 52 , 44 , 36 , 28 , 20 , 12 , 4 ,
	62 , 54 , 46 , 38 , 30 , 22 , 14 , 6 , 64 , 56 , 48 , 40 , 32 , 24 , 16 , 8 ,
	57 , 49 , 41 , 33 , 25 , 17 , 9 , 1 , 59 , 51 , 43 , 35 , 27 , 19 , 11 , 3 ,
	61 , 53 , 45 , 37 , 29 , 21 , 13 , 5 , 63 , 55 , 47 , 39 , 31 , 23 , 15 , 7
};

// ip
void initial_permutation(unsigned char * data){
    unsigned char idx;
    for(idx = 0;idx<32;idx ++){
        left_data[idx] = data[ip_table[idx]-1];
    }
    for(idx = 0;idx<32;idx ++){
        right_data[idx] = data[ip_table[idx+32]-1];
    }

    for( idx = 32;idx > 0;idx--){
        printf("%d",left_data[idx-1]);
    }
    for( idx = 32;idx > 0;idx--){
        printf("%d",right_data[idx-1]);
    }

    printf("\r\n");
}
