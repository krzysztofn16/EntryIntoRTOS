// Use only core  1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu=0;
#else
static const BaseType_t app_cpu=1;
#endif

//Led rates
static const int rate_1 = 500; //ms
static const int rate_2 = 300; //ms

//Pins
static const int led_pin = LED_BUILTIN;

//task 1: blink a LED in rate rate_1
void toggleLED_1(void *parameter){
    while(1){
        digitalWrite(led_pin, HIGH);
        vTaskDelay(rate_1 / portTICK_PERIOD_MS); 
        // this function tells to scheduler to run other tasks until this specific delay time is up.
        //Expect number of this other than number of milliseconds. Desired millisends, devided by the tick period
        digitalWrite(led_pin, LOW);
        vTaskDelay(rate_1 / portTICK_PERIOD_MS); // tick period is set to 1millisecond in this RTOS
    }
}

//task 2: blink a LED in rate rate_2
void toggleLED_2(void *parameter){
    while(1){
        digitalWrite(led_pin, HIGH);
        vTaskDelay(rate_2/portTICK_PERIOD_MS);
        digitalWrite(led_pin,LOW);
        vTaskDelay(rate_2/portTICK_PERIOD_MS);
    }
}

void setup(){
    pinMode(led_pin, OUTPUT);

    // Task to  run forever
    xTaskCreatePinnedToCore(    // Use xTaskCreate() in vanilla FreeRTOS
                toggleLED_1,      // Function to be called
                "Toggle 1",   // Name of task
                1024,           // Stack size (bytes in ESP32, words in FreeRTOS)
                NULL,           // Parameter to   pass to  function
                1,              // Task priority (0 to configMAX_PRIORITIES -1)
                NULL,           // Task handle
                app_cpu);         // Run on one core for demo   purposes (ESP32 only)

    // If this wasvanilla FreeRTOS, you'd want to call vTaskStartScheduler() in
    //main after setting  up your tasks.

    xTaskCreatePinnedToCore(
                toggleLED_2,
                "Toggle 2",
                1024,
                NULL,
                1,
                NULL,
                app_cpu);
}
void loop(){
    // Do nothing
    // setup() and loop() run in their own task with priority 1 in core 1
    // on ESP32
}