#include <Arduino.h>
#include <detect_fall.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void detect_fall(void *agrs){
  Wire.begin();

  while(!mpu.begin(MPU_I2C_ADDR)){
    Serial.println("Esperando A Inicialização do acelerometro...");
    delay(100);
  }

  Serial.println("-- Bem Vindo ao Queda Segura --");

  for(;;){
    Serial.println("Lorem");
  }
}