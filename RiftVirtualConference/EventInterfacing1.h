#include "EventInterface.h"

class EventInterfacing1 : IEvent
{
private:
	float walkAcc;
	float walkDecc;
	IRift * rift;
	
public:

	/*
	* Constructor
	*/
	EventInterfacing1::EventInterfacing1();

	/*
	* Destructor
	*/
	EventInterfacing1::~EventInterfacing1();

	/*
	* Sets threshold values for acceleration and decceleration.
	*
	* @updates walkAcc, walkDecc
	*	Updates walkAcc and walkDecc to the values passed in.
	*		walkAcc = acc && walkDecc = decc
	*/
	void setThreshold(float acc, float decc);

	/*
	* Finds and returns threshold values for acceleration to walking.
	*
	* @requires 
	*	Acceleration data is valid
	*		accData.length > 0 && accData != NULL
	*
	* @return 
	*	A threshold value that signifies that a person has begun walking
	*/
	float findAccelerationThreshold(std::vector<float> & accData);

	/*
	* Finds and returns threshold values for decceleration to stop.
	*
	* @return
	*	A threshold value that signifies that a person has begun to stop walking
	*/
	float findDeccelerationThreshold(std::vector<float> accData);
	/*
	* Simple implementation of movement in OpenSim. If threshold values are broken, we
	* move the avatar in virtual world by "pressing" a key.
	*
	*/
	void move();
	/*
	* Pedometer using accelerometer in the Oculus Rift. 
	*
	* @return
	*	Returns true if the person is walking and returns false if the person is not
	*		if (walking) return true
	*		else return false
	* 
	* @param rift
	*	An instance of the Rift interfacing class
	*/
	bool pedometer(IRift *rift);

	/*
	* Pedometer using accelerometer in the Oculus Rift. 
	*
	* @return
	*	Returns true if the person is walking and returns false if the person is not
	*		if (walking) return true
	*		else return false
	*/
	bool pedometer();
};