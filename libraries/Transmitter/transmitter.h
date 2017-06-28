#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include "Arduino.h"
#include <Servo.h>

class Transmitter
{
public:
	Transmitter(int *pins);

	Transmitter();
	
	~Transmitter();

	void Initialize();

	inline float GetAil() { return surfs[AILERON]; }
	inline float GetElev() { return surfs[ELEVATOR]; }
	inline float GetRud() { return surfs[RUDDER]; }

	void SetAil(float ail_val);
	void SetElev(float elev_val);
	void SetRud(float rud_val);

protected:

private:
	enum
	{
		AILERON,
		ELEVATOR,
		RUDDER,
		SURFS
	};

	int pins[SURFS];
	float surfs[SURFS];
	Servo *ailServo,
		  *elevServo,
		  *rudServo;
};

#endif
