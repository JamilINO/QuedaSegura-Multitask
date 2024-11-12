#include <Arduino.h>
#include <detect_fall.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include <RTClib.h>

Adafruit_MPU6050 mpu;
RTC_DS1307 rtc;

sensors_event_t acelerometer, gyroscope, temp;

void detect_fall(void *agrs){
  Wire.begin();

  Serial.println("Iniciando RTC...");
  while(!rtc.begin()){}
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

  for(;;){
    mpu.getEvent(&acelerometer, &gyroscope, &temp);
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
    Serial.println(gyroscope.gyro.z);
  }
}