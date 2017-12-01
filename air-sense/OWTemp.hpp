#pragma once

#include <OneWire.h>

class OWTemp {
public:
	OWTemp(int pin) : ds(pin) {}

	void search(void);
	float get(void);


private:
	OneWire ds;
	byte data[12];
	byte addr[8];
	byte type_s;
};
