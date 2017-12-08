#include "SenDS18B20.hpp"

int SenDS18B20::init() {
    if (!ds.search(addr)) {
        Serial.println("No more addresses");
        ds.reset_search();
        return 1;
    }

    Serial.print("ROM =");
    for(int i = 0; i < 8; i++) {
        Serial.write(' ');
        Serial.print(addr[i], HEX);
    }

    if (OneWire::crc8(addr, 7) != addr[7]) {
        Serial.println("CRC is not valid!");
        return 1;
    }
    Serial.println();

    setId(IDSenDS18B20);
    return 0;
}

int SenDS18B20::read() {
    if (!getId()) {
        return 1;
    }
    ds.reset();
    ds.select(addr);
    ds.write(0x44, 1);

    delay(1000);

    ds.reset();
    ds.select(addr);
    ds.write(0xBE); // Read Scratchpad

    for (int i = 0; i < 9; i++) {
        data[i] = ds.read();
    }

    int16_t raw = (data[1] << 8) | data[0];
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms

    _temperature = (float)raw / 16.0;

    return 0;
}
