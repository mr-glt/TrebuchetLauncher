#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>
#include <Adafruit_NeoPixel.h>
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

  Serial2.begin(9600);
  Serial.begin(9600);
  imu.begin();
  strip.begin();
  strip.show();
}
void loop() {
  //Serial2.println("Hello");
  imu.readGyro();
  imu.readAccel();
  gyroX = imu.calcGyro(imu.gx);
  gyroY = imu.calcGyro(imu.gy);
  gyroZ = imu.calcGyro(imu.gz);
  accelX = imu.calcAccel(imu.ax);
  accelZ = imu.calcAccel(imu.ay);
  accelY = imu.calcAccel(imu.az);
  Serial2.println("A" + gyroX + "B" + gyroY + "C" + gyroZ + "D" + accelX + "E" + accelY + "F" + accelZ + "G");

  incomingByte = Serial2.readString();
  if(incomingByte.substring(0,1) == "1"){
    colorWipe(strip.Color(255, 0, 0), 50);
    Serial.println(incomingByte);
  }
  if(incomingByte.substring(0,1) == "2"){
    colorWipe(strip.Color(0, 255, 0), 50);
    Serial.println(incomingByte);
  }
  if(incomingByte.substring(0,1) == "3"){
    colorWipe(strip.Color(0, 0, 255), 50);
    Serial.println(incomingByte);
  }
  if(incomingByte.substring(0,1) == "4"){
    colorWipe(strip.Color(0, 0, 0), 50);
    Serial.println(incomingByte);
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
