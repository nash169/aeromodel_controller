#include "transmitter.h"

int pins[3] = {9, 11, 10};
Transmitter myPilot(pins);

void setup() {
  myPilot.Initialize();
  Serial.begin(9600);
  
  Serial.print("Ailerons angle (+/-): ");
  Serial.print(myPilot.GetAil());
  Serial.print("\n");

  Serial.print("Elevator angle: ");
  Serial.print(myPilot.GetElev());
  Serial.print("\n");

  Serial.print("Rudder angle: ");
  Serial.print(myPilot.GetRud());
  Serial.print("\n");  
}

void loop() {
  while(Serial.available()){
    float val = Serial.parseFloat();
    myPilot.SetAil(val);
    myPilot.SetElev(val);
    myPilot.SetRud(val);
    
    Serial.print("Ailerons angle (+/-): ");
    Serial.print(myPilot.GetAil());
    Serial.print("\n");
  
    Serial.print("Elevator angle: ");
    Serial.print(myPilot.GetElev());
    Serial.print("\n");
  
    Serial.print("Rudder angle: ");
    Serial.print(myPilot.GetRud());
    Serial.print("\n");
    }
}
