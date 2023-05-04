// Include LCD functions:
#include <LiquidCrystal.h>

// LCD Connection
#define R_S 8
#define E 9
#define DB4 10
#define DB5 11
#define DB6 12
#define DB7 13

// LCD Defines
#define NUM_CHAR 20
#define NUM_LINES 4

//Analog Read Pin
#define ANALOG_READ_PIN A0
#define BUTTON_PIN A1

//LED PINs
#define GREEN1 2
#define GREEN2 3
#define YELLOW1 4
#define YELLOW2 5
#define RED1 6
#define RED2 7


// Global variables
// Define the LCD screen
LiquidCrystal lcd(R_S, E, DB4, DB5, DB6, DB7);

unsigned long DEBOUNCE_INTERVAL = 50;
unsigned long last_changed;
int color = 0;
int last_output = '0';
int frequency = 1;
int led_state;
unsigned long blink_interval = 1000;
unsigned long next_blink;
bool button_was_pressed = false;
int button_last_changed;

void setup() {
  // LCD has 4 lines with 20 chars
  lcd.begin(NUM_CHAR, NUM_LINES);
  lcd.setCursor(0, 0);
  lcd.print("Analog 0: ");

  Serial.begin(9600);
  pinMode(GREEN1, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  pinMode(YELLOW1, OUTPUT);
  pinMode(YELLOW2, OUTPUT);
  pinMode(RED1, OUTPUT);
  pinMode(RED2, OUTPUT);

  next_blink = millis() + blink_interval;

  button_last_changed = millis();
}



void loop() {
  int analog_read_value = analogRead(ANALOG_READ_PIN);

  // Set cursor to 10th position because the first String doesn't change.
  lcd.setCursor(10, 0);

  // Ex. 2
  // lcd.print(analog_read_value);

  // Ex. 3
  // blinkulate Voltage and transoform into printable String
  float analog_voltage = analog_read_value * 3.3 / 1023.0;
  String data_string = String(analog_voltage) + "V";
  lcd.print(data_string);

  // Ex. 5
  analog_read_value = analogRead(BUTTON_PIN);
  lcd.setCursor(0, 1);
  char output;
  switch (analog_read_value) {
    case 0 ... 10:
      output = '1';
      break;
    case 203 ... 283:
      output = '2';
      break;
    case 434 ... 514:
      output = '3';
      break;
    case 639 ... 719:
      output = '4';
      break;
    case 791 ... 871:
      output = '5';
      break;
    default:
      output = '-';
      break;
  }
  data_string = "S" + String(output);

  lcd.setCursor(0, 1);
  lcd.print(data_string);

  // Ex. 6 Output Serial
  if (output != '-') {
    Serial.print("S");
    Serial.println(output);
  }

  //Ex. 7
  // if (output != last_output) {
  //   last_changed = millis();
  // }

  // if (millis() - last_changed > DEBOUNCE_INTERVAL) {
  //   if (output != last_output) {
  //     if (output == '1') {
  //       if (color < 2) {
  //         color++;
  //       } else {
  //         color = 0;
  //       }
  //     }
  //   }
  // }

  // last_output = output;



  if (millis() - button_last_changed > DEBOUNCE_INTERVAL) {
    if (button_was_pressed) {
      if (output != '1') {
        button_was_pressed = false;
        button_last_changed = millis();
      }
    } else {
      if (output == '1') {
        if (color < 2) {
          color++;
        } else {
          color = 0;
        }
        button_was_pressed = true;
        button_last_changed = millis();
      }
    }
  }



  analog_read_value = analogRead(ANALOG_READ_PIN);
  frequency = map(analog_read_value, 0, 1023, 1, 50);
  blink_interval = 1000 / frequency;
  if (millis() >= next_blink) {
    if (led_state) {
      led_state = LOW;
    } else {
      led_state = HIGH;
    }

    digitalWrite(GREEN1, color == 0 ? led_state : LOW);
    digitalWrite(GREEN2, color == 0 ? led_state : LOW);

    digitalWrite(YELLOW1, color == 1 ? led_state : LOW);
    digitalWrite(YELLOW2, color == 1 ? led_state : LOW);

    digitalWrite(RED1, color == 2 ? led_state : LOW);
    digitalWrite(RED2, color == 2 ? led_state : LOW);

    next_blink += blink_interval;
  }
  lcd.setCursor(0, 2);
  switch (color) {
    case 0:
      lcd.print("Green");
      break;
    case 1:
      lcd.print("Yellow");
      break;
    case 2:
      lcd.print("Red");
      break;
  }
  lcd.setCursor(0, 3);
  lcd.print("  ");
  lcd.setCursor(0, 3);
  lcd.print(frequency);






  // Prevent display flickering for too fast updates
  //delay(100);
  // Clear the display.
  // lcd.clear();
  // NOTE: If you update only parts of the screen, don't use lcd.clear.
  // Set the cursor to the line and column to be updated and override existing chars.
}
