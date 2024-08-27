// Now turn this trash into treasure!
#include <LiquidCrystal.h>
int potmeterPin = A0;
int potmeterVal = 0;

int buttonPin = 2;
int buttonVal = 0;

boolean sliderRight = false;
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

String question = "How are you?";
String terminateStatement = "Bye bye!";
String responses[] = { "Good", "Bad" };
int questionIndex = 0;
void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  Serial1.println("Hello, Raspberry Pi Pico W!");
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  lcd.begin(16, 2);
  // you can now interact with the LCD, e.g.:
  lcd.print(question);
}
void loop() {
  potmeterVal = analogRead(potmeterPin);
  int buttonRes = digitalRead(buttonPin);
  boolean sliderRes = potmeterVal > 511;

  if (sliderRes != sliderRight) {
    if (potmeterVal > 511) {
      //Yes
      //Serial1.println("Yes");
      lcd.clear();
      lcd.print(question);
      lcd.setCursor(2, 2);
      lcd.print(responses[0]);
    } else {
      //No
      //Serial1.println("No!");
      lcd.clear();
      lcd.print(question);
      lcd.setCursor(2, 2);
      lcd.print(responses[1]);
    }
    sliderRight = sliderRes;
  }
  if (buttonVal != buttonRes) {
    if (buttonRes == LOW) {
      //Pressed the button
      digitalWrite(LED_BUILTIN, HIGH);
      //Confirm slider position
      switch (questionIndex) {
        case 0:
          {
            if (sliderRight) {
              question = "Great!";
            } else {
              lcd.clear();
              lcd.print("No...");
              delay(2500);
              question = "What's wrong?";
            }
            responses[0] = "Bye!";
            responses[1] = "Why ask?";
            break;
          }
        case 1:
          {
            if (sliderRight) {
              question = terminateStatement;
            } else {
              question = "Because I care.";
            }
            responses[0] = "Do you really?";
            responses[1] = "Bye...";
            break;
          }
        case 2:
          {
            if (sliderRight) {
              question = "Of course I care.";
              lcd.clear();
              lcd.print("I'm human..");
              delay(1500);
              lcd.clear();
              lcd.print("Just like you...");
              delay(1500);
            } else {
              question = terminateStatement;
            }
            responses[0] = "Interesting...";
            responses[1] = "No you're not!";
            break;
          }
        case 3:
          {
            if (!sliderRight) {
              lcd.clear();
              lcd.print("Sure I am...");
              delay(2000);
            }
            lcd.clear();
            lcd.print("Thanks for...");
            delay(2000);
            question = "chatting with me!";
            responses[0] = "Alright.";
            responses[1] = responses[0];
            break;
          }
        case 4:
          {
            question = terminateStatement;
            break;
          }
      }
      lcd.clear();
      lcd.print(question);
      questionIndex++;

      if (question.equals(terminateStatement)) {
        //Reset
        delay(5000);
        question = "How are you?";
        responses[0] = "Good";
        responses[1] = "Bad";
        setup();
        questionIndex = 0;
      }
    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }
    buttonVal = buttonRes;
  }
  delay(100);
}