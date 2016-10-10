#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3);
float batterylevel = 0.0;
const int relay =  4;

void setup() {

  pinMode(relay, OUTPUT);
  String setName = String("AT+NAME=ChargerPort1\r\n"); //Setting name as 'MyBTBee'
  Serial.begin(9600);
  BTSerial.begin(38400);
  BTSerial.print("AT\r\n"); //Check Status
  delay(500);
  while (BTSerial.available()) {
    Serial.write(BTSerial.read());
  }
  BTSerial.print(setName); //Send Command to change the name
  delay(500);
  while (BTSerial.available()) {
    Serial.write(BTSerial.read());
  }

}


void loop() {

  if (BTSerial.available() > 0) { // Checks whether data is comming from the serial port
    batterylevel = BTSerial.read(); // Reads the data from the serial port
    Serial.write(BTSerial.read());
  }

  (batterylevel >= 1.0) ? digitalWrite(relay, LOW) : digitalWrite(relay, HIGH);
}
