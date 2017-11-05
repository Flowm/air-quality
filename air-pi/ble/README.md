# Airpi BLE Controller
Connects to sensor modules over BLE and reads all incoming sensor data, publishing on the respective MQTT topics.

## Requirements
- `sudo apt install libbluetooth-dev`
- `sudo apt install libglib2.0-dev`
- `sudo pip3 install pybluez`
- `sudo pip3 install bluepy`
- `sudo pip3 install paho-mqtt`



<!--
For gattlib installation check the following requirements


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

- `sudo pip3 install bluepy`-->

