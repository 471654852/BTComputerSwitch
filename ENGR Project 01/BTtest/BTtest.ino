#include <Wire.h>  //communicate with I2C, A4 (SDA), A5 (SCL)
#include <LiquidCrystal_I2C.h> //control I2C LCD

LiquidCrystal_I2C lcd(0x27,20,4); // LCD setup

char data = 0;            //Variable for storing received data

void setup()
{
//-------------典开!-LCD!-------------
    lcd.init();  //initialize
    lcd.backlight();  //turn on backlight 
//------------LCD显示！---------------
    lcd.begin(20,4);
    lcd.setCursor(0,0);
    lcd.print("Bluetooth Switch");
    delay(2000);
    lcd.setCursor(0,2);
    lcd.print("BT is on");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Stand By...");
//---------------蓝牙！启动！------------------------------
    Serial.begin(9600);   //Sets the baud for serial data transmission  
//---------------------------------------------                             
    pinMode(11, OUTPUT);  //Sets digital pin 13 as output pin
    digitalWrite(11, HIGH);
    pinMode(12, OUTPUT);
    digitalWrite(12, HIGH);
}
void loop()
{
   if(Serial.available() > 0)      // Send data only when you receive data:
   {
      data = Serial.read();        //Read the incoming data & store into data
     // Serial.print(data);          //Print Value inside data in Serial monitor
     // Serial.print("\n");        
      if(data == '1')              // Checks whether value of data is equal to 1
      {
         digitalWrite(11, LOW);   //If value is 1 then LED turns ON
         delay(200);
         digitalWrite(11, HIGH); 
         Serial.print(data);
         Serial.println("Power Button Pushed");
         lcd.setCursor(0,1);
         lcd.print("Power Button Pushed");
         delay(3000);
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("Stand By...");
         
      }
      else if(data == '0')         //  Checks whether value of data is equal to 0
        digitalWrite(11, LOW);    //If value is 0 then LED turns OFF
      else if(data == '2')
        digitalWrite(12, LOW);
      else if(data == '3')
        digitalWrite(12, HIGH);
   }
}
