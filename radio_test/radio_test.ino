#include <EnableInterrupt.h>
#include "radio_decoder.h"
#include "transmitter.h"

#define SERIAL_PORT_SPEED 57600

int pins[4] = {9, 11, 10, 6};

Transmitter myPilot(pins);

RadioDecoder radio;

#define RC_CH1  0
#define RC_CH2  1
#define RC_CH3  2
#define RC_CH4  3

#define RC_CH1_INPUT  A0
#define RC_CH2_INPUT  A1
#define RC_CH3_INPUT  A2
#define RC_CH4_INPUT  A3

void calc_ch1() { radio.calc_input(RC_CH1, RC_CH1_INPUT); }
void calc_ch2() { radio.calc_input(RC_CH2, RC_CH2_INPUT); }
void calc_ch3() { radio.calc_input(RC_CH3, RC_CH3_INPUT); }
void calc_ch4() { radio.calc_input(RC_CH4, RC_CH4_INPUT); }

void setup() {
  Serial.begin(SERIAL_PORT_SPEED);
  
  myPilot.Initialize();
  
  radio.Initialize();

  enableInterrupt(RC_CH1_INPUT, calc_ch1, CHANGE);
  enableInterrupt(RC_CH2_INPUT, calc_ch2, CHANGE);
  enableInterrupt(RC_CH3_INPUT, calc_ch3, CHANGE);
  enableInterrupt(RC_CH4_INPUT, calc_ch4, CHANGE);

  // radio.Calibrate();
}

void loop() {
  radio.rc_read_values();
  float ctr1 = radio.CtrInput(radio.GetChannel(0), 0),
        ctr2 = radio.CtrInput(radio.GetChannel(1), 1),
        ctr3 = radio.CtrInput(radio.GetChannel(2), 2),
        ctr4 = radio.CtrInput(radio.GetChannel(3), 3);

  // float servo1 = myPilot.ServoInput(ctr1, 0),
  //       servo2 = myPilot.ServoInput(ctr2, 1),
  //       servo3 = myPilot.ServoInput(ctr3, 2),
  //       servo4 = myPilot.ServoInput(ctr4, 3);
  
  myPilot.SetCtr(ctr1, 0);
  myPilot.SetCtr(ctr2, 1);
  myPilot.SetCtr(ctr3, 2);
  myPilot.SetCtr(ctr4, 3);
  // Serial.print("CH1:"); Serial.print(servo1); Serial.print("\t");
  // Serial.print("CH2:"); Serial.print(servo2); Serial.print("\t");
  // Serial.print("CH3:"); Serial.print(servo3); Serial.print("\t");
  // Serial.print("CH4:"); Serial.println(servo4);

  // Serial.print("CH1:"); Serial.print(radio.GetChannel(RC_CH1)); Serial.print("\t");
  // Serial.print("CH2:"); Serial.print(radio.GetChannel(RC_CH2)); Serial.print("\t");
  // Serial.print("CH3:"); Serial.print(radio.GetChannel(RC_CH3)); Serial.print("\t");
  // Serial.print("CH4:"); Serial.println(radio.GetChannel(RC_CH4));


  // delay(200);
}
