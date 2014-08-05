#include "EventInterfacing1.h"

EventInterfacing1::EventInterfacing1(IRift *connection, float accThreshold, float deccThreshold)
{
	this->rift = connection;
	this->walkAcc = accThreshold;
	this->walkDecc = deccThreshold;
}

EventInterfacing1::~EventInterfacing1()
{
	this->rift->clear();
}
/*
 Sets threshold values for acceleration and decceleration.
*/
void EventInterfacing1::setThreshold(float acc, float decc)
{
	this->walkAcc = acc;
	this->walkDecc = decc;
}

/*
  Orients virtual body in response to the head position recorded
  by the Oculus Rift.
 */
void EventInterfacing1::orientBody(IList *orientation)
{
	// 15 degree change in yaw orientation corresponds to one keystroke in OpenSim
	const int DEGREE_RATIO = 15;
	// Determine position
	EulerAngles ang = this->rift->RawEulerAngles();

	// Change to position in list. We do this in order to create feasible
	// thresholds--the Oculus is too sensitive for each degrees. The integer division
	// here is intended. The reason for this is important and is left to you 
	// to figure out (but is pretty simple).
	int pos = OVR::RadToDegree(ang.yaw) / DEGREE_RATIO;

	// Determine position as modeled in the list
	int currPos = orientation->position();
	// If we are ahead in the list, retreat until we are oriented.
	while (currPos < pos)
	{
		orientation->retreat();
		currPos = orientation->position();
	}  

	// If we are behind in the list, advance until we are oriented.
	while (currPos > pos)
	{
		orientation->advance();
		currPos = orientation->position();
	};
};

/*
 Finds and returns threshold values for acceleration to walking.
*/
float EventInterfacing1::findAccelerationThreshold(std::vector<float> accData)
{
	// TODO write algorithm to quickly find a threshold for beginning walking from a vector.
	return 0;
};

/*
 Finds and returns threshold values for decceleration to stop.
*/
float EventInterfacing1::findDeccelerationThreshold(std::vector<float> accData)
{
	// TODO write algorithm to quickly find threshold for decceleration.
	return 0;
};

/*
 Simple implementation of movement in OpenSim. If threshold values are broken, we
 move the avatar in virtual world by "pressing" a key.
*/
void EventInterfacing1::move()
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
			zAccel = this->rift->CorrectedAcceleration().z;
		}
	}

	//Release key
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
};

/*
  Orients virtual body in response to the head position recorded
  by the Oculus Rift.
 */
void EventInterfacing1::orientBody(IList *orientation)
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
	while (currPos < pos)
	{
		orientation->retreat();
	}  

	// If we are behind in the list, advance until we are oriented.
	while (currPos > pos)
	{
		orientation->advance();
	};
};

/*
 Pedometer using accelerometer in the Oculus Rift. 
*/
bool EventInterfacing1::pedometer(IRift *pRift, Pedometer &pedo)
{
	const float precision = 0.15; // A predetermined precision to filter the high frequency noise data.  May be adjusted or calibrated
	bool step = false; // Return value whether or not a step has been taken

	// Sample the accelerometer
	float sampleResult = pRift->RawAcceleration().z;

	// Check change in acceleration against a predifined precision
	// If the change is too small, ignore it to smooth the high frequency noise
	if(abs(sampleResult - pedo.getNewAcc()) > precision)
	{
		pedo.setNewAcc(sampleResult);
	}

	// If the new acceleration is lower than the current min, then update the min to the new acc
	// After a few readings, the accelerometer starts to drift positively
	// When the drift occurs, the min must start trailing the max upward or else
	// the dynamic threshold level will be thrown off by an increasing max and a stagnant min
	if(pedo.getNewAcc() < pedo.getMin())
	{
		pedo.updateMin(pedo.getNewAcc());
	}
	else if(pedo.getDTD() > pedo.getDTL() - pedo.getMin())
	{
		pedo.updateMin(pedo.getMax() - 2 * pedo.getDTD());
	}

	// If the new acceleration is greater than the current max, then update the max to the new acc
	// Also store the one most previous max reading
	if(pedo.getNewAcc() > pedo.getMax())
	{
		pedo.maxToMaxPrev();
		pedo.updateMax(pedo.getNewAcc());
	}

	// Index the counter
	if(pedo.getLoopCounter() < 60)
	{
		pedo.indexLoopCounter();
	}
	else
	{
		// Update the dynamic threshold level every 50 cycles and reset the counter to 0
		pedo.updateDTL();
		//Calibrated the CTD
		if(pedo.getMax()<2)
		{
			pedo.updateDTD();
		}
		pedo.resetLoopCounter();
	}

	if(pedo.getNewAcc() < pedo.getOldAcc() && pedo.getNewAcc() < pedo.getDTL() && pedo.getOldAcc() > pedo.getDTL())
	{
		step = true;
	}

	// Store the acceleration value for the next cylce by copying NewAcc to OldAcc
	pedo.newToOld();

	return step;
	return false;
};
