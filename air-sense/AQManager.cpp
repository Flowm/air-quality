#include "AQManager.hpp"

void AQManager::init() {
    bme.init();
    ds.init();
    an.init();
}

void AQManager::read() {
    bme.read();
    ds.read();
    an.read();
}

const char* AQManager::format(int counter) {
    line[0] = '\0';
    snprintf(buf, BUFSZ, "cnt=%05u", counter);
    strlcat(line, buf, LINESZ);

    if (bme.getId()) {
        snprintf(buf, BUFSZ, ",temp=%04.2f,humi=%05.3f,pres=%07.2f",
                bme.temperature(),
                bme.humidity(),
                bme.pressure());
        strlcat(line, buf, LINESZ);
    }

    if (bme.getId()) {
        snprintf(buf, BUFSZ, ",gasr=%05.0f", bme.gasresistance());
        strlcat(line, buf, LINESZ);
    }

    if (ds.getId()) {
        snprintf(buf, BUFSZ, ",dst=%04.2f", ds.temperature());
        strlcat(line, buf, LINESZ);
    }

    if (an.getId(IDSenALight)) {
        snprintf(buf, BUFSZ, ",ali=%04u", an.light());
        strlcat(line, buf, LINESZ);
    }

    if (an.getId(IDSenAMQ135)) {
        snprintf(buf, BUFSZ, ",amq=%04u", an.mq135());
        strlcat(line, buf, LINESZ);
    }

    // Calculate checksum for transmission
    unsigned sum = 0;
    for (size_t i = 0; i < strlen(line); i++) {
        sum += line[i] * (i+1);
    }
    sum = 0xFF & sum;

    snprintf(buf, BUFSZ, ",chk=%03u\r\n", sum);
    strlcat(line, buf, LINESZ);

    return &line[0];
}
