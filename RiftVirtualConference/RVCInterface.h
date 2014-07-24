#ifndef RVCINTERFACE_H
#define RVCINTERFACE_H
#include "OVR.h"
#include "EulerAngles.h"

//Abstract base class

/*
Connection to an Oculus Rift. Provides information about
head position from Oculus Rift.
*/
class IRift
{
public:
	/*
	 Initializes the Oculus Rift connection.
	
	*/
	virtual void init() = 0;

	/*
	 Clears the Oculus Rift connection.
	*/
	virtual void clear() = 0;
	

	/*
	 Return raw acceleration data from the Oculus Rift
	
	 @requires
		The Rift connection must be connected properly.
			pSensor == true
	
	 @return 
		The raw acceleration data.
			< x, y, z> == accelerations in 3D
	*/
	virtual OVR::Vector3f RawAcceleration() = 0;

	/*
	 Return raw Euler angles in radians from the Oculus Rift
	
	 @requires
		The Rift is connected properly
			pSensor
	
	 @return
		instance of class EulerAngles such that EulerAngles.yaw = yaw 
												EulerAngles.pitch = pitch 
												EulerAngles.roll = roll 
		 = of Oculus Rift at the time of the call.
	*/
	virtual EulerAngles RawEulerAngles() = 0;

	/*
	 Return the raw orientation of the Oculus Rift in the form of a quaternion
	
	 @requires
		The Rift is connected properly
			pSensor
	
	 @return
		A quaternion representing the orientation of the Oculus Rift at the time of
		the call
	*/
	virtual OVR::Quatf RawOrientation() = 0;

	/*
	 Return gravity corrected acceleration of the Oculus Rift.
	
	 @requires
		The rift is connected properly && the standard gravity of the environment
		is near to 9.81.
			pSensor && STD_GRAV == tolerance(9.81);
	
	 @return
		The acceleration of the Oculus Rift corrected for gravity
			<x, y, z> == acceleration in 3D - given that the z acceleration = z acceleration - ((9.81 m/s/s)sin(pitch)) 
	*/
	virtual OVR::Vector3f CorrectedAcceleration() = 0;

	/*
	 Virtual destructor
	*/
	virtual ~IRift(){};
};

#endif