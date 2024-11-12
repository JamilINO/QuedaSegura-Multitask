#include <toggle_led.h>
#include <detect_fall.h>

#if CONFIG_FREERTOS_UNICORE
#define TASK_RUNNING_CORE 0
#else
#define TASK_RUNNING_CORE 1
#endif


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  xTaskCreate(
    detect_fall,
    "Detect Fall",
    2048,
    (void *)NULL,
    3,
    NULL
  );

  xTaskCreate(
    toggle_led, 
    "Toggle Led",
    2048,
    (void *)NULL,
    1,
    NULL
  );
}

void loop() {
  // put your main code here, to run repeatedly:
 
}
