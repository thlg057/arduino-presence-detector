/*!
 * Arduino presence detector project
 * Autor : thlg
 * 
 * Based on Haljia Arduino starter kit
 * http://www.haljia.com/
 * Component : 
 * - Arduino Uno
 * - Ultra sonic HC-SR04
 *
 * Released under the MIT license
 * https://opensource.org/licenses/MIT
 *
 * Date: 2017-12-26
 */

#include "Ultrasonic.h"
int warningDistance = 20;
int alertDistance = 10;
int okPlotId = 12;
int warningPlotId = 11;
int alertPlotId = 10;
int sensorTrigPlotId = 9;
int sensorEchoPlotId = 8;
int greenFlashLoopCount = 1;
Ultrasonic ultrasonic(sensorTrigPlotId, sensorEchoPlotId); //(Trig,Echo)

void setup() {
  Serial.begin(9600);
  pinMode(okPlotId, OUTPUT);
  pinMode(warningPlotId, OUTPUT);
  pinMode(alertPlotId, OUTPUT);  
}

void loop()
{
  digitalWrite(okPlotId, LOW);
  digitalWrite(warningPlotId, LOW);
  digitalWrite(alertPlotId, LOW);
  
  int distanceInCm = ultrasonic.Ranging(CM);
  Serial.println(distanceInCm);
  if (distanceInCm <= warningDistance) {
    greenFlashLoopCount = 1;
    int ledId = warningPlotId;
    if (distanceInCm <= alertDistance) {
      ledId = alertPlotId;
    }

    flashLed(ledId);
  }
  else {
    if (greenFlashLoopCount % 10 == 0) {
      digitalWrite(okPlotId, HIGH);
      delay(200);
      greenFlashLoopCount = 1;
    }
    
    greenFlashLoopCount++;
  }

  delay(100);
}

void flashLed(int ledId) {
  int digitalStatus;
  for (int i = 1; i < 5; i++) {
    if (i % 2 == 0) {
      digitalStatus = LOW;
    }
    else {
      digitalStatus = HIGH;
    }
    digitalWrite(ledId, digitalStatus);
    delay(200);
  }
}


