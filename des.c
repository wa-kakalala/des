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

	for( int i=47;i>=0;i--){
		printf("%d",ext_data[i]);
	}
	printf("\r\n");
	
	return 0;
}
