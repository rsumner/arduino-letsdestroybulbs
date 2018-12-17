#ifndef LIGHTBULB_H_
#define LIGHTBULB_H_

#include <Relay.h>
#include <ACS712.h>

class LightBulb {
public:
    LightBulb(int relayPin, int sensorPin, String label);
    void initSensorRelay();
    void initBulb();
    boolean toggle();
    String getZeroReport();
    String getMiniReport();
    String getReport();
    boolean isPresent();

private:
    String label;
    boolean present;
    ACS712 sensor;
    Relay relay;
    float amps;
    int watts;
    float zeroAmps;
    unsigned int toggleCount;
    String getState();
};

#endif /* LIGHTBULB_H_ */
