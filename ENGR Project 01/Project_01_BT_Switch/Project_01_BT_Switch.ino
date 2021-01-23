#include <Wire.h>  //communicate with I2C, A4 (SDA), A5 (SCL)  https://www.arduino.cc/en/Reference/Wire
#include <LiquidCrystal_I2C.h>  //control I2C LCD  https://www.arduino.cc/en/Reference/LiquidCrystal

LiquidCrystal_I2C lcd(0x27,20,4);  // LCD setup

char BT = 0;  //variable for BT data

void setup() 
  {
    lcd.init();  //initialize LCD
    lcd.backlight();  //turn on LCD backlight
    lcd.begin(20,4);  //set LCD dimensions
    Serial.begin(9600);  //set baud for BT

    pinMode(11, OUTPUT);  //realy control pin 1
    digitalWrite(11, HIGH);  //low level trigger
    pinMode(12, OUTPUT);  //realy control pin 2 for future use
    digitalWrite(12, HIGH);  //low level trigger

    pinMode(9, INPUT);  //PC power
    digitalWrite(9, HIGH);  //low level trigger

    pinMode(7, INPUT);  //to BT Status LED pin "+" side. The Arduino will see the 3.3v signal from the HM-10 as HIGH
    digitalWrite(7, LOW);  //high level trigger
    
    lcd.setCursor(0,0);
    lcd.print("Automatic BT Switch");
    delay(5000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("BT is on");
    delay(500);
    lcd.setCursor(0,1);
    lcd.print("Stand By...");
    delay(5000);
  }

void loop() 
  {
    //if(Serial.available() > 0)  //when get data //some problems here
    //{
      BT = Serial.read();  //put into BT
      
        if(digitalRead(9) == LOW) //if the PC is on
          {
            Serial.println("PC is ON");
            lcd.setCursor(0,2);
            lcd.print("PC is ON ");
           if(BT == '1')
            {
              Serial.println("PC is already ON");
              lcd.setCursor(0,3);
              lcd.print("PC is already ON ");
              delay(1500);
              lcd.setCursor(0,3);
              lcd.print("                 ");
            }
            else if(BT == '0')
            {
              digitalWrite(11, LOW);
              delay(250);
              digitalWrite(11, HIGH);
              Serial.println("shutting down...");
              lcd.setCursor(0,3);
              lcd.print("shutting down...");
              delay(1500);
              lcd.setCursor(0,3);
              lcd.print("                ");
            }
            else if (digitalRead(7) == LOW) //when BT disconnect
            {
              digitalWrite(11, LOW);
              delay(250);
              digitalWrite(11, HIGH);
              lcd.setCursor(0,3);
              lcd.print("Disconnect PC OFF");
              delay(1500);
              lcd.setCursor(0,3);
              lcd.print("                 ");

              delay(50000);
            }
          }
          
        else if(digitalRead(9) == HIGH)  //if the PC is off
          {
            Serial.println("PC is OFF");
            lcd.setCursor(0,2);
            lcd.print("PC is OFF");
          if(BT == '1')
            {
              digitalWrite(11, LOW);
              delay(250);
              digitalWrite(11, HIGH);
              Serial.println("turning on...");
              lcd.setCursor(0,3);
              lcd.print("turning on...");
              delay(1500);
              lcd.setCursor(0,3);
              lcd.print("             ");
            }
          else if(BT == '0')
            {
              Serial.println("PC is already OFF");
              lcd.setCursor(0,3);
              lcd.print("PC is already OFF");
              delay(1500);
              lcd.setCursor(0,3);
              lcd.print("                 ");
            }
          //else if()
          }
      //}
  }
