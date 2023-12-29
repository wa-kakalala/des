#include "des_key.h"

int main() {
	unsigned char key[64] = {0};
	for( int i=0;i<64;i++){
		key[i] = (i%2 == 0 ) ? 1:0;
	}

	unsigned char * key48;
	for( int i=0;i<16;i++){
		key48 = generate_key(key,i);
	}
	
	return 0;
}
