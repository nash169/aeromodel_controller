#include "transmitter.h"

Transmitter::Transmitter(int *pins)
{
	for (int i = 0; i < SURFS; ++i){
		surfs[i] = 0;
		this->pins[i] = pins[i];
	}
}

Transmitter::Transmitter() { }

Transmitter::~Transmitter() { }

void Transmitter::Initialize()
{
	// AILERON
	ailServo = new Servo;
	ailServo->attach(pins[AILERON]);
	SetAil(surfs[AILERON]);

	// ELEVATOR
	elevServo = new Servo;
	elevServo->attach(pins[ELEVATOR]);
	SetElev(surfs[ELEVATOR]);

	// RUDDER
	rudServo = new Servo;
	rudServo->attach(pins[RUDDER]);
	SetRud(surfs[RUDDER]);
}

void Transmitter::SetAil(float ail_val)
{
	float ailIN;
	ailIN = 8./3.*(ail_val + 15.) + 50.;
	ailServo->write(ailIN);
	surfs[AILERON] = ail_val;
}

void Transmitter::SetElev(float elev_val)
{
	float elevIN;
	elevIN = 14./3.*(elev_val + 15.) + 20.;
	elevServo->write(elevIN);
	surfs[ELEVATOR] = elev_val;
}

void Transmitter::SetRud(float rud_val)
{
	float rudIN;
	rudIN = 14./3. * (rud_val+15.) + 20.;
	rudServo->write(rudIN);
	surfs[RUDDER] = rud_val;
}

