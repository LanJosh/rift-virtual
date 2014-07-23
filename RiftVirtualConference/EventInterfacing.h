#include "EventInterface.h"

class EventInterfacing : public IEvent
{
private:
	float walkAcc;
	float walkDecc;
	IRift * rift;

public:
	EventInterfacing::EventInterfacing(IRift *connection, float accThreshold, float deccThreshold);

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
	 Returns true if walking and false if not
	*/
	bool pedometer();

	/*
	 Returns true if walking and false if not
	*/
	bool pedometer(IRift * rift);
	
};