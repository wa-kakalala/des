#include "des_key.h"
#include "des_calc.h"
#include <time.h>
#include <stdlib.h>

int main() {
	srand(time(0));
	unsigned char key[64] = {0};
	unsigned char data[64] = {0};
	for( int i=0;i<64;i++){
		key[i] = (i%2 == 0 ) ? 1:0;
		data[i] = rand() % 2 ;
	}

	// for(int i=63;i>=0;i--){
	// 	printf("%d",data[i]);
	// }
	// printf("\r\n");


	initial_permutation(data);
	unsigned char * ext_data = select_extension();
	unsigned char * xor_data;
	unsigned char * s_data;

	for( int idx = 0; idx < 16; idx++){
		xor_data = xor_key(ext_data, key,idx);
		for( int i=47;i>=0;i--){
			printf("%d",xor_data[i]);
		}
		printf("\r\n");
		s_data = select_s(xor_data);
		for( int i=31;i>=0;i--){
			printf("%d",s_data[i]);
		}
		printf("\r\n");
	}
	
	return 0;
}
