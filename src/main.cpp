#include <Arduino.h>
#include <FreeRTOS.h>

void taskOne( void * parameter );
void taskTwo( void * parameter);


void setup() {
 
  Serial.begin(9600);
  delay(1000);
 
  xTaskCreate(
                    taskOne,          /* Task function. */
                    "TaskOne",        /* String with name of task. */
                    10000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */
 
  xTaskCreate(
                    taskTwo,          /* Task function. */
                    "TaskTwo",        /* String with name of task. */
                    10000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */
 
}
 
void loop() {
  delay(1000);
}
 
void taskOne( void * parameter )
{
 
    for( int i = 0;i<10;i++ ){
 
        Serial.println("Hello from task 1");
          Serial.print("loop() running on core ");
  Serial.println(xPortGetCoreID());
        delay(1000);
    }
 
    Serial.println("Ending task 1");
    vTaskDelete( NULL );
 
}
 
void taskTwo( void * parameter)
{
 
    for( int i = 0;i<10;i++ ){
 
        Serial.println("Hello from task 2");
          Serial.print("loop() running on core ");
  Serial.println(xPortGetCoreID());
        delay(1000);
    }
    Serial.println("Ending task 2");
    vTaskDelete( NULL );
 
}