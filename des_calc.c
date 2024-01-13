#include "des_calc.h"

unsigned char left_data [32] = {0};
unsigned char right_data[32] = {0};
unsigned char ext_data  [48] = {0};
unsigned char xor48_data[48] = {0};
unsigned char s_data    [32] = {0};
unsigned char p_data    [48] = {0};
unsigned char xor32_data[32] = {0};
unsigned char res_data  [64] = {0};

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

//S盒子代替
const static unsigned char sbox[8][64] = {
{//S1盒子
    14 , 4 , 13 , 1 , 2 , 15 , 11 , 8 , 3 , 10 , 6 , 12 , 5 , 9 , 0 , 7 ,
    0 , 15 , 7 , 4 , 14 , 2 , 13 , 1 , 10 , 6 , 12 , 11 , 9 , 5 , 3 , 8 ,
    4 , 1 , 14 , 8 , 13 , 6 , 2 , 11 , 15 , 12 , 9 , 7 , 3 , 10 , 5 , 0 ,
    15 , 12 , 8 , 2 , 4 , 9 , 1 , 7 , 5 , 11 , 3 , 14 , 10 , 0 , 6 , 13
} ,
{//S2盒子
    15 , 1 , 8 , 14 , 6 , 11 , 3 , 4 , 9 , 7 , 2 , 13 , 12 , 0 , 5 , 10 ,
    3 , 13 , 4 , 7 , 15 , 2 , 8 , 14 , 12 , 0 , 1 , 10 , 6 , 9 , 11 , 5 ,
    0 , 14 , 7 , 11 , 10 , 4 , 13 , 1 , 5 , 8 , 12 , 6 , 9 , 3 , 2 , 15 ,
    13 , 8 , 10 , 1 , 3 , 15 , 4 , 2 , 11 , 6 , 7 , 12 , 0 , 5 , 14 , 9
} ,
{//S3盒子
    10 , 0 , 9 , 14 , 6 , 3 , 15 , 5 , 1 , 13 , 12 , 7 , 11 , 4 , 2 , 8 ,
    13 , 7 , 0 , 9 , 3 , 4 , 6 , 10 , 2 , 8 , 5 , 14 , 12 , 11 , 15 , 1 ,
    13 , 6 , 4 , 9 , 8 , 15 , 3 , 0 , 11 , 1 , 2 , 12 , 5 , 10 , 14 , 7 ,
    1 , 10 , 13 , 0 , 6 , 9 , 8 , 7 , 4 , 15 , 14 , 3 , 11 , 5 , 2 , 12
} ,
{//S4盒子
    7 , 13 , 14 , 3 , 0 , 6 , 9 , 10 , 1 , 2 , 8 , 5 , 11 , 12 , 4 , 15 ,
    13 , 8 , 11 , 5 , 6 , 15 , 0 , 3 , 4 , 7 , 2 , 12 , 1 , 10 , 14 , 9 ,
    10 , 6 , 9 , 0 , 12 , 11 , 7 , 13 , 15 , 1 , 3 , 14 , 5 , 2 , 8 , 4 ,
    3 , 15 , 0 , 6 , 10 , 1 , 13 , 8 , 9 , 4 , 5 , 11 , 12 , 7 , 2 , 14
} ,
{//S5盒子
    2 , 12 , 4 , 1 , 7 , 10 , 11 , 6 , 8 , 5 , 3 , 15 , 13 , 0 , 14 , 9 ,
    14 , 11 , 2 , 12 , 4 , 7 , 13 , 1 , 5 , 0 , 15 , 10 , 3 , 9 , 8 , 6 ,
    4 , 2 , 1 , 11 , 10 , 13 , 7 , 8 , 15 , 9 , 12 , 5 , 6 , 3 , 0 , 14 ,
    11 , 8 , 12 , 7 , 1 , 14 , 2 , 13 , 6 , 15 , 0 , 9 , 10 , 4 , 5 , 3
} ,
{//S6盒子
    12 , 1 , 10 , 15 , 9 , 2 , 6 , 8 , 0 , 13 , 3 , 4 , 14 , 7 , 5 , 11 ,
    10 , 15 , 4 , 2 , 7 , 12 , 9 , 5 , 6 , 1 , 13 , 14 , 0 , 11 , 3 , 8 ,
    9 , 14 , 15 , 5 , 2 , 8 , 12 , 3 , 7 , 0 , 4 , 10 , 1 , 13 , 11 , 6 ,
    4 , 3 , 2 , 12 , 9 , 5 , 15 , 10 , 11 , 14 , 1 , 7 , 6 , 0 , 8 , 13
} ,
{//S7盒子
    4 , 11 , 2 , 14 , 15 , 0 , 8 , 13 , 3 , 12 , 9 , 7 , 5 , 10 , 6 , 1 ,
    13 , 0 , 11 , 7 , 4 , 9 , 1 , 10 , 14 , 3 , 5 , 12 , 2 , 15 , 8 , 6 ,
    1 , 4 , 11 , 13 , 12 , 3 , 7 , 14 , 10 , 15 , 6 , 8 , 0 , 5 , 9 , 2 ,
    6 , 11 , 13 , 8 , 1 , 4 , 10 , 7 , 9 , 5 , 0 , 15 , 14 , 2 , 3 , 12
} ,
{//S8盒子
    13 , 2 , 8 , 4 , 6 , 15 , 11 , 1 , 10 , 9 , 3 , 14 , 5 , 0 , 12 , 7 ,
    1 , 15 , 13 , 8 , 10 , 3 , 7 , 4 , 12 , 5 , 6 , 11 , 0 , 14 , 9 , 2 ,
    7 , 11 , 4 , 1 , 9 , 12 , 14 , 2 , 0 , 6 , 10 , 13 , 15 , 3 , 5 , 8 ,
    2 , 1 , 14 , 7 , 4 , 10 , 8 , 13 , 15 , 12 , 9 , 0 , 3 , 5 , 6 , 11
}   
};

//P盒置换
const static unsigned char p_table[32] = {
	16 , 7 , 20 , 21 , 29 , 12 , 28 , 17 , 1 , 15 , 23 , 26 , 5 , 18 , 31 , 10 ,
	2 , 8 , 24 , 14 , 32 , 27 , 3 , 9 , 19 , 13 , 30 , 6 , 22 , 11 , 4 , 25
} ;

//置换  
const static unsigned char invp_table[64] = {
	40 , 8 , 48 , 16 , 56 , 24 , 64 , 32 , 39 , 7 , 47 , 15 , 55 , 23 , 63 , 31 ,
	38 , 6 , 46 , 14 , 54 , 22 , 62 , 30 , 37 , 5 , 45 , 13 , 53 , 21 , 61 , 29 ,
	36 , 4 , 44 , 12 , 52 , 20 , 60 , 28 , 35 , 3 , 43 , 11 , 51 , 19 , 59 , 27 ,
	34 , 2 , 42 , 10 , 50 , 18 , 58 , 26 , 33 , 1 , 41 , 9 , 49 , 17 , 57 , 25
} ;

// ip
void initial_permutation(unsigned char * data){
    unsigned char idx;
    for(idx = 0;idx<32;idx ++){
        right_data[idx] = data[ip_table[idx]-1];
    }
    for(idx = 0;idx<32;idx ++){
        left_data[idx] = data[ip_table[idx+32]-1];
    }
}

unsigned char * select_extension(){
    unsigned char idx;
    int i;
    for( idx = 0;idx<48;idx++){
        ext_data[idx] = right_data[expa_perm[idx]-1];
    }

    return ext_data;
}

unsigned char * xor_48(unsigned char * ext_data, unsigned char* key, unsigned char key_idx ){
    unsigned char * key_data= generate_key(key,key_idx);
    unsigned char idx;
    for( idx=0;idx<48;idx++){
        xor48_data[idx] = (key_data[idx] + ext_data[idx]) %2;
    }

    return xor48_data;
}

unsigned char * select_s(unsigned char * x_data) {
    unsigned char idx;
    unsigned row;
    unsigned col;
    unsigned res;
    unsigned s_idx=0;
    for( idx = 0;idx<48;idx+=6){
        row = x_data[idx+5]*2 + x_data[idx];
        col = x_data[idx+4]*8 + x_data[idx+3]*4 + x_data[idx+2]*2+x_data[idx+1];
        res = sbox[idx/6][row*16+col];
        s_data[s_idx++] = (res >> 0) & 0x01;
        s_data[s_idx++] = (res >> 1) & 0x01;
        s_data[s_idx++] = (res >> 2) & 0x01;
        s_data[s_idx++] = (res >> 3) & 0x01;
    }
    return s_data;
}

unsigned char * permutation(unsigned char * s_data){
    unsigned char idx; 
    for( idx = 0;idx<32;idx++){
        p_data[idx] = s_data[p_table[idx]-1];
    }
    return p_data;
}

void xor_32(unsigned char* left_data,unsigned char*right_data){
    unsigned char idx;
    for( idx=0;idx<32;idx++){
        xor32_data[idx] = (left_data[idx] + right_data[idx]) %2;
    }
}

unsigned char * invinit_permutation(unsigned char * left_data,unsigned char*right_data){
    unsigned char idx; 
    unsigned char new_idx;
    for( idx = 0;idx<64;idx++){
        new_idx = invp_table[idx]-1;
        if( new_idx >= 32 ) {
            res_data[idx] = right_data[new_idx-32];
        }else {
            res_data[idx] = left_data[new_idx];
        }
    }
    return res_data;
}

unsigned char check_key(unsigned char *key){
    unsigned char idx;
    unsigned char count=0;
    for( idx =0;idx<64;idx++){
        count += key[idx];
        if( (idx+1) %8 == 0) {
            if(count % 2 != 1) return 0;
            count = 0;
        }
    }
    return 1;
}

/**
 * @bref: des encryption or decryption
 * @param data : the data to encrypt or decrypt
 * @param key  : the key 
 * @param mode : the mode  0-> encrypt 1-> decrypt
 * @return     : if key is error -> NULL , else result of des
*/
unsigned char * des(unsigned char* data, unsigned char*key,unsigned char mode){
    initial_permutation(data);
    unsigned char idx;
    unsigned char index;
    if(!check_key(key)) return NULL;
    for(idx =0;idx<16;idx++){
        xor_32(
            left_data, 
            permutation(
                select_s(
                    xor_48(
                        select_extension(),
                        key,
                        (mode==1)?15-idx:idx
                    )
                )
            )
        );
        for(index = 0;index<32;index++){
            left_data[index] = right_data[index];
            right_data[index]= xor32_data[index];
        }
    }
    return invinit_permutation(left_data,right_data);
}

