OBJS = Mqtt.cpp Sensor.cpp
LIBS = -lmosquittopp -lpthread
CC = g++

all: ser2mqtt

ser2mqtt:
	$(CXX) $(LIBS) $(OBJS) main.cpp -o ser2mqtt -std=c++11

clean:
	rm -f ser2mqtt
