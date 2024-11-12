#include <Arduino.h>
#include <toggle_led.h>

void toggle_led(void *args){
  pinMode(led_pin, OUTPUT);
  for(;;){
      digitalWrite(led_pin, HIGH);
      delay(1000);
      digitalWrite(led_pin, LOW);
      delay(1000);
  }
}