/* Sensor Module
 * Copyright (c) 2021
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:

 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "Arduino.h"
#include <Wire.h>

#include "SparkFun_SCD30_Arduino_Library.h" // http://librarymanager/All#SparkFun_SCD30

SCD30 scd30;

uint16_t counter = 0;

struct SCD30Sensor {
  float Temperature = -999;
  float Humidity = -999;
  uint16_t CO2 = 0;
} SCD30Sensor;


void serialPrint(){
  // Serial output: 
  // OK,Temperature [°C], Humidity [%], CO2 [ppm],X
  Serial.print("OK");
  Serial.print(",");
  Serial.print(counter);
  Serial.print(",");
  Serial.print(SCD30Sensor.Temperature, 1);
  Serial.print(",");
  Serial.print(SCD30Sensor.Humidity, 0);
  Serial.print(",");
  Serial.print(SCD30Sensor.CO2);
  Serial.print(",");
  Serial.println("X");
  Serial.flush();
}


void setup()
{
  Serial.begin(115200);
  Wire.begin();

  if (scd30.begin() == false)
  {
    Serial.println("SCD30 sensor not detected. Please check wiring. Freezing...");
    while (1);
  }
  Serial.flush();
}


void loop()
{
  //The default configuration is used where SCD30 has data ready every two seconds.

  int inByte = 0;

  if(Serial.available() > 0){
    inByte = Serial.read();
    }

  switch(inByte){
    case 115: // use a simple 'communication protocol', in this case ASCII lower case letter s
      counter++;

      while(!scd30.dataAvailable()){
        // Wait untill data is available
      }

      SCD30Sensor.Temperature = scd30.getTemperature();
      SCD30Sensor.Humidity = scd30.getHumidity();
      SCD30Sensor.CO2 = scd30.getCO2();
      serialPrint();
  }
}