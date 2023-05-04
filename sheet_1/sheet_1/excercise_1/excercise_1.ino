#define LED_PIN 10
#define CALC_INTERVAL 1000

// Switch between Part i and ii by defining i or ii
#define ii

unsigned long timer;
unsigned long next_calc;
#ifdef ii
int led_state;
#endif

void setup() {
  pinMode(LED_PIN, OUTPUT);
  next_calc = millis() + CALC_INTERVAL;
  #ifdef ii
  led_state = HIGH;
  #endif
}

void loop() {
  /* i)*/
  #ifdef i
  delay(1000);
  digitalWrite(LED_PIN, 1);
  delay(1000);
  digitalWrite(LED_PIN, 0);
  #endif

  /*  ii) The delay function internally calls the micros function in a while loop and therefore during the execution of the delay
  * function we can't perform other things. This is also called active waiting and basically means we're wasting 
  * calculation time. */
  #ifdef ii
  if (millis() >= next_calc) {  
    if(led_state) {
      led_state = LOW;
    } else {
      led_state = HIGH;
    }
    digitalWrite(LED_PIN, led_state);
    next_calc += CALC_INTERVAL;
  }
  #endif
}
