String incomingByte = "";

void setup() {

  Serial2.begin(9600);
  Serial.begin(9600);
}
void loop() {
  //Serial2.println("Hello");
  if (Serial2.available() > 0) {
        // read the incoming byte:
        incomingByte = Serial2.readString();
        if(incomingByte == ""){

        }
        else{
          Serial.println(incomingByte);
        }
  }
}
