# Air Quality monitor
Implementation of an affordable indoor air quality monitor using various sensors connected to a microcontroller and streaming the data to a Raspberry PI for analysis using [Node-RED](http://nodered.org/).

## Sensing Unit
In the sensing unit a [Teensy](https://www.pjrc.com/teensy/) microcontroller reads the sensor data from the connected sensors and sends it over the attached Bluetooth BLE module.

### Hardware
The following sensors were used:

| Category            | Name                                                                                                  | Provides                             | Price   |
|---------------------|-------------------------------------------------------------------------------------------------------|--------------------------------------|--------:|
| Core                | [Teensy 3.2](https://www.pjrc.com/teensy/)                                                            | Processing                           | ~24€ |
| Core                | [HM-11 BLE Module](http://wiki.seeed.cc/Bluetooth_V4.0_HM_11_BLE_Module/)                             | Bluethooth                           |  ~5€ |
| Sensors             | [BME280](https://www.bosch-sensortec.com/bst/products/all_products/bme280)                            | Temperature, Pressure, Humidity      | ~14€ |
| Sensors             | [iAQ-core C](http://ams.com/eng/Products/Environmental-Sensors/Air-Quality-Sensors/iAQ-core-C)        | VOC Sensor                           | ~33€ |
| Sensors (optional)  | [MQ135](https://www.olimex.com/Products/Components/Sensors/SNS-MQ135/)                                | Gas                                  |  ~2€ |
| Sensors (optional)  | [SM-PWM-01C](http://www.amphenol-sensors.com/en/component/edocman/3-co2/4-co2-modules/194-sm-pwm-01c) | Dust Sensor                          | ~14€ |
| Sensors (NA) | [BME680](https://www.bosch-sensortec.com/bst/products/all_products/bme680)                                   | Temperature, Pressure, Humidity, VOC |        NA |

### Wiring
A Fritzing sketch showing the layout of the current hardware prototype is included in the air-monitor folder.
