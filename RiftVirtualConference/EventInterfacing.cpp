#include "EventInterfacing.h"
#include "OrientationList.h"

EventInterfacing::EventInterfacing(IRift *connection, float accThreshold, float deccThreshold)
{
	this->rift = connection;
	this->walkAcc = accThreshold;
	this->walkDecc = deccThreshold;
}

EventInterfacing::~EventInterfacing()
{
	this->rift = NULL;
	this->walkAcc = NULL;
	this->walkDecc = NULL;
};

/*
 Changes the standrad threshold for determining if we have started or stopping walking to the arguments.
*/
void EventInterfacing::setThreshold(float acc, float decc)
{
	this->walkAcc = acc;
	this->walkDecc = decc;
}

/*
 Finds and returns threshold values for acceleration to walking.

 @requires 
	Acceleration data is valid
		accData.length > 0 && accData != NULL

 @return 
	A threshold value that signifies that a person has begun walking
*/
float EventInterfacing::findAccelerationThreshold(std::vector<float> accData)
{
	// TODO write algorithm to quickly find a threshold for beginning walking from a vector.
	return 0;
};

/*
 Finds and returns threshold values for decceleration to stop.

 @return
	A threshold value that signifies that a person has begun to stop walking
*/
float EventInterfacing::findDeccelerationThreshold(std::vector<float> accData)
{
	// TODO write algorithm to quickly find threshold for decceleration.
	return 0;
};

/*
  Sets up virtual keyboard. If walking we hit a keystroke corresponding to 
  foward movement in the virtual world. 
*/
void EventInterfacing::move()
{
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	float zAccel = this->rift->CorrectedAcceleration().z;
	// If we detect acceleration, assume walking until we detect deceleration
	if (zAccel < this->walkAcc)
	{
		// Once we detected decceleration, stop walking.
		while (zAccel < this->walkDecc)
		{
			ip.ki.wVk = 0x57;
			ip.ki.dwFlags = 0;
			SendInput(1, &ip, sizeof(INPUT));
			zAccel = rift->CorrectedAcceleration().z;

			// Release key
			ip.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &ip, sizeof(INPUT));
		}
	};
};

/*
  Orients virtual body in response to the head position recorded
  by the Oculus Rift.
 */
void EventInterfacing::orientBody(IList *orientation)
{
	// 15 degree change in yaw orientation corresponds to one keystroke in OpenSim
	const int DEGREE_RATIO = 15;

	// Determine position
	EulerAngles ang = this->rift->RawEulerAngles();

	// Change to position in list. We do this in order to create feasible
	// thresholds--the Oculus is too sensitive for each degrees. The integer division
	// here is intended. The reason for this is important and is left to you 
	// to figure out (but is pretty simple).
	int pos = ang.yaw / DEGREE_RATIO;

	// Determine position as modeled in the list
	int currPos = orientation->position();

	// If we are ahead in the list, retreat until we are oriented.
	while (currPos > pos)
	{
		orientation->retreat();
		currPos = orientation->position();
	}  

	// If we are behind in the list, advance until we are oriented.
	while (currPos < pos)
	{
		orientation->advance();
		currPos = orientation->position();
	};
};

	