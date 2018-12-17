#include <Arduino.h>
#include <AceButton.h>
using namespace ace_button;
#include <AdjustableButtonConfig.h>
#include <ButtonConfig.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include "LightBulb.h"

#define SENSOR_PIN1   A0
#define SENSOR_PIN2   A1
#define SENSOR_PIN3   A2
#define SENSOR_PIN4   A3

#define BUZZER_PIN    8
#define PLAYBUTTON_PIN  6
#define STOPBUTTON_PIN  7
#define RELAY_PIN1    2
#define RELAY_PIN2    3
#define RELAY_PIN3    4
#define RELAY_PIN4    5

LiquidCrystal_PCF8574 lcd(0x27);
AceButton playButton(PLAYBUTTON_PIN);
AceButton stopButton(STOPBUTTON_PIN);

LightBulb bulb1(RELAY_PIN1, SENSOR_PIN1, "B1");
LightBulb bulb2(RELAY_PIN2, SENSOR_PIN2, "B2");
LightBulb bulb3(RELAY_PIN3, SENSOR_PIN3, "B3");
LightBulb bulb4(RELAY_PIN4, SENSOR_PIN4, "B4");

// stub functions we'll define after loop()
void buttonEvent(AceButton*, uint8_t, uint8_t);
void displayZeroReport();
void displayMiniReport();
void displayReport();

boolean running = false;

void setup() {
	  Serial.begin(9600);
	  Serial.print("Checking for LCD...");
	  Wire.begin();
	  Wire.beginTransmission(0x27);
	  int error = Wire.endTransmission();
	  if (error == 0) {
	    Serial.println("Found.");
	  } else {
	    Serial.println("Not Found!!");
	  }
	  lcd.begin(20, 4); // initialize the LCD
	  lcd.setBacklight(255); // turn up the backlight
	  lcd.blink();
	  lcd.clear();

	  bulb1.initSensorRelay();
	  bulb2.initSensorRelay();
	  bulb3.initSensorRelay();
	  bulb4.initSensorRelay();

	  lcd.home();
	  displayZeroReport();

	  pinMode(PLAYBUTTON_PIN, INPUT);
	  pinMode(STOPBUTTON_PIN, INPUT);
	  playButton.init(PLAYBUTTON_PIN, LOW);
	  stopButton.init(STOPBUTTON_PIN, LOW);
	  playButton.setEventHandler(buttonEvent);
	  stopButton.setEventHandler(buttonEvent);

	  pinMode(BUZZER_PIN, OUTPUT);

	  bulb1.initBulb();
	  bulb2.initBulb();
	  bulb3.initBulb();
	  bulb4.initBulb();
	  displayMiniReport();
}

void loop() {
	  playButton.check();
	  stopButton.check();

	  if(running) {
	    playButton.check();
	    stopButton.check();

	    if(bulb1.isPresent()) {
	      bulb1.toggle();
	      if(!bulb1.isPresent()) {
	        // bulb blew
	        digitalWrite(BUZZER_PIN, HIGH);
	        delay(10);
	        digitalWrite(BUZZER_PIN, LOW);
	      }
	      displayReport();
	    }

	    playButton.check();
	    stopButton.check();

	    if(bulb2.isPresent()) {
	      bulb2.toggle();
	      if(!bulb2.isPresent()) {
	        // bulb blew
	        digitalWrite(BUZZER_PIN, HIGH);
	        delay(10);
	        digitalWrite(BUZZER_PIN, LOW);
	      }
	      displayReport();
	    }

	    playButton.check();
	    stopButton.check();

	    if(bulb3.isPresent()) {
	      bulb3.toggle();
	      if(!bulb3.isPresent()) {
	        // bulb blew
	        digitalWrite(BUZZER_PIN, HIGH);
	        delay(10);
	        digitalWrite(BUZZER_PIN, LOW);
	      }
	      displayReport();
	    }

	    playButton.check();
	    stopButton.check();

	    if(bulb4.isPresent()) {
	      bulb4.toggle();
	      if(!bulb4.isPresent()) {
	        // bulb blew
	        digitalWrite(BUZZER_PIN, HIGH);
	        delay(10);
	        digitalWrite(BUZZER_PIN, LOW);
	      }
	      displayReport();
	    }

	  }
}

void displayReport() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(bulb1.getReport());
  lcd.setCursor(0,1);
  lcd.print(bulb2.getReport());
  lcd.setCursor(0,2);
  lcd.print(bulb3.getReport());
  lcd.setCursor(0,3);
  lcd.print(bulb4.getReport());
}

void displayMiniReport() {
  lcd.clear();
  lcd.print("LET'S DESTROY BULBS!");
  lcd.setCursor(0,1);
  lcd.print(bulb1.getMiniReport());
  lcd.print(" / " + bulb2.getMiniReport());
  lcd.setCursor(0,2);
  lcd.print(bulb3.getMiniReport());
  lcd.print(" / " + bulb4.getMiniReport());
  lcd.setCursor(0,3);
  lcd.print("PRESS PLAY or RESET");
}

void displayZeroReport() {
  lcd.clear();
  lcd.print("LET'S DESTROY BULBS!");
  lcd.setCursor(0,1);
  lcd.print("SENSOR BASELINE");
  lcd.setCursor(0,2);
  lcd.print(bulb1.getZeroReport());
  lcd.print(" / " + bulb2.getZeroReport());
  lcd.setCursor(0,3);
  lcd.print(bulb3.getZeroReport());
  lcd.print(" / " + bulb4.getZeroReport());
}

void buttonEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventReleased:
      break;
    case AceButton::kEventPressed:
      if(button->getPin() == PLAYBUTTON_PIN) running = true;

      if(button->getPin() == STOPBUTTON_PIN && running == false) {
        bulb1.initBulb();
        bulb2.initBulb();
        bulb3.initBulb();
        bulb4.initBulb();
        displayMiniReport();
      }

      if(button->getPin() == STOPBUTTON_PIN && running == true) running=false;

      break;
  }
}
