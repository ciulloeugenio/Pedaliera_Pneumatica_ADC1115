#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#define VERSION 'j'
#include <Joystick.h>

Adafruit_ADS1115 adc;

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  0, 0,                  // Button Count, Hat Switch Count
  false, false, false,     // X and Y, but no Z Axis
  true, true, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

void setup() {
  Joystick.begin();
//  Serial.begin(9600);
  adc.setGain(GAIN_TWOTHIRDS);
  adc.begin();
}

const bool initAutoSendState = true;

void loop() {
  static unsigned long previousMillis = 0; 
  const unsigned long interval = 1;       

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    int Acceleratore = adc.readADC_SingleEnded(0);
    int Freno = adc.readADC_SingleEnded(1);

    Joystick.setRxAxisRange(0, 32768);
    Joystick.setRyAxisRange(0, 32768);
    Joystick.setRxAxis(Acceleratore);
    Joystick.setRyAxis(Freno);
    /*
    Serial.print("Gas: \t");
    Serial.print(Acceleratore);
    Serial.print("\t || Brk: \t");
    Serial.println(Freno);
    */
    }
}
