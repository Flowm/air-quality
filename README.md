# Air Quality monitor
Implementation of an affordable indoor air quality monitor using various sensors connected to a microcontroller and streaming the data to a Raspberry Pi for analysis using [Node-RED](http://nodered.org/).

![Dashboard]

## Architecture

## Sensing Unit (air-sense)
In the sensing unit a [Teensy] microcontroller reads the sensor data from the connected sensors and sends it over the attached Bluetooth BLE module.

### Hardware
The following sensors are used:

| Category            | Name                 | Provides                             | Price |
|---------------------|----------------------|--------------------------------------|------:|
| Core                | [Teensy 3.2][Teensy] | Microcontroller                      |  ~24€ |
| Communication       | [HM-11]              | Bluethooth                           |   ~5€ |
| Sensors             | [BME280]             | Temperature, Pressure, Humidity      |  ~14€ |
| Sensors             | [iAQ-core C]         | VOC Sensor                           |  ~33€ |
| Sensors (optional)  | [MQ135]              | Gas                                  |   ~2€ |
| Sensors (optional)  | [SM-PWM-01C]         | Dust Sensor                          |  ~14€ |
| Sensors (NA)        | [BME680]             | Temperature, Pressure, Humidity, VOC |    NA |

### Wiring
A Fritzing sketch documenting the layout of the current hardware prototype is located in `air-sense/wiring`.


## Processing unit (air-pi)
This unit was installed and tested on a [Raspberry Pi 3], running Debian Jessie.
The purpose of this unit is to process all the data received via Bluetooth from the sensing unit and compute the current air quality index, based on the latest measurements.
This unit is also configured to display the current status, as well as triggering real-time notifications in case the air quality gets worse.

### Hardware
Besides the Raspberry Pi an additional Bluetooth BLE module is used to receive the data from wirelessly connected sensing units.

| Category       | Name                  | Price |
|----------------|-----------------------|------:|
| Core           | [Raspberry Pi 3]      | ~40€  |
| Comm           | [HM-11]               |  ~5€  |
| LED (optional) | [WS2812 RGB LED Ring] |  ~7€  |

The HM-11 BLE module is connected to the serial port of the Raspberry Pi:
- [TXD](http://pinout.xyz/pinout/pin8_gpio14)
- [RXD](http://pinout.xyz/pinout/pin10_gpio15)

The Neopixel LED ring can be additionally connected to the Raspberry Pi to indicate the current air quality directly on the processing unit.
- VCC (any)
- GND (any)
- [BCM 18](https://pinout.xyz/pinout/pin12_gpio18) (pin 12) for providing input to the LED

### Installation
Raspberry Pi 3 comes with a pre-installed version of Node-RED.
Additionally, the following node modules are used:
- [node-red-node-sqlite](https://www.npmjs.com/package/node-red-node-sqlite)
- [node-red-contrib-telegrambot](https://github.com/windkh/node-red-contrib-telegrambot)
- [node-red-dashboard](https://github.com/node-red/node-red-dashboard)
- [node-red-node-pi-neopixel](https://www.npmjs.com/package/node-red-node-pi-neopixel)
(for controlling the neopixel LEDs, an additional library needs to be installed. This can be done by following the instructions on the npmjs or github page of this module)

All the required flows needed for running the application can be found inside the `air-pi/node-red` folder.
These flows can be easily imported via the web-based GUI provided by Node-RED.


[Dashboard]: https://cloud.githubusercontent.com/assets/1117666/21831099/b9782bfa-d7a1-11e6-8d5f-f32e0b3c3636.png
[Teensy]: https://www.pjrc.com/teensy
[HM-11]: http://wiki.seeed.cc/Bluetooth_V4.0_HM_11_BLE_Module
[BME280]: https://www.bosch-sensortec.com/bst/products/all_products/bme280
[BME680]: https://www.bosch-sensortec.com/bst/products/all_products/bme680
[iAQ-core C]: http://ams.com/eng/Products/Environmental-Sensors/Air-Quality-Sensors/iAQ-core-C
[MQ135]: https://www.olimex.com/Products/Components/Sensors/SNS-MQ135
[SM-PWM-01C]: http://www.amphenol-sensors.com/en/component/edocman/3-co2/4-co2-modules/194-sm-pwm-01c
[Raspberry Pi 3]: https://www.raspberrypi.org/products/raspberry-pi-3-model-b
[WS2812 RGB LED Ring]: http://www.watterott.com/de/WS2812B-RGB-Ring-8
