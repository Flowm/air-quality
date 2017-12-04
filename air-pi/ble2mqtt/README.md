# Airpi BLE Controller
Connects to sensor modules over BLE and reads all incoming sensor data, publishing on the respective MQTT topics.

## Requirements
The `airpi_ble` daemon is tested on a Raspberry PI with Raspbian.
It should however run on other Linux distributions as well, as it depends on `hcitool` and `gatttool`.

The following linux packages need to be installed to enable access to bluetooth APIs:
- `sudo apt install libbluetooth-dev`
- `sudo apt install libglib2.0-dev`

The required python3 libraries can be installed automatically via pip, using the `requirements.txt` file
(a virtualenv is recommended), or manually by executing the following commands:
- `sudo pip3 install pybluez`
- `sudo pip3 install bluepy`
- `sudo pip3 install paho-mqtt`

## Usage
The ble controller connects to a predefined BLE module. The address and UUID are hardcoded inside `airpi_ble.py`.
Change these when coupling a different BLE chip.

By default, the program attempts to connect to an mqtt broker on localhost. Change this parameter inside `airpi_ble.py` in case the broker is residing on a different machine.

The ble module can be run as a standalone daemon on the system. Simply run `./airpi_ble.py`


*Note: airpi_ble requires sudo rights to run, as the `bluepy` APIs rely on `hcitool` and `gatttool`, which must be run as superuser.*


<!--
USED ONLY FOR ALTERNATIVE PYTHON LIBS (gattlib)

Gattlib requires an additional glib2.0 package, therefore install:
- `sudo apt install libperl-dev`
- `sudo apt install libgtk2.0-dev`

or
- `sudo apt install libglib2.0-dev`

Now we can install gattlib:
- `sudo apt install libboost-thread-dev`
- `sudo pip3 install libboost-python-dev`

- `pip3 download gattlib`
- `tar xvzf ./gattlib-0.20150805.tar.gz`
-` cd gattlib-0.20150805/`
- `sed -ie 's/boost_python-py34/boost_python-py35/' setup.py`
- `pip3 install .`


