//-------| src/fnd.c |-------//
#include "fnd.h"

static unsigned short fnd_hexadecimal[16] = {
	0x3F, // 0
	0x06, // 1
	0x5B, // 2
	0x4F, // 3
	0x66, // 4
	0x6D, // 5
	0x7D, // 6
	0x07, // 7
	0x7F, // 8
	0x67, // 9
	0x77, // A
	0x7C, // b
	0x39, // C
	0x5E, // d
	0x79, // E
	0x71  // F
};

static short * fnd[MAX_FND];
int total = 0;

void init_fnd(short * address[]) {
	int i;
	for( i=0; i<MAX_FND; i++ ) {
		fnd[i] = address[i];
	}
}

void fnd_clear() {
	int i;
	for(i=0; i<MAX_FND; i++){
		*fnd[i] = 0;
	}
	usleep(0);
}

void fnd_all() {
	int i;
	for(i=0; i<MAX_FND; i++){
		*fnd[i] = 0xFF;
	}
}

void fnd_write(int hexadecimal, int fnd_num) {
	*fnd[fnd_num] = fnd_hexadecimal[hexadecimal];
}

void fnd_hexa_number(unsigned long number) {
	int i;
	for(i=0; i<MAX_FND; i++){
		fnd_write( (short)(number & 0xF), i);
		number = number >> 4;
	}
}

void fnd_add(){
	int i;
	int number;
	total = total + 10;
	number = total;
	for(i=0; i<7; i++){
		fnd_write(number % 10, i);
		number = number / 10;
	}
	usleep(10);
}

void fnd_subtract(){
	int i;
	int number;
	if(total>0){
	total = total - 2;
	number = total;
	for(i=0; i<7; i++){
		fnd_write(number % 10, i);
		number = number / 10;
		}
	}
	else{
	total = total;
	}
	usleep(10);
}

int fnd_total(){
	return total;
	}
