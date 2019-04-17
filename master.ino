// Servo Stuff
#include <Servo.h>
Servo myservo;

// Hbridge Stuff
#define enA 4
#define in1 5
#define in2 6

// Temp Stuff
#include <OneWire.h> 
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2 
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// WATER STUFF
int moistureSensor = 0;   //one nail goes to +5V, the other nail goes to this analogue pin
int moisture_val;
double thresh = 200;
//SD Stuff
#include <SPI.h>
#include <SD.h>
File myFile;
//* SD card attached to SPI bus as follows:
// ** MOSI - pin 11 on Arduino Uno/Duemilanove/Diecimila
// ** MISO - pin 12 on Arduino Uno/Duemilanove/Diecimila
// ** CLK - pin 13 on Arduino Uno/Duemilanove/Diecimila
// ** CS - depends on your SD card shield or module. 
//    Pin 10 used here for consistency with other Arduino examples
Sd2Card card;
SdVolume volume;
SdFile root;
const int chipSelect = 10;

//EMPTY WATER BUTTON
const int buttonPin = 8;
int buttonState = 0;

void setup() {

  // Hbridge stuff
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  Serial.begin(9600);

  myservo.attach(3);
  myservo.write(180);

  sensors.begin();
   
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  pinMode(chipSelect, OUTPUT);
}

void loop() {
  moisture_val = analogRead(moistureSensor);   // read the value from the nails
  if (moisture_val > thresh) {
  Serial.println( moisture_val );     // print the moisture level to the serial monitor
  // put your main code here, to run repeatedly:
  //analogWrite(enA,255);
  myservo.write(90);
  delay(2000);
  //Collect Sample for 1 min 45 sec
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA,255);
  delay(105000);
//Turn servo back to normal position and pump air in to clear tubes of water

  myservo.write(180);
  delay(1000);
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA,255);
  delay(15000);
  
  analogWrite(enA,0);
  // TEMP STUFF
  //Serial.print(" Requesting temperatures..."); 
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  myFile = SD.open("test.txt", FILE_WRITE);
  myFile.println(sensors.getTempCByIndex(0));
  myFile.close();
  //Serial.println("DONE"); 
/********************************************************************/
  //Serial.print("Temperature is: "); 
  //Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"?  
  // You can have more than one DS18B20 on the same bus.  
  // 0 refers to the first IC on the wire 

  //WATER STUFF
}
buttonState = digitalRead(buttonPin);
if (buttonState == HIGH) {
  myservo.write(90);
  delay(2000);
  //Collect Sample for 1 min 45 sec
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA,255);
  delay(120000);
  analogWrite(enA,0);
  myservo.write(180);
}
 }
