#include "LightBulb.h"
#include <Arduino.h>
#include <ACS712.h>
#include <Relay.h>


LightBulb::LightBulb(int _relayPin, int _sensorPin, String _label): sensor(ACS712_05B, _sensorPin), relay(_relayPin, true) {
  label = _label;
  amps = 0.0;
  watts = 0;
  toggleCount = 0;
  present = false;
  zeroAmps = 0.0;
}

void LightBulb::initSensorRelay() {
  sensor.calibrate();
  zeroAmps = sensor.getCurrentAC(1);
  relay.begin();
  relay.turnOff();
  Serial.println(label + " relay state is " + relay.getState()==0?"OFF":"ON");
}

void LightBulb::initBulb() {
  toggle();
  toggleCount = 0;
}

boolean LightBulb::toggle() {
  relay.turnOn();
  amps = sensor.getCurrentAC(1) - zeroAmps;
  watts = 120 * amps;
  if(watts >= 5) {
    present = true;
  } else {
    present = false;
  }
  relay.turnOff();
  toggleCount++;
  return present;
}

// a formatted report suitable for LCD output
String LightBulb::getReport() {
  return label + ":" + getState() + " " + (String)watts + "W C=" + (String)toggleCount;
}

String LightBulb::getMiniReport() {
  return label + ":" + getState();
}

String LightBulb::getZeroReport() {
  return label + ":" + (String)zeroAmps;
}

String LightBulb::getState() {
  return present==true?" OK":"BAD";
}

boolean LightBulb::isPresent() {
  return present;
}
