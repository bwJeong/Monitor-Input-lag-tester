#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <MsTimer2.h>

#define txSignal 0x10
#define switchPin 2
#define photoResistorPin A0
#define CLICKED HIGH

LiquidCrystal_I2C lcd(0x3F, 16, 2);

int accumulatedTime = 0;

void setup() {
  lcd.begin();
  lcd.backlight();
  Serial.begin(115200);
  MsTimer2::set(1, msTimer);
}

void loop() {
  if (digitalRead(switchPin) == CLICKED) {
    Serial.write(0x10);
    MsTimer2::start();

    while(1) {
      if (analogRead(photoResistorPin) > 750) {
        MsTimer2::stop();
        lcd.clear();
        lcd.print("PC Input lag = ");
        lcd.setCursor(0, 1);
        lcd.print(accumulatedTime);
        lcd.print(" ms");
        accumulatedTime = 0;
        break;
      }
    }
    delay(500);
  }
}

void msTimer() {
  accumulatedTime++;
}
