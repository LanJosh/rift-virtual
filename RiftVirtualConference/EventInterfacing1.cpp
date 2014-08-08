#include "EventInterfacing1.h"

EventInterfacing1::EventInterfacing1()
{
}

EventInterfacing1::~EventInterfacing1()
{
}

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

	ip.ki.wVk = 0x57;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));

	//Release key
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
};

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
*
* @param pedo
*	An instance of the Pedometer class
*/
bool EventInterfacing1::pedometer(IRift *pRift, Pedometer &pedo)
{
	const float precision = 0.55; // A predetermined precision to filter the high frequency noise data.  May be adjusted or calibrated
	bool step = false; // Return value whether or not a step has been taken

	// Sample the accelerometer
	float sampleAcc = pRift->RawAcceleration().z;

	// Check change in acceleration against a predifined precision
	// If the change is too small, ignore it to smooth the high frequency noise
	if (abs(sampleAcc - pedo.getNewAcc()) > precision)
	{
		pedo.setNewAcc(sampleAcc);

		// If the new acceleration is lower than the current min, then update the min to the new acc
		// After a few readings, the accelerometer starts to drift positively
		// When the drift occurs, the min must start trailing the max upward or else
		// the dynamic threshold level will be thrown off by an increasing max and a stagnant min
		if (pedo.getNewAcc() < pedo.getMin())
		{
			pedo.updateMin(pedo.getNewAcc());
		}
	else if (pedo.getCTD() > pedo.getDTL() - pedo.getMin())
	{
		pedo.updateMin(pedo.getMax() - 2 * pedo.getCTD());
	}

	// If the new acceleration is greater than the current max, then update the max to the new acc
	// Also store the one most previous max reading
	if (pedo.getNewAcc() > pedo.getMax())
	{
		pedo.maxToMaxPrev();
		pedo.updateMax(pedo.getNewAcc());
	}

	// Index the counter
	if (pedo.getLoopCounter() < 60)
	{
		pedo.indexLoopCounter();
	}
	else
	{
		// Update the dynamic threshold level every 50 cycles and reset the counter to 0
		pedo.updateDTL();
		//Calibrated the CTD
		if (pedo.getMax()<2)
		{
			pedo.updateCTD();
		}
		pedo.resetLoopCounter();
	}

	if (pedo.getNewAcc() < pedo.getOldAcc() && pedo.getNewAcc() < pedo.getDTL() && pedo.getOldAcc() > pedo.getDTL())
	{
		step = true;
	}
	}
	// Store the acceleration value for the next cylce by copying NewAcc to OldAcc
	pedo.newToOldAcc();

	return step;
};

/*
* turn uses the gyrscope to decide whether the person has turned
* and which direction they have turned
*
* @return
*	Returns 0 if the person has not turned, 1 if the person has turned left, 2 if the person has turned right
*
* @param rift
*	An instance of the Rift interfacing class
*
* @param pedo
*	An instance of the Pedometer class
*/
void EventInterfacing1::turn(IRift *pRift, Pedometer &pedo)
{
	const float precision = 0.0698; // Predetermined precision to reduce noise from gyroscope (10 degrees)
	float sampleYaw = pRift->RawEulerAngles().yaw; // Sample the yaw angle from the gyroscope
	const float convert = 5000 /6.28; // Based on 5000 milliseconds per 2pi radians
	int turn; // Variable for determining how long to turn by converting radians to milliseconds
	
	// Set up keyboard input for movement
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	if (abs(sampleYaw - pedo.getOldYaw()) > precision)
	{
		if (pedo.getOldYaw() < sampleYaw)
		{
			if (pedo.getOldYaw() < -3 && sampleYaw > 3)
			{
				// std::cout << "R1" << std::endl;
				// Convert radians to degrees
				turn = 2 * (3.14 - abs(pedo.getOldYaw()) + 3.14 - abs(sampleYaw)) * convert;
			
				// Turn right
				// Press d key
				ip.ki.wVk = 0x44;
				ip.ki.dwFlags = 0;
				SendInput(1, &ip, sizeof(INPUT));
				// Sleep program for as long as needed to turn the correct distance
				Sleep(turn);
				//Release key
				ip.ki.dwFlags = KEYEVENTF_KEYUP;
				SendInput(1, &ip, sizeof(INPUT));
			}
			else
			{
				// std::cout << "L2" << std::endl;
				// Convert from radians to milliseconds
				turn = abs(sampleYaw - pedo.getOldYaw()) * convert;

				// Turn left
				// Press a key
				ip.ki.wVk = 0x41;
				ip.ki.dwFlags = 0;
				SendInput(1, &ip, sizeof(INPUT));
				// Sleep program for as long as needed to turn the correct distance
				Sleep(turn);
				//Release key
				ip.ki.dwFlags = KEYEVENTF_KEYUP;
				SendInput(1, &ip, sizeof(INPUT));
			}
		}
		else if (pedo.getOldYaw() > sampleYaw)
		{
			if (pedo.getOldYaw() > 3 && sampleYaw < -3)
			{
				// std::cout << "L1" << std::endl;
				// Convert from radians to milliseconds
				turn = 2 * (3.14 - abs(pedo.getOldYaw()) + 3.14 - abs(sampleYaw)) * convert;
				
				// Turn left
				// Press a key
				ip.ki.wVk = 0x41;
				ip.ki.dwFlags = 0;
				SendInput(1, &ip, sizeof(INPUT));
				// Sleep program for as long as needed to turn the correct distance
				Sleep(turn);
				//Release key
				ip.ki.dwFlags = KEYEVENTF_KEYUP;
				SendInput(1, &ip, sizeof(INPUT));
			}
			else
			{
				// std::cout << "R2" << std::endl;
				// Convert radians to milliseconds
				turn = abs(pedo.getOldYaw() - sampleYaw) * convert;
				// Turn right
				// Press d key
				ip.ki.wVk = 0x44;
				ip.ki.dwFlags = 0;
				SendInput(1, &ip, sizeof(INPUT));
				// Sleep program for as long as needed to turn the correct distance
				Sleep(turn);
				//Release key
				ip.ki.dwFlags = KEYEVENTF_KEYUP;
				SendInput(1, &ip, sizeof(INPUT));
			}
		}

		// Update OldYaw
		pedo.newToOldYaw(sampleYaw);
	}
};
