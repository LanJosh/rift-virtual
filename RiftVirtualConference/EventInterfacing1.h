#ifndef EVENTINTERFACING1_H
#define EVENTINTERFACING1_H
#include "IEvent.h"
#include "IPedo.h"

class EventInterfacing1 : public IPedo
{
private:
	float walkAcc;
	float walkDecc;
	
public:
	/*
	 Constructor
	*/
	EventInterfacing1::EventInterfacing1();

	/*
	 Destructor
	*/
	EventInterfacing1::~EventInterfacing1();

	/*
	 Simple implementation of movement in OpenSim. If threshold values are broken, we
	 move the avatar in virtual world by "pressing" a key.
	*/
	void move();

	/*
	 Pedometer using accelerometer in the Oculus Rift. 
	*/
	bool pedometer(IRift *rift, Pedometer &pedo);

	/*
	 Turns body in OpenSim
	*/
	void turn(IRift *pRift, Pedometer &pedo);
};
#endif