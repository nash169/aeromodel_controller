#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include "Arduino.h"
#include <Servo.h>

struct min_max
{
	float minCtr;
	float maxCtr;
	float minServo;
	float maxServo;
};

class Transmitter
{
public:
	Transmitter(int *pins);

	Transmitter();
	
	~Transmitter();

	void Initialize();

	inline float GetCtr(int ctr) { return controls[ctr]; }

	void SetCtr(float inputCtr, int ctr);

	float ServoInput(float inputCtr, int ctr);

protected:

private:
	enum
	{
		AILERON,
		ELEVATOR,
		RUDDER,
		THROTTLE,
		NUM_CONTROLS
	};

	int pins[NUM_CONTROLS];
	float controls[NUM_CONTROLS];
	Servo *ailServo,
		  *elevServo,
		  *rudServo,
		  *thrServo;
	min_max bd[NUM_CONTROLS];
};

#endif
