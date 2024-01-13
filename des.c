#include <stdlib.h>
#include <time.h>
#include "des_key.h"
#include "des_calc.h"

int main() {
	unsigned char key[64]  = {0};
	unsigned char data[64] = {0};
	char * key_str  = "1010101110101011101010111010101110101011101010111010101110101011";
	// char * data_str = "1111011101001010010000011010001010111011010111100001010111011111";
	char * data_str = "0110110011101111101101101000010011110010111100000111111110111001";
	
	for(int i=0;i<64;i++){
		data[i] = data_str[i]-'0';
		key[i]  = key_str[i]-'0';
	}

	printf("key: ");
	for(int i=0;i<64;i++) {
		printf("%d",key[i]);	
	}
	printf("\r\n");

	printf("------------------------\r\n");
	printf("encryption:\r\n");
	printf("- data  : ");
	for(int i=0;i<64;i++) {
		printf("%d",data[i]);	
	}
	printf("\r\n");
	unsigned char * res = des(data,key,0);
	if( res == NULL ){
		printf("the key is error \r\n");
	} else {
		printf("- result: ");
		for(int i=0;i<64;i++) {
			printf("%d",res[i]);
		}
	}
	printf("\r\n");
	printf("------------------------\r\n");
	printf("decryption:\r\n");
	printf("- data  : ");
	for(int i=0;i<64;i++) {
		printf("%d",res[i]);	
	}
	printf("\r\n");
	res = des(res,key,1);
	if( res == NULL ){
		printf("the key is error \r\n");
	} else {
		printf("- result: ");
		for(int i=0;i<64;i++) {
			printf("%d",res[i]);
		}
	}
	printf("\r\n");
	return 0;
}
