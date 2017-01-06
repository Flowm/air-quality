#include "DustSensor.h"

DustSensor::DustSensor(int pin) : pin(pin) {
	pinMode(pin, INPUT);
}

void DustSensor::enable(void (*isr_wrap)()) {
	start_time = micros();
	state = digitalRead(pin);

	attachInterrupt(this->pin, isr_wrap, CHANGE);
}

void DustSensor::reset() {
	for (unsigned int i=0; i < PULSE_BUFFER_LEN; i++) {
		pulses[i] = 0;
	}

	count = 0;
	start_time = micros();
}

void DustSensor::isr() {
	uint8_t newstate = digitalRead(this->pin);

	if (state == 0 && newstate == 1) {
		pulse_start = micros();
	} else if (state == 1 && newstate == 0) {
		pulses[count++] = micros() - pulse_start;
		if (count > PULSE_BUFFER_LEN) {
			reset();
		}
	}
	state = newstate;
}

uint32_t DustSensor::getCount() {
	return count;
}

float DustSensor::getLPO() {
	unsigned long acc = 0;
	for (unsigned int i=0; i < count; i++) {
		acc += pulses[i];
	}
	float lpo = (float)acc / (micros() - start_time);

	return lpo;
}
