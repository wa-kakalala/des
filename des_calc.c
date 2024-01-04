#include "des_calc.h"

unsigned char left_data [32] = {0};
unsigned char right_data[32] = {0};
unsigned char ext_data  [48] = {0};

//初始置换表
const static unsigned char ip_table[64] = {
	58 , 50 , 42 , 34 , 26 , 18 , 10 , 2 , 60 , 52 , 44 , 36 , 28 , 20 , 12 , 4 ,
	62 , 54 , 46 , 38 , 30 , 22 , 14 , 6 , 64 , 56 , 48 , 40 , 32 , 24 , 16 , 8 ,
	57 , 49 , 41 , 33 , 25 , 17 , 9 , 1 , 59 , 51 , 43 , 35 , 27 , 19 , 11 , 3 ,
	61 , 53 , 45 , 37 , 29 , 21 , 13 , 5 , 63 , 55 , 47 , 39 , 31 , 23 , 15 , 7
};

//扩展置换，将数据从32位扩展为48位
static const unsigned char expa_perm[48] = {
	32 , 1  , 2  , 3  , 4  , 5  , 4  , 5  , 6  , 7  , 8  , 9  , 8  , 9  , 10 , 11 ,
	12 , 13 , 12 , 13 , 14 , 15 , 16 , 17 , 16 , 17 , 18 , 19 , 20 , 21 , 20 , 21 ,
	22 , 23 , 24 , 25 , 24 , 25 , 26 , 27 , 28 , 29 , 28 , 29 , 30 , 31 , 32 , 1
} ;

// ip
void initial_permutation(unsigned char * data){
    unsigned char idx;
    for(idx = 0;idx<32;idx ++){
        left_data[idx] = data[ip_table[idx]-1];
    }
    for(idx = 0;idx<32;idx ++){
        right_data[idx] = data[ip_table[idx+32]-1];
    }
}

unsigned char * select_extension(){
    unsigned char idx;
    int i;
    for( i = 31;i>=0;i--){
        printf("%d",right_data[i]);
    }
    printf("\r\n");
    for( idx = 0;idx<48;idx++){
        ext_data[idx] = right_data[expa_perm[idx]-1];
    }
    return ext_data;
}
