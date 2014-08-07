#ifndef IPEDO_H
#define IPEDO_H
#include "Pedometer.h"

/*
* Interface for event handler pedometer to determine movement and head tracking to determine
* orientation. 
*/
class IPedo : public IEvent
{
public:
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
	virtual bool pedometer(IRift * rift, Pedometer &pedo) = 0;

	/*
	 turn uses the gyrscope to decide whether the person has turned
	 and which direction they have turned
	
	@return
		Returns 0 if the person has not turned, 1 if the person has turned left, 2 if the person has turned right

	@param rift
		An instance of the Rift interfacing class

	@param pedo
		An instance of the Pedometer class
	*/
	virtual void turn(IRift *pRift, Pedometer &pedo) = 0;
};

#endif