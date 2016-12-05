#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>
#include <Adafruit_NeoPixel.h>
#include <SparkFunDS1307RTC.h>
#include <SPI.h>
#include <SD.h>
LSM9DS1 imu;
#define LSM9DS1_M  0x1E
#define LSM9DS1_AG  0x6B
#define DECLINATION -7.55 //For Newark
String gyroX;
String gyroZ;
String gyroY;
String accelX;
String accelZ;
String accelY;
String incomingByte = "";
Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, 4, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  //imu.begin();
  strip.begin();
  strip.show();
  rtc.begin();
  SD.begin(5);
}
void loop() {
  //Serial.println("Hello");
  rtc.update();
  //imu.readGyro();
  //imu.readAccel();
  //gyroX = imu.calcGyro(imu.gx);
  //gyroY = imu.calcGyro(imu.gy);
  //gyroZ = imu.calcGyro(imu.gz);
  //accelX = imu.calcAccel(imu.ax);
  //accelZ = imu.calcAccel(imu.ay);
  //accelY = imu.calcAccel(imu.az);
  // Read the time:
  int s = rtc.second();
  int m = rtc.minute();
  int h = rtc.hour();

  // Read the day/date:
  int dy = rtc.day();
  int da = rtc.date();
  int mo = rtc.month();
  int yr = rtc.year();
  File dataFile = SD.open("data.csv", FILE_WRITE);
  dataFile.print(String(mo) + "/" + String(da) + "/" + String(yr) + " " + String(h) + ":" + String(m) + ":" + String(s));
  //Serial.println(String(mo) + "/" + String(da) + "/" + String(yr) + " " + String(h) + ":" + String(m) + ":" + String(s));
  //dataFile.print(",");
  //dataFile.print(gyroX);
  //dataFile.print(",");
  //dataFile.print(gyroY);
  //dataFile.print(",");
  //dataFile.print(gyroZ);
  //dataFile.print(",");
  //dataFile.print(accelX);
  //dataFile.print(",");
  //dataFile.print(accelY);
  //dataFile.print(",");
  //dataFile.println(accelZ);
  //dataFile.close();
  //Serial.println("A" + gyroX + "B" + gyroY + "C" + gyroZ + "D" + accelX + "E" + accelY + "F" + accelZ + "G");
    incomingByte = Serial.readString();
    if(incomingByte.substring(0,1) == "1"){
      colorWipe(strip.Color(255, 0, 0), 50);
      //Serial.println("Switched color to red");
    }
    if(incomingByte.substring(0,1) == "2"){
      colorWipe(strip.Color(0, 255, 0), 50);
      //Serial.println("Switched color to green");
    }
    if(incomingByte.substring(0,1) == "3"){
      colorWipe(strip.Color(0, 0, 255), 50);
      //Serial.println("Switched color to blue");
    }
    if(incomingByte.substring(0,1) == "4"){
      colorWipe(strip.Color(0, 0, 0), 50);
      //Serial.println("Cleared lights");
    }
    if(incomingByte.substring(0,1) == "5"){
      rainbowCycle(10);
      //Serial.println(incomingByte);
    }


  //delay(600);
}
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    incomingByte = Serial.readString();
    if(incomingByte.substring(0,1) == "1"){
      colorWipe(strip.Color(255, 0, 0), 50);
      //Serial.println("Switched color to red");
    }
    if(incomingByte.substring(0,1) == "2"){
      colorWipe(strip.Color(0, 255, 0), 50);
      //Serial.println("Switched color to green");
    }
    if(incomingByte.substring(0,1) == "3"){
      colorWipe(strip.Color(0, 0, 255), 50);
      //Serial.println("Switched color to blue");
    }
    if(incomingByte.substring(0,1) == "4"){
      colorWipe(strip.Color(0, 0, 0), 50);
      //Serial.println("Cleared lights");
    }
    if(incomingByte.substring(0,1) == "5"){
      rainbowCycle(10);
      //Serial.println(incomingByte);
    }
    delay(wait);

  }
}
void fire(){
  //Fire
  //Serial.println("STARTED");
  delay(500);
  //Serial.println("5...");
  colorWipe(strip.Color(255, 0, 0), 33);
  //Serial.println("4...");
  colorWipe(strip.Color(0, 255, 0), 33);
  //Serial.println("3...");
  colorWipe(strip.Color(0, 0, 255), 33);
  //Serial.println("2...");
  colorWipe(strip.Color(255, 0, 0), 33);
  //Serial.println("1...");
  colorWipe(strip.Color(0, 0, 0), 33);
  analogWrite(3, 255);
  //Serial.println("GO");
  delay(2000);
  analogWrite(3, 0);
}
