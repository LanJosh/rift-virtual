#include "Samples.h"
#include "RVC.h"
#include "EventInterfacing.h"
#include "OrientationList.h"
#include "Pedometer.h"
#include <conio.h>
#include <string>
#include "EventInterfacing1.h"

/*
 Sample shows using the the Rift object and getting orientation data from it.
*/
void Orientation()
{
	// Connect to rift
	std::cout << "Connecting to Oculus Rift" << std::endl;
	RVC rift;
	std::cout << "Getting acceleration data" << std::endl;
	std::cout << "Printing acceleration data, press any key to exit" << std::endl;
	while (true)
	{
		// Get the Euler angles. It is possible to get orientation
		// in different structures--check the documentation 
		EulerAngles ang = rift.RawEulerAngles();
		// Euler angles are returned in radians. Note that we use 
		// RadToDegree from Oculus' OVR. We did not hide this (IRift is just 
		// hiding Oculus SDK to make it easier for us to use and update) 
		// because it is unlikely to change but trivial to implement. 
		// if you get some weird errors, it could be because of this. 
		std::cout << "Roll: " << OVR::RadToDegree(ang.roll)
			<< " Pitch: " << OVR::RadToDegree(ang.pitch)
			<< " Yaw: " << OVR::RadToDegree(ang.yaw) << std::endl;
		if (_kbhit())
		{
			std::cout << "End orientation sample" << std::endl;
			break;
		};
	};
};

/*
 Demonstration of how to get accleration data using the RVC object.
*/
void Acceleration()
{
	std::cout << "Connecting to Oculus Rift" << std::endl;
	RVC rift;
	std::cout << "Begin printing acceleration data" << std::endl
	 << "rX is raw acceleration, cX is corrected acceleration" << std::endl
	 << "Press any key to stop demo" << std::endl;
	while (true)
	{
		// Again we use something from rift outside of the rift class.
		// This should NOT be done as the rift is still in development
		// and this may change. We use it here simply to show the data hiding.
		// (though that seems contradictory, we do it simply to maintain transparency
		// and because we might not be here to maintain backend and you will need to know how)

		OVR::Vector3f acc = rift.RawAcceleration();
		OVR::Vector3f cAcc = rift.CorrectedAcceleration();
		std::cout << "rX: " << acc.x 
			<< "rY: " << acc.y
			<< "rZ: " << acc.z << std::endl;
		std::cout << "cX: " << cAcc.x
			<< "cY: " << cAcc.y
			<< "cZ: " << cAcc.z << std::endl;
		if (_kbhit())
		{
			std::cout << "End acceleration sample" << std::endl;
			break;
		}
	};
};

/*
 Demonstration of using EventInterfacing to determine movement.
*/
void PeakAnalysisDemo()
{

	std::cout << "Connecting to Oculus Rift" << std::endl;
	RVC rift;
	IRift* pRift = &rift;

	// Set up the event handler for controlling the rift.
	// Constants -1 and -1.5 are threshold values for acceleration and decceleration--here they are hard coding for simplicity.
	std::cout << "Opening connection to OpenSim" << std::endl;

	EventInterfacing eventHandler(pRift, (float) -1, (float) -1.5);
	IThresh* pEventHandler = &eventHandler;
	// Set up an infite loop to continually poll the event handler.
	std::cout << "Begin sync to virtual world" << std::endl;
	std::cout << "Press enter to exit virtual conferencing" << std::endl;
	while (true)
	{
		// Tell the event handler to coordinate rift with virtual world. 
		pEventHandler->move();
		// Allow the user to  exit!
		if (_kbhit())
		{
			std::cout << "Ending connection to virtual world" << std::endl;
			break;
		};
	};
};

/*
 Demonstration of using EventInterfacing to determine head position and move.
*/
void PeakAnalysisWithListHeadtrackingDemo()
{
	std::cout << "Connecting to Oculus Rift" << std::endl;
	RVC rift;
	IRift* pRift = &rift;

	std::cout << "Opening connection to OpenSim" << std::endl;

	// Set up the event handler for controlling the rift.
	// Constants -1 and -1.5 are threshold values for acceleration and decceleration--here they are hard coding for simplicity.
	EventInterfacing eventHandler(pRift, (float) -1, (float) -1.5);
	IThresh* pEventHandler = &eventHandler;

	// Set up the orientation as a virtual representation and data structure.
	std::cout << "Configuring your virtual representation" << std::endl;
	OList virtRep;
	IList* pVirtRep = &virtRep;

	std::cout << "Begin Sync to Virtual World" << std::endl;
	std::cout << "Press 'q' to quit Virtual Conferencing" << std::endl;
	std::string sentinel;
	do
	{
		// Tell the event handler to coordinate rift with virtual world. 
		pEventHandler->move();

		// Orient body with virtual world
		pEventHandler->orientBody(pVirtRep);

		sentinel = _getch();
	} while (sentinel != "q");
};

/*
 Demonstration of using EventInterfacing to determine head position.
*/
void HeadtrackingWithList()
{
	std::cout << "Setting up data representation" << std::endl;
	OList orient;
	IList* pOrient = &orient;

	std::cout << "Connecting to Rift" << std::endl;
	RVC rift;
	IRift* pRift = &rift;

	std::cout << "Creating interfacing" << std::endl;
	EventInterfacing eventHandler(pRift, (float) -1, (float) -1.5);
	IThresh* pEventHandler = &eventHandler;

	std::cout << "Press enter to begin" << std::endl;
	std::cin.get();

	std::cout << "Printing data orientation value" << std::endl;
	std::string sentinel;
	do
	{
		pEventHandler->orientBody(pOrient);
		std::cout << "position: " << pOrient->position() << std::endl;
		sentinel = _getch();
	} while (sentinel != "q");

	std::cout << "Exiting Headtracking Demo" << std::endl;
};

/*
 Demonstration using EventInterfacing1 to determine movement.
*/
void PedometerDemo(){
	std::cout << "Connecting to Oculus Rift" << std::endl;
	RVC rift;
	std::cout << "Connecting to virtual world" << std::endl;
	EventInterfacing1 eventHandler;
	IPedo* pEventHandler = &eventHandler;

	std::string sentinel;
	do 
	{
		pEventHandler->move();
	} while (sentinel != "q");
};
