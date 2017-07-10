#ifndef RADIO_DECODER_H
#define RADIO_DECODER_H

#include "Arduino.h"

#define RC_NUM_CHANNELS  4

#define RC_CH1  0
#define RC_CH2  1
#define RC_CH3  2
#define RC_CH4  3

#define RC_CH1_INPUT  A0 // AILERON
#define RC_CH2_INPUT  A1 // ELEVATOR
#define RC_CH3_INPUT  A2 // RUDDER
#define RC_CH4_INPUT  A3 // THROTTL

struct max_min
{
	uint16_t minRadio;
	uint16_t maxRadio;
	float minCtr;
	float maxCtr;
};

class RadioDecoder
{
public:
	RadioDecoder();
	~RadioDecoder();

	void Initialize();

	void Calibrate();

	void rc_read_values();

	void calc_input(uint8_t channel, uint8_t input_pin);

	float CtrInput(uint16_t inputRadio, int ch);

	inline uint16_t GetChannel(uint8_t channel) { return rc_values[channel]; }
protected:

private:
	uint16_t rc_values[RC_NUM_CHANNELS];
	uint32_t rc_start[RC_NUM_CHANNELS];
	volatile uint16_t rc_shared[RC_NUM_CHANNELS];
	max_min bd[RC_NUM_CHANNELS];
};

#endif // RADIO_DECODER_H