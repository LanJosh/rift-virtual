#ifndef ITHRESH_H
#define ITHRESH_H
#include <vector>
#include "OrientationList.h"

/*
* Interface for determining movement from acceleration thresholds and determine orientation using the
* OList interface. 
*/
class IThresh : public IEvent
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
	 Orients the avatars body to the position 
	 the position of the users head

	 @requires
		There is a connectino to OpenSim.
	 */
	virtual void orientBody(IList *orientation) = 0;
};

#endif