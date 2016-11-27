#include <SPI.h>
#include <SD.h>
void setup() {
  SD.begin(5);

}
void loop() {
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  dataFile.print("test ");
  dataFile.println(",");
  dataFile.close();
  delay(1000);
}
