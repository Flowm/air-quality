#ifdef ARDUINO_ARCH_SAMD
#include "BluefruitController.hpp"

void error(const char * err) {
  Serial.println(F(err));
  Serial.println();
}

void BluefruitController::setup() {
  if ( !ble.begin(VERBOSE_MODE) ){
    error("Couldn't start Bluefruit. Check wiring?");
  }
  if (BLUEFRUIT_FACTORY_RESET) {
    factoryReset();
  }
  setName(BLUEFRUIT_DEVICE_NAME);
  if (BLUEFRUIT_BEACON_ENABLED) {
    iBeacon(MANUFACTURER_APPLE, BEACON_UUID, BEACON_MAJOR, BEACON_MINOR, BEACON_RSSI_1M);
  }
  ble.reset();
}

void BluefruitController::reset() {
  if (!ble.reset()) {
    error("Couldn't reset Bluefruit!");
  }
}

void BluefruitController::factoryReset() {
  if (!ble.factoryReset()) {
    error("Couldn't factory reset");
  }

  ble.echo(false);
  ble.info();
}

void BluefruitController::setName(const char * name) {
  ble.print("AT+GAPDEVNAME=");
  ble.print(name);
  ble.println();

  if (!ble.waitForOK()) {
    error("Couldn't change the name of the Bluetooth controller!");
  }
}

void BluefruitController::getAddress(char * buffer) {
  ble.println("AT+BLEGETADDR");
  ble.readline();
  if (strcmp("ERROR", ble.buffer) != 0) {
    strncpy(buffer, ble.buffer, 20);
  } else {
    memset(buffer, 0, 20);
  }
}

void BluefruitController::getPeerAddress(char * buffer) {
  ble.println("AT+BLEGETPEERADDR");
  ble.readline();
  if (strcmp("ERROR", ble.buffer) != 0) {
    strncpy(buffer, ble.buffer, 20);
  } else {
    memset(buffer, 0, 20);
  }
}

bool BluefruitController::isConnectable() {
  ble.println("AT+GAPCONNECTABLE=?");
  ble.readline();
  int res = atoi(ble.buffer);
  return res == 1;
}

void BluefruitController::setConnectable(bool connectable) {
  ble.print("AT+GAPCONNECTABLE=");
  ble.print(connectable);
  ble.println();

  if (!ble.waitForOK()) {
    error("Couldn't set connectable mode");
  }
}

bool BluefruitController::isConnected() {
  return ble.isConnected();
}

void BluefruitController::iBeacon(uint16_t manufacturerId, const char * uuid, uint16_t major, uint16_t minor, uint8_t rssi) {
  ble.print("AT+BLEBEACON=" );
  ble.print(manufacturerId  ); ble.print(',');
  ble.print(uuid            ); ble.print(',');
  ble.print(major           ); ble.print(',');
  ble.print(minor           ); ble.print(',');
  ble.print(rssi            );
  ble.println();

  if (!ble.waitForOK()) {
    error("Couldn't start iBeacon!");
  }
}

void BluefruitController::eddystone() {
  //TODO: implement
  error("eddystone function is not implemented");
}

void BluefruitController::advertise(bool enable) {
  if (enable) {
    ble.println("AT+GAPSTARTADV");
  } else {
    ble.println("AT+GAPSTOPADV");
  }
  if (!ble.waitForOK()) {
    error("Couldn't force advertising!");
  }
}

void BluefruitController::addService(uint16_t uuid) {
  char service [32] = {0};
  int32_t serviceId = 0;
  snprintf(service, 31, "AT+GATTADDSERVICE=UUID=%#x", uuid);
  Serial.println(service);
  if (!ble.sendCommandWithIntReply(service, &serviceId)) {
    error("Couldn't setup service!");
  }
}

void BluefruitController::addService(const char * uuid) {
  char service [32] = {0};
  int32_t serviceId = 0;
  snprintf(service, 31, "AT+GATTADDSERVICE=UUID=0x%s", uuid);
  Serial.println(service);
  if (!ble.sendCommandWithIntReply(service, &serviceId)) {
    error("Couldn't setup service!");
  }
}

uint32_t BluefruitController::addCharacteristic(const char * uuid, uint8_t properties, uint8_t minLength, uint8_t maxLength) {
  char characteristic [96] = {0};
  int32_t charId = 0;
  snprintf(characteristic, 95, "AT+GATTADDCHAR=UUID=%s, PROPERTIES=%#x, MIN_LEN=%u, MAX_LEN=%u", uuid, properties, minLength, maxLength);
  Serial.println(characteristic);
  if (!ble.sendCommandWithIntReply(characteristic, &charId)) {
    error("Couldn't setup characteristic!");
  }
  return charId;
}

uint32_t BluefruitController::addCharacteristic(uint16_t uuid, uint8_t properties, uint8_t minLength, uint8_t maxLength) {
  char characteristic [96] = {0};
  int32_t charId = 0;
  snprintf(characteristic, 95, "AT+GATTADDCHAR=UUID=%#x, PROPERTIES=%#x, MIN_LEN=%u, MAX_LEN=%u, DATATYPE=1", uuid, properties, minLength, maxLength);
  Serial.println(characteristic);
  if (!ble.sendCommandWithIntReply(characteristic, &charId)) {
    error("Couldn't setup characteristic!");
  }
  return charId;
}

void BluefruitController::setCharacteristic(uint32_t charId, const char * data) {
  // char preparedData[256] = {0};
  char output[21] = {0};
  // prepareData(data, preparedData);
  int i=0, j=0;
  while (data[i] != '\0') {
    output[j++] = data[i++];
    if (j >= 20 || data[i] == '\0') {
      output[j] = '\0';
      ble.print("AT+GATTCHAR=");
      ble.print(charId);
      ble.print(",");
      ble.println(output);
      j=0;
    }
  }
}

void BluefruitController::sendData(const char * data) {
  char output[256] = {0};
  int i=0, j=0;
  while (data[i] != '\0' && j < 240) { //240 max length allowed by bluetooth buffer
    if (data[i] == '\r') {
      output[j++] = '\\';
      output[j++] = 'r';
    } else if (data[i] == '\n') {
      output[j++] = '\\';
      output[j++] = 'n';
    } else {
      output[j++] = data[i];
    }
    i++;
  }
  ble.print("AT+BLEUARTTX=");
  ble.println(output);
}

#endif
