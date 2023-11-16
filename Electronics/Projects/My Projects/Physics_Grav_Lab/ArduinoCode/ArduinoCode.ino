int sensorValue = 0;
bool Active = false;
void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT);
  pinMode(A5,INPUT);
  Serial.begin(2000000);
}

void loop() {
    // put your main code here, to run repeatedly:
    // read the value from the sensor
    float sensorValue = float(analogRead(A0))/1.5;
    if (sensorValue > 100 ){
        // turn the LED on
        tone(13,sensorValue);      
    }else{
      noTone(13);
    }
    if (analogRead(A5)==1023) {
        Serial.println("Hit");
    }

}