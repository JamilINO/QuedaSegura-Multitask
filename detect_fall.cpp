#include <Arduino.h>
#include <detect_fall.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include <RTClib.h>

Adafruit_MPU6050 mpu;
RTC_DS1307 rtc;

sensors_event_t acelerometer, gyroscope, temp;
sensors_event_t last_acelerometer, last_gyroscope, temp;

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
  DateTime before = rtc.now();
  for(;;){
    mpu.getEvent(&acelerometer, &gyroscope, &temp);

    Serial.print("aX: ");
    Serial.print(acelerometer.acceleration.x);
    Serial.print(" aY: ");
    Serial.print(acelerometer.acceleration.y);
    Serial.print(" aZ: ");
    Serial.print(acelerometer.acceleration.z);
/*
    Serial.print(" gX: ");
    Serial.print(gyroscope.gyro.x);
    Serial.print(" gY: ");
    Serial.print(gyroscope.gyro.y);
    Serial.print(" gZ: ");
    Serial.print(gyroscope.gyro.z);
*/
    DateTime now = rtc.now();
    Serial.print(" Hora: ");
    Serial.println(now.hour());
    Serial.print(":");
    Serial.print(now.minute());
    Serial.print(":");
    Serial.print(now.second());

    Serial.println("");

    if((now - before) > 1000){
      before = now;
      last_acelerometer = acelerometer
      lasr_gyroscope = gyroscope
      Serial.print(acelerometer.acceleration.x)
      Serial.print(" - ")
      Serial.print(last_acelerometer.acceleration.x)

      Serial.print("")
    }
  }
}