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

void loop() {
	digitalWrite(LED_BUILTIN, LOW);

	ir_header();
	ir_byte(0xB8);
	ir_byte(0xFF); // key
	ir_post();
	ir_zero();

	digitalWrite(LED_BUILTIN, HIGH);
	delay(200);
}
