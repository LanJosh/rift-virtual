#ifndef EVENTINTERFACING_H
#define EVENTINTERFACING_H
#include <vector>
#include "RVCInterface.h"

class IEvent
{
public:
	/*
	* Sets the threshold value checking acceleration and decceleration.
	*
	* @updates walkAcc, walkDecc
	*	Changes walkAcc to new acceleration and walkDecc to new threshold
	*		walkAcc = acc && walkDecc = decc
	*/
	virtual void setThreshold(float acc, float decc) = 0;

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
	virtual float findAccelerationThreshold(std::vector<float> & accData) = 0;

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
	virtual float findAccelerationThreshold(float accData[]) = 0; 

	/*
	* Finds and returns threshold values for decceleration to stop.
	*
	* @return
	*	A threshold value that signifies that a person has begun to stop walking
	*/
	virtual float findAccelerationThreshold(std::vector<float> accData) = 0;

	/*
	* Finds and returns threshold values for decceleration to stop.
	*
	* @return
	*	A threshold value that signifies that a person has begun to stop walking
	*/
	virtual float FindDeccelerationThreshold(float accData[]) = 0;

	/*
	* Pedometer using accelerometer in the Oculus Rift. 
	*
	* @return
	*	Returns true if the person is walking and returns false if the person is not
	*		if (walking) return true
	*		else return false
	*/
	virtual bool pedometer(IRift * rift) = 0;

	/*
	* Pedometer using accelerometer in the Oculus Rift. 
	*
	* @return
	*	Returns true if the person is walking and returns false if the person is not
	*		if (walking) return true
	*		else return false
	*/
	virtual bool pedometer() = 0;

	// This (move) is likely the function that will change the most if future interns are able to establish a direct connection to OpenSim
	// or build a viewer. Much of the other algorithms should require NO change and future interns should be careful
	// to discard the work already done. 

	/*
	* Moves the avatar in virtual world. 
	*
	* @requires
	*	There is a connection to OpenSim.
	*/
	virtual void move() = 0;

	/*
	* Virtual destructor
	*/
	virtual ~IEvent(){};
};

#endif