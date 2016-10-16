
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial BTSerial(2, 3);
float batterylevel ;
const int relay =  4;
char c[4];
bool backlighton = false;
String charger1 = "06:20:52:94";
String charger2 = "06:29:19:75";
String charger3 = "07:04:12:64";
void setup() {
  lcd.init();
  lcd.init();
  lcd.backlight();
  backlighton = true;
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);

  Serial.begin(9600);
  BTSerial.begin(9600);

  LCD_MSG(charger1, "Bluetooth") ;
}


void loop() {


  int i = 0;

  if (BTSerial.available()) {
    delay(100); //allows all serial sent to be received together
    while (BTSerial.available() && i < 4) {
      c[i++] = BTSerial.read();
    }
    c[i++] = '\0';
  }

  if (i > 0) {
    batterylevel = atof(c);
    Serial.println(c);

    if (batterylevel >= 1.00) {
      digitalWrite(relay, HIGH);
      LCD_MSG("Charger OFF", String(batterylevel * 100) + "%") ;
      if(backlighton){
        lcd.noBacklight();
      }
      backlighton = false;  
    } 
    if (batterylevel < 0.90) {
      digitalWrite(relay, LOW);
      LCD_MSG("Charger ON", String(batterylevel * 100) + "%") ;
      if (!backlighton) {
        lcd.backlight();
      }
      backlighton = true;
    }

  }

}



void LCD_MSG(String MSG1, String MSG2) {
  lcd.clear();
  lcd.setCursor(0, 0); //set to second Line
  lcd.print(MSG1); // Print a message to the LCD.
  lcd.setCursor(0, 1); //set to second Line
  lcd.print(MSG2); // Print a message to the LCD.
}
