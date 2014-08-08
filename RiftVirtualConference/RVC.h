#ifndef RVC_H
#define RVC_H
#include "IRIFT.h"
#include <string>
#include <utility>
#include <iostream>

// Only using the namespace here because this class is made
// strictly to communicate with the Rift.

class RVC : public IRift
{
	/*
	* For future interns: Quick learning opportunity here for writing better code.
	* There is a reason these are private. If they were public, and we sent this code
	* to another team working on the Oculus Rift as a library (just the RVC class), they could
	* write code that called these members from the class. If we updated the code to a new SDK
	* and they used these members--their code would break! Likely they would have no idea why
	* as they would not be seeing this part or know the entirety of the SDK update, resulting
	* in ambiguous error messaging and general displeasure with us. Make sure to consider things like
	* this when you write new classes and actually consider and wrestle with access levels, rather than
	* just taking a sledgehammer with public so code is easier for you to write. Easily made can mean easily broken!
	*/
private:
	OVR::Ptr<OVR::DeviceManager>	pManager;
	OVR::Ptr<OVR::HMDDevice>		pHMD;
	OVR::Ptr<OVR::SensorDevice>	pSensor;
	OVR::SensorFusion*		pFusionResult;
	OVR::HMDInfo			Info;
	bool			InfoLoaded;

public:
	/*
	* Initializes the connection to the Oculus Rift. More about this and clear is shown in the Minimal Oculus 
	* tutorial for SDK 0.2.5c. This is deprecated as of DK2, but at the time of implementation we
	* did not have DK2s and therefore choose not to use SDK 0.3.x. If new Oculus Rifts are bought by the 
	* lab or the consumer version is release it is EXTREMELY important to update this program. Though direct changes
	* are clearly needed within these functions, it is likely this entire program will be
	* deprecated by the time of release (as the API will change on release). All conventions and algorithms will likely hold,
	* updates should just be rolling in new functions/updating deprecated ones.
	*
	* Comments like the one above I will try to avoid as it populates the code too much and hurts readability. In practice, things like this will
	* never be commented--I'm working on the assumption that, much like my team now, there is not much experience on the team
	* (including me) so these comments should save you some time reading through tutorials and teach you a little about programming conventions
	* my team and I have found helpful for keeping our code good and not just "working".
	*/
	void init();

	/*
	* Clears and destroys connection to the Oculus Rift
	*/
	void clear();

	/*
	* Constructor. Initializes the Rift.
	*/ 
	RVC::RVC();

	/*
	* Destructor. Closes and destroys Rift connection
	*/
	RVC::~RVC();

	/*
	* Returns uncorrected and unfiltered Euler Angles. 
	*/
	EulerAngles RawEulerAngles();

	/*
	* Returns uncorected and unfiltered acceleration data from the Oculus Rift. 
	*/
	OVR::Vector3f RawAcceleration();

	/*
	* Returns unfiltered and uncorrected orientation data from the Oculus Rift.
	*/
	OVR::Quatf RawOrientation();

	/*
	* Returns corrected and filtered acceleration data from the Oculus Rift.
	*/
	OVR::Vector3f CorrectedAcceleration();
};

#endif