#include <Arduino.h>
#include <detect_fall.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include <RTClib.h>

#include <HTTPClient.h>
#include <ArduinoJson.h>

Adafruit_MPU6050 mpu;
RTC_DS1307 rtc;
HTTPClient http;

sensors_event_t acelerometer, gyroscope, temp;
sensors_event_t last_acelerometer, last_gyroscope, tmp;

void detect_fall(void *agrs){
  Wire.begin();

  Serial.println("Iniciando RTC...");
  while(!rtc.begin()){}
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  for(int i = 0; !rtc.isrunning(); i++){
    Serial.print(i);
    Serial.print("...");
    delay(100);
  }

  Serial.println("Iniciando acelerometro...");
  for(int i = 0; !mpu.begin(MPU_I2C_ADDR); i++){
    Serial.print(i);
    Serial.print("...");
    delay(100);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G); // Definindo o range de ação do acelerometro.
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);      // Definindo o range de ação do giroscopio.
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);   // Configurando a largura da banda do filtro

  Serial.println("-- Bem Vindo ao Queda Segura --");

  mpu.getEvent(&last_acelerometer, &last_gyroscope, &temp);
  //DateTime before = rtc.now();
  for(;;){
    mpu.getEvent(&acelerometer, &gyroscope, &temp);
/*

    Serial.print("aX: ");
    Serial.print(acelerometer.acceleration.x);
    Serial.print(" aY: ");
    Serial.print(acelerometer.acceleration.y);
    Serial.print(" aZ: ");
    Serial.print(acelerometer.acceleration.z);
  

    Serial.print(" gX: ");
    Serial.print(gyroscope.gyro.x);
    Serial.print(" gY: ");
    Serial.print(gyroscope.gyro.y);
    Serial.print(" gZ: ");
    Serial.print(gyroscope.gyro.z);
  */
    DateTime now = rtc.now();
/*
    Serial.print(" Hora: ");
    Serial.print(now.hour());
    Serial.print(":");
    Serial.print(now.minute());
    Serial.print(":");
    Serial.print(now.second());
*/
    int intensity = acelerometer.acceleration.x - last_acelerometer.acceleration.x;
    if(intensity > 10){
      Serial.print("aX: ");
      Serial.print(acelerometer.acceleration.x);
      Serial.print(" aY: ");
      Serial.print(acelerometer.acceleration.y);
      Serial.print(" aZ: ");
      Serial.print(acelerometer.acceleration.z);
      Serial.print(" Intensity: ");
      Serial.print(intensity);
      Serial.println("");
    }

    Serial.println(acelerometer.acceleration.x);
    DynamicJsonDocument doc(2048);

    doc["ax"] = acelerometer.acceleration.x;
    doc["ay"] = acelerometer.acceleration.y;
    doc["az"] = acelerometer.acceleration.z;

    doc["gx"] = gyroscope.gyro.x;
    doc["gy"] = gyroscope.gyro.y;
    doc["gz"] = gyroscope.gyro.z;

    doc["h"] = now.hour();
    doc["m"] = now.minute();
    doc["s"] = now.second();

    http.begin("http://192.168.15.77:7777/api");

    String json; 
    serializeJson(doc, json);

   // Serial.println(json);
    http.begin("http://192.168.15.77:7777/api");
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST(json);
    if (httpCode == HTTP_CODE_OK) {
      Serial.print("Hello");
    }
    else{
      Serial.print("Error");
    }
    http.end();
    last_acelerometer = acelerometer;
    last_gyroscope = gyroscope;
    //Serial.println("");
  }
}