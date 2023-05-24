//-------| src/led.c |-------//
//먼저 초록불 주소만 on//
#include "led.h"

static short * led;

void init_led(short * address) {
	led = address;
}

void led_clear() {
	*led = (short)~0;
}

void led_green() {
	*led = (short)~0xAA;
}

void led_red() {
	*led = (short)~0x55;
}

void led_bit(int number) {
	*led = (short)~(number << 4);
}
