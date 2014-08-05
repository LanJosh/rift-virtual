#ifndef EVENTINTERFACING1_H
#define EVENTINTERFACING1_H
#include "EventInterface.h"

class EventInterfacing1 : public IEvent
{
private:
	float walkAcc;
	float walkDecc;
	IRift * rift;
	
public:
	/*
	 Constructor
	*/
	EventInterfacing1::EventInterfacing1(IRift *connection, float accThreshold, float deccThreshold);

	/*
	 Destructor
	*/
	EventInterfacing1::~EventInterfacing1();

	/*
	 Sets threshold values for acceleration and decceleration.
	*/
	void setThreshold(float acc, float decc);

	/*
	 Finds and returns threshold values for acceleration to walking.
	*/
	float findAccelerationThreshold(std::vector<float> accData);

	/*
	 Finds and returns threshold values for decceleration to stop.
	*/
	float findDeccelerationThreshold(std::vector<float> accData);


	/*
	 Simple implementation of movement in OpenSim. If threshold values are broken, we
	 move the avatar in virtual world by "pressing" a key.
	*/
	void move();

	/*
	 Orients body.
	*/
	void orientBody(IList *orientation);

	/*
	 Pedometer using accelerometer in the Oculus Rift. 
	*/
	bool pedometer(IRift *rift, Pedometer &pedo);
};
#endif