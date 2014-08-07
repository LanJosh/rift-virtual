#ifndef EVENINTERFACING_H
#define EVENTINTERFACING_H
#include "IEvent.h"
#include "IThresh.h"

class EventInterfacing : public IThresh
{
private:
	float walkAcc;
	float walkDecc;
	IRift * rift;

public:
	/*
	 Constructor
	*/
	EventInterfacing::EventInterfacing(IRift *connection, float accThreshold, float deccThreshold);

	/*
	 Destructor
	*/
	EventInterfacing::~EventInterfacing();

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
	 Simple implementation of movement in OpenSim. 
	*/
	void move();

	/*
	 Orients virtual body.
	*/
	void orientBody(IList *orientation);
};
#endif