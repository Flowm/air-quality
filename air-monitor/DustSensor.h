#pragma once

#include "Wire.h"

#define PULSE_BUFFER_LEN 1024

class DustSensor {
	public:
		DustSensor(int pin);

		void enable(void (*isr_wrap)());
		void reset();
		void isr();

		uint32_t getCount();
		float getLPO();

	private:
		int pin;
		uint8_t state;
		unsigned long start_time;
		unsigned long pulses[PULSE_BUFFER_LEN] = {0};
		uint16_t count = 0;
		unsigned long pulse_start = 0;
};
