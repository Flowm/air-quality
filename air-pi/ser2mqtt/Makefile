OBJS = Mqtt.cpp Sensor.cpp
LIBS = -lmosquittopp -lpthread
CXXFLAGS = -g -Wall -Wextra
all: ser2mqtt

ser2mqtt:
	$(CXX) $(CXXFLAGS) $(LIBS) $(OBJS) main.cpp -o ser2mqtt -std=c++11

clean:
	rm -f ser2mqtt
