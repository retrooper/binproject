// Now turn this trash into treasure!
#include <LiquidCrystal.h>

int potmeterPin = A0;
int potmeterVal = 0;

int buttonPin = 2;
int buttonVal = 0;

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  Serial1.println("Hello, Raspberry Pi Pico W!");
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

   lcd.begin(16, 2);
  // you can now interact with the LCD, e.g.:
  lcd.print("Hello World!");
}
void loop() {
  potmeterVal = analogRead(potmeterPin);
  int buttonRes = digitalRead(buttonPin);
  if (potmeterVal > 511) {
    //Yes
    //Serial1.println("Yes");
  }
  else {
    //No
    //Serial1.println("No!");
  }
  if (buttonVal != buttonRes) {
    if (buttonRes == LOW) {
      //Pressed the button
      digitalWrite(LED_BUILTIN, HIGH);
      lcd.clear();
      lcd.print("Yes!");
    }
    else {
      digitalWrite(LED_BUILTIN, LOW);
      lcd.clear();
      lcd.print("No!");
    }
    buttonVal = buttonRes;
  }
  delay(100);
}