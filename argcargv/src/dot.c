//-------| src/dot.c |-------//
#include "dot.h"


static unsigned short dot_decimal[10][MAX_DOT] = {
	{0x7F, 0x41, 0x41, 0x41, 0x7F}, // 0
	{0x00, 0x00, 0x7F, 0x00, 0x00}, // 1
	{0x4F, 0x49, 0x49, 0x49, 0x79}, // 2
	{0x49, 0x49, 0x49, 0x49, 0x7F}, // 3
	{0x78, 0x08, 0x08, 0x7F, 0x08}, // 4
	{0x79, 0x49, 0x49, 0x49, 0x4F}, // 5
	{0x7F, 0x49, 0x49, 0x49, 0x4F}, // 6
	{0x40, 0x40, 0x40, 0x40, 0x7F}, // 7
	{0x7F, 0x49, 0x49, 0x49, 0x7F}, // 8
	{0x78, 0x48, 0x48, 0x48, 0x7F}  // 9
};
static unsigned short dot_E[MAX_DOT] = {
	0x7F, 0x49, 0x49, 0x49, 0x49	// E
};


static short *dot[MAX_DOT];

void init_dot(short *address[])
{
	int i;
	for(i = 0; i < MAX_DOT; i++) {
		dot[i] = address[i];
	}
}

void dot_clear()
{
	int i;
	for(i = 0; i < MAX_DOT; i++){
		*dot[i] = 0;
	}
	usleep(0); // for Ximulator
}

void dot_write(int decimal)
{
	int i;
	for(i = 0; i < MAX_DOT; i++){
		*dot[i] = dot_decimal[decimal][i];
	}
	usleep(0); // for Ximulator
}

void dot_up_shift(int decimal)
{
	int shift, i;
	for(shift = 0; shift <= 7; shift++) {
		for(i = 0; i < MAX_DOT; i++){
			*dot[i] = dot_decimal[decimal][i] << shift;
		}
		usleep(50000);
	}
}

void dot_down_shift(int decimal)
{
	int shift, i;
	for(shift = 0; shift <= 7; shift++) {
		for(i = 0; i < MAX_DOT; i++){
			*dot[i] = dot_decimal[decimal][i] >> shift;
		}
		usleep(50000);
	}
}

void dot_inverse(int decimal)
{
	int shift, i;
	for(shift = 0; shift < 3; shift++) {
		for(i = 0; i < MAX_DOT; i++){
			*dot[i] = dot_decimal[decimal][i];
		}
		usleep(300000);
		for(i = 0; i < MAX_DOT; i++){
			*dot[i] = ~dot_decimal[decimal][i];
		}
		usleep(300000);
	}
	dot_clear();
}

void dot_error()
{
	int i;
	for(i = 0; i < MAX_DOT; i++) {
		*dot[i] = dot_E[i];
	}
}

