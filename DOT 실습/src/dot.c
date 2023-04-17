//-------| src/dot.c |-------//
#include "dot.h"


static unsigned short dot_decimal[10][MAX_DOT] = {
	{0x7f, 0x41, 0x41, 0x41, 0x7F}, // 0
	{0x00, 0x00, 0x7F, 0x00, 0x00}, // 1
	{    ,     ,     ,     ,     }, // 2
	{    ,     ,     ,     ,     }, // 3
	{    ,     ,     ,     ,     }, // 4
	{    ,     ,     ,     ,     }, // 5
	{    ,     ,     ,     ,     }, // 6
	{    ,     ,     ,     ,     }, // 7
	{    ,     ,     ,     ,     }, // 8
	{    ,     ,     ,     ,     }  // 9
};

static short * dot[MAX_DOT];

void init_dot(short * address[]) {
	int i;
	for( i=0; i<MAX_DOT; i++ ) {
		dot[i] = address[i];
	}
}

void dot_clear() {
	int i;
	for(i=0; i<MAX_DOT; i++){
		*dot[i] = 0;
	}
	usleep(0); // for Ximulator
}

void dot_write(int decimal) {
	int i;
	for(i=0; i<MAX_DOT; i++){
		*dot[i] = dot_decimal[decimal][i];
	}
	usleep(0); // for Ximulator
}

void dot_up_shift(int decimal) {
	int shift, i;
	for( shift=0; shift<=7; shift++ ) {
		for(i=0; i<MAX_DOT; i++){
			*dot[i] = dot_decimal[decimal][i] << shift;
		}
		usleep(50000);
	}
}

void dot_down_shift(int decimal) {
	int shift, i;
	for( shift=0; shift<=7; shift++ ) {
		for(i=0; i<MAX_DOT; i++){
			*dot[i] =
		}
		usleep(50000);
	}
}

void dot_inverse(int decimal) {
	int shift, i;
	for( shift=0; shift<3; shift++ ) {
		for(i=0; i<MAX_DOT; i++){
			*dot[i] = 
		}
		usleep(300000);
		for(i=0; i<MAX_DOT; i++){
			  *dot[i] =
		}
		usleep(300000);
	}
	dot_clear();
}
