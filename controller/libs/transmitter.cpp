#include "transmitter.h"

Transmitter::Transmitter(int *pins)
{
	for (int i = 0; i < NUM_CONTROLS; ++i){
		controls[i] = 0;
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
	bd[AILERON].minCtr = -15;
  	bd[AILERON].maxCtr = 15;
  	bd[AILERON].minServo = 50;
  	bd[AILERON].maxServo = 130;
	SetCtr(controls[AILERON], AILERON);

	// ELEVATOR
	elevServo = new Servo;
	elevServo->attach(pins[ELEVATOR]);
	bd[ELEVATOR].minCtr = -15;
  	bd[ELEVATOR].maxCtr = 15;
  	bd[ELEVATOR].minServo = 20;
  	bd[ELEVATOR].maxServo = 160;
	SetCtr(controls[ELEVATOR], ELEVATOR);

	// RUDDER
	rudServo = new Servo;
	rudServo->attach(pins[RUDDER]);
	bd[RUDDER].minCtr = -15;
  	bd[RUDDER].maxCtr = 15;
  	bd[RUDDER].minServo = 20;
  	bd[RUDDER].maxServo = 160;
	SetCtr(controls[RUDDER], RUDDER);

  	// THROTTLE (dummy values)
	thrServo = new Servo;
	thrServo->attach(pins[THROTTLE]);
	bd[THROTTLE].minCtr = -15;
  	bd[THROTTLE].maxCtr = 15;
  	bd[THROTTLE].minServo = 50;
  	bd[THROTTLE].maxServo = 150;
	SetCtr(controls[THROTTLE], THROTTLE);
}

void Transmitter::SetCtr(float inputCtr, int ctr)
{
	float inputServo = ServoInput(inputCtr, ctr);

	switch(ctr){
		case AILERON:
			ailServo->write(inputServo);
			controls[AILERON] = inputCtr;
			break;
		case ELEVATOR:
			elevServo->write(inputServo);
			controls[ELEVATOR] = inputCtr;
			break;
		case RUDDER:
			rudServo->write(inputServo);
			controls[RUDDER] = inputCtr;
			break;
		case THROTTLE:
			thrServo->write(inputServo);
			controls[THROTTLE] = inputCtr;
			break;
		default:
			break;
	}
}

float Transmitter::ServoInput(float inputCtr, int ctr)
{
  float Q = abs(bd[ctr].maxCtr-bd[ctr].minCtr)/abs(bd[ctr].maxServo-bd[ctr].minServo);

  return abs(inputCtr-bd[ctr].minCtr)/Q + bd[ctr].minServo;
}

