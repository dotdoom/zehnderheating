#include "Arduino.h"

#define LED_IR D2
#define CARRIER_FREQUENCY 455000

void ir_pulse(int length) {
#ifdef CARRIER_FREQUENCY
	// 50% duty cycle.
	analogWrite(LED_IR, 1);
	delayMicroseconds(length);
	analogWrite(LED_IR, 0);
#else
	digitalWrite(LED_IR, HIGH);
	delayMicroseconds(length);
	digitalWrite(LED_IR, LOW);
#endif
}

void ir_space(int length) {
	delayMicroseconds(length);
}

void ir_zero() {
	ir_pulse(30);
	ir_space(650);
}

void ir_one() {
	ir_pulse(30);
	ir_space(830);
}

void ir_header() {
	ir_pulse(30);
	ir_space(1000);
}

void ir_post() {
	ir_pulse(30);
	ir_space(460);
}

void ir_byte(char b) {
	for (int i = 0; i < 8; ++i) {
		if (b & 0b10000000) {
			ir_one();
		} else {
			ir_zero();
		}
		b = b << 1;
	}
}

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(LED_IR, OUTPUT);
#ifdef CARRIER_FREQUENCY
	analogWriteFreq(CARRIER_FREQUENCY);
	analogWriteRange(2);
	analogWrite(LED_IR, 1);
#endif
}

// https://sourceforge.net/p/lirc/mailman/lirc-list/thread/trinity-e7cf0040-4ca4-4304-95a6-510d69ba1c92-1521283664810%403c-app-gmx-bs47/#msg36265158
#define KEY_OFF 0x0D
#define KEY_1   0x86
#define KEY_2   0x95
#define KEY_3   0xA0
#define KEY_4   0xB3
#define KEY_5   0xCA
#define KEY_6   0xD9
#define KEY_7   0xEC
#define KEY_8   0xFF

void loop() {
	digitalWrite(LED_BUILTIN, LOW);

	ir_header();
	ir_byte(0xB8);
	ir_byte(KEY_8);
	ir_post();
	ir_zero();

	digitalWrite(LED_BUILTIN, HIGH);
	delay(200);
}
