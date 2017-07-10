#include "radio_decoder.h"

RadioDecoder::RadioDecoder() {  }

RadioDecoder::~RadioDecoder() {  }

void RadioDecoder::Initialize()
{
	pinMode(RC_CH1_INPUT, INPUT);
  pinMode(RC_CH2_INPUT, INPUT);
  pinMode(RC_CH3_INPUT, INPUT);
  pinMode(RC_CH4_INPUT, INPUT);

  for (int i = 0; i < RC_NUM_CHANNELS; ++i)
  {
    bd[i].minRadio = 1500;
    bd[i].maxRadio = 1500;
  }

  bd[RC_CH1].minCtr = -15;
  bd[RC_CH1].maxCtr =  15;
  bd[RC_CH2].minCtr = -15;
  bd[RC_CH2].maxCtr =  15;
  bd[RC_CH3].minCtr = -15;
  bd[RC_CH3].maxCtr =  15;
  bd[RC_CH4].minCtr = -15;
  bd[RC_CH4].maxCtr =  15;

  for (int i = 0; i < RC_NUM_CHANNELS; ++i)
    {
      bd[i].maxRadio = 2000;
      bd[i].minRadio = 1000;
    }
}

void RadioDecoder::Calibrate()
{
  Serial.println(F("\nSend any character to begin calibration of radio deoceder: "));
    
  while (Serial.available() && Serial.read()); // empty buffer
  while (!Serial.available());                 // wait for data
  while (Serial.available() && Serial.read()); // empty buffer again

  while(millis() < 50000) {
    rc_read_values();
    Serial.print("CH1:"); Serial.print(rc_values[RC_CH1]); Serial.print("\t");
    Serial.print("CH2:"); Serial.print(rc_values[RC_CH2]); Serial.print("\t");
    Serial.print("CH3:"); Serial.print(rc_values[RC_CH3]); Serial.print("\t");
    Serial.print("CH4:"); Serial.println(rc_values[RC_CH4]);
    for (int i = 0; i < RC_NUM_CHANNELS; ++i)
    {
      if (rc_values[i] > bd[i].maxRadio)
        bd[i].maxRadio = rc_values[i];
      else if (rc_values[i] < bd[i].minRadio)
        bd[i].minRadio = rc_values[i];
    }
  }

  for (int i = 0; i < RC_NUM_CHANNELS; ++i)
  {
    Serial.print("Max CH"); Serial.print(i); Serial.print("\t");
    Serial.print(bd[i].maxRadio); Serial.print("\t");
    Serial.print("Min CH"); Serial.print(i); Serial.print("\t");
    Serial.println(bd[i].minRadio);
  }

  Serial.println(F("\nSend any character to continue: "));
    
  while (Serial.available() && Serial.read()); // empty buffer
  while (!Serial.available());                 // wait for data
  while (Serial.available() && Serial.read()); // empty buffer again

}

void RadioDecoder::calc_input(uint8_t channel, uint8_t input_pin) {
  if (digitalRead(input_pin) == HIGH) {
    rc_start[channel] = micros();
  } else {
    uint16_t rc_compare = (uint16_t)(micros() - rc_start[channel]);
    rc_shared[channel] = rc_compare;
  }
}

void RadioDecoder::rc_read_values() {
  noInterrupts();
  memcpy(rc_values, (const void *)rc_shared, sizeof(rc_shared));
  interrupts();
}

float RadioDecoder::CtrInput(uint16_t inputRadio, int ch)
{
  float Q = abs(bd[ch].maxRadio-bd[ch].minRadio)/abs(bd[ch].maxCtr-bd[ch].minCtr);

  return abs(inputRadio-bd[ch].minRadio)/Q + bd[ch].minCtr;
}
