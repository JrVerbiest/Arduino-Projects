 /* nRF52840_IMU
 *
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

#include <Arduino.h>
#include "ICM_20948.h"

#define AD0_VAL 1
#define FREQUENCY_HZ        50
#define INTERVAL_MS         (1000 / (FREQUENCY_HZ + 1))
#define CONVERT_MG_TO_MS2   9.80665f/1000

ICM_20948_I2C myICM;

void printData(ICM_20948_I2C *sensor, uint8_t decimals);

void setup() {
  Serial.begin(115200);
  while(!Serial){
  };

  Wire.begin();
  Wire.setClock(400000);

  myICM.enableDebugging();

  bool initialized = false;
  while(!initialized){
    myICM.begin(Wire, AD0_VAL);
    Serial.print(F("Initialization of the sensor retured: "));
    Serial.println(myICM.statusString());
    if(myICM.status != ICM_20948_Stat_Ok)
    {
      Serial.println("Trying again...");
      delay(1000);
    }else{
      initialized = true;
    }
  }
}

void loop() {

  static unsigned long last_interval_ms = 0;

  if (millis() > last_interval_ms + INTERVAL_MS) {
    last_interval_ms = millis();
    myICM.getAGMT();
    printData(&myICM, 2);
  }
}

void printData(ICM_20948_I2C *sensor, uint8_t decimals){
  // Acc (mg) is converted to m/s^2
  Serial.print(sensor->accX()*CONVERT_MG_TO_MS2, decimals);
  Serial.print(",");
  Serial.print(sensor->accY()*CONVERT_MG_TO_MS2, decimals);
  Serial.print(",");
  Serial.print(sensor->accZ()*CONVERT_MG_TO_MS2, decimals);
  Serial.print(",");

  // Gyr (DPS)
  Serial.print(sensor->gyrX(), decimals);
  Serial.print(",");
  Serial.print(sensor->gyrY(), decimals);
  Serial.print(",");
  Serial.println(sensor->gyrZ(), decimals);
}