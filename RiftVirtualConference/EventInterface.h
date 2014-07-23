#ifndef EVENTINTERFACING_H
#define EVENTINTERFACING_H
#include <vector>
#include "RVCInterface.h"

class IEvent
{
public:
	/*
	 Sets the threshold value checking acceleration and decceleration.
	
	
	 @param acc
		The new value to be used as a threshold to determine if acceleration means we 
		began walking.
			if (not walking) acceleration < acc
	 @param decc
		The new values to be used as a threshold to determine if decceleration means we
		have stopped walking.
			if (walking) deceleration > decc
	 @updates walkAcc, walkDecc
		Changes walkAcc to new acceleration and walkDecc to new threshold.
			walkAcc = acc && walkDecc = decc
	*/
	virtual void setThreshold(float acc, float decc) = 0;

	/*
	 Finds and returns threshold values for acceleration to walking.
	
	 @param accData
		A vector of floats that represents the acceleration of a person
		from the rest to the instant they reach walking speed.

	 @requires 
		Acceleration data is valid
			accData.length > 0 && accData != NULL
	
	 @return 
		A threshold value that signifies that a person has begun walking.
	*/
	virtual float findAccelerationThreshold(std::vector<float> accData) = 0;

	/*
	 Finds and returns threshold values for decceleration to stop.
	
	 @param accData
		A vector of floats that represents the decceleration of a person
		from walking speed to the instant they reach rest.

	 @return
		A threshold value that signifies that a person has begun to stop walking.
	*/
	virtual float findDeccelerationThreshold(std::vector<float> accData) = 0;

	/*
	 Pedometer using accelerometer in the Oculus Rift. 
	
	 @param *rift
		A connection to the rift. 

	 @requires
		*rift is a valid connection

	 @return
		Returns true if the person is walking and returns false if the person is not
			if (walking) return true
			else return false
	*/
	virtual bool pedometer(IRift * rift) = 0;

	/*
	 Pedometer using accelerometer in the Oculus Rift. 
	
	 @return
		Returns true if the person is walking and returns false if the person is not
			if (walking) return true
			else return false
	*/
	virtual bool pedometer() = 0;

	// This (move) is likely the function that will change the most if future interns are able to establish a direct connection to OpenSim
	// or build a viewer. Much of the other algorithms should require NO change and future interns should be careful
	// to discard the work already done. 

	/*
	 Moves the avatar in virtual world. 
	
	 @requires
		There is a connection to OpenSim.
	*/
	virtual void move() = 0;

	/*
	 Virtual destructor
	*/
	virtual ~IEvent(){};
};

#endif