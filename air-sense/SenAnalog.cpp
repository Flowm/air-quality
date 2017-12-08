#include "SenAnalog.hpp"

int SenAnalog::init() {
    analogReadAveraging(32);

#ifdef APIN_LIGHT
    pinMode(APIN_LIGHT, INPUT);
    setId(IDSenALight);
#endif

#ifdef APIN_MQ135
    pinMode(APIN_MQ135, INPUT);
    setId(IDSenALight | IDSenAMQ135);
#endif
    return 0;
}

int SenAnalog::read() {
#ifdef APIN_LIGHT
    _light = analogRead(APIN_LIGHT);
#endif
#ifdef APIN_MQ135
    _mq135 = analogRead(APIN_MQ135);
#endif
    return 0;
}
