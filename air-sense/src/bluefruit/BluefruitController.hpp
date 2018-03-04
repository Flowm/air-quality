#pragma once

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
//#include "Adafruit_BLEGatt.h"

#include "BluefruitConfiguration.h"

#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif

/*=========================================================================
    APPLICATION SETTINGS

    FACTORYRESET_ENABLE       Perform a factory reset when running this sketch
   
                              Enabling this will put your Bluefruit LE module
                              in a 'known good' state and clear any config
                              data set in previous sketches or projects, so
                              running this at least once is a good idea.
   
                              When deploying your project, however, you will
                              want to disable factory reset by setting this
                              value to 0.  If you are making changes to your
                              Bluefruit LE device via AT commands, and those
                              changes aren't persisting across resets, this
                              is the reason why.  Factory reset will erase
                              the non-volatile memory where config data is
                              stored, setting it back to factory default
                              values.
       
                              Some sketches that require you to bond to a
                              central device (HID mouse, keyboard, etc.)
                              won't work at all with this feature enabled
                              since the factory reset will clear all of the
                              bonding data stored on the chip, meaning the
                              central device won't be able to reconnect.
    MINIMUM_FIRMWARE_VERSION  Minimum firmware version to have some new features
    MODE_LED_BEHAVIOUR        LED activity, valid options are
                              "DISABLE" or "MODE" or "BLEUART" or
                              "HWUART"  or "SPI"  or "MANUAL"
    -----------------------------------------------------------------------*/
     #define FACTORYRESET_ENABLE         1
     #define MINIMUM_FIRMWARE_VERSION    "0.6.7"
     #define MODE_LED_BEHAVIOUR          "MODE"
/*=========================================================================*/

class BluefruitController {
public:
  BluefruitController() {};
  void setup();
  void reset();
  void factoryReset();
  void getAddress(char * buffer);
  void getPeerAddress(char * buffer);
  void setName(const char * name);
  bool isConnectable();
  void setConnectable(bool connectable);
  bool isConnected();
  void iBeacon(uint16_t manufacturerId, const char * uuid, uint16_t major, uint16_t minor, uint8_t rssi);
  void eddystone();
  void advertise(bool enable);
  void addService(uint16_t uuid);
  void addService(const char * uuid);
  uint32_t addCharacteristic(uint16_t uuid, uint8_t properties, uint8_t minLength = 1, uint8_t maxLength = 20);
  uint32_t addCharacteristic(const char * uuid, uint8_t properties, uint8_t minLength = 1, uint8_t maxLength = 20);
  void setCharacteristic(uint32_t charId, const char * data);
  void sendData(const char * data);
private:
  Adafruit_BluefruitLE_SPI ble {BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST};
};
