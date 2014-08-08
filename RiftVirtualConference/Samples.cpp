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

	IRift* pRift = &RVC();

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

	IRift* pRift = &RVC();

	std::cout << "Opening connection to OpenSim" << std::endl;

	// Set up the event handler for controlling the rift.
	// Constants -1 and -1.5 are threshold values for acceleration and decceleration--here they are hard coding for simplicity.
	IThresh* pEventHandler = &EventInterfacing(pRift, (float) -1, (float) -1.5);

	// Set up the orientation as a virtual representation and data structure.
	std::cout << "Configuring your virtual representation" << std::endl;
	IList* pVirtRep = &OList();

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
	IList* pOrient = &OList();

	std::cout << "Connecting to Rift" << std::endl;
	IRift* pRift = &RVC();

	std::cout << "Creating interfacing" << std::endl;

	IThresh* pEventHandler = &EventInterfacing(pRift, (float) -1, (float) -1.5);

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
void PedometerDemo()
{
	std::cout << "Connecting to Oculus Rift" << std::endl;
	IRift *pRift = &RVC();

	// Set up the event handler for controlling the rift.
	std::cout << "Opening connection to OpenSim" << std::endl;
	IPedo *pEventHandler = &EventInterfacing1();
	
	std::cout << "Begin Sync to Virtual World" << std::endl;

	// Opens the CtrlAltStudio viewer.
	// system("start CtrlAltStudio-Viewer-Release.exe");

	// Set up the pedometer class that will store all the information about the pedometer
	Pedometer pedo = Pedometer(pRift);

	// Initiate variable for whether a step has been taken
	bool step = false;
	std::string sentinel;

	std::cout << "Press q to exit Virtual Conferencing" << std::endl;
	do
	{
		// Poll the event handler to see if a step has been taken.
		step = pEventHandler->pedometer(pRift, pedo);

		// If a step is registered, then send the movement commands to the viewer
		if(step)
		{
			pEventHandler->move();
		}
		sentinel = _getch();

	} while(sentinel != "q");
	std::cout << "Exiting pedometer demo" << std::endl;
};

void HeadtrackingWithoutList()
{
	std::cout << "Connecting to Oculus Rift" << std::endl;
	IRift *pRift = &RVC();

	// Set up the event handler for controlling the rift.
	std::cout << "Opening connection to OpenSim" << std::endl;
	IPedo *pEventHandler = &EventInterfacing1();
	
	std::cout << "Begin Sync to Virtual World" << std::endl;

	// Opens the CtrlAltStudio viewer.
	// system("start CtrlAltStudio-Viewer-Release.exe");

	// Set up the pedometer class that will store all the information about the pedometer
	Pedometer pedo = Pedometer(pRift);

	// Initiate variable for whether a step has been taken
	std::string sentinel;

	std::cout << "Press q to exit Virtual Conferencing" << std::endl;
	do
	{
		pEventHandler->turn(pRift, pedo);
		sentinel = _getch();

	} while(sentinel != "q");
	std::cout << "Exiting pedometer demo" << std::endl;
}

void PedometerWithoutListHeadtracking()
{
	std::cout << "Connecting to Oculus Rift" << std::endl;
	IRift *pRift = &RVC();

	// Set up the event handler for controlling the rift.
	std::cout << "Opening connection to OpenSim" << std::endl;
	IPedo *pEventHandler = &EventInterfacing1();
	
	std::cout << "Begin Sync to Virtual World" << std::endl;

	// Opens the CtrlAltStudio viewer.
	// system("start CtrlAltStudio-Viewer-Release.exe");

	// Set up the pedometer class that will store all the information about the pedometer
	Pedometer pedo = Pedometer(pRift);

	// Initiate variable for whether a step has been taken
	bool step = false;
	std::string sentinel;

	std::cout << "Press q to exit Virtual Conferencing" << std::endl;
	do
	{
		// Poll the event handler to see if a step has been taken.
		step = pEventHandler->pedometer(pRift, pedo);

		// If a step is registered, then send the movement commands to the viewer
		if(step)
		{
			pEventHandler->move();
		}
		sentinel = _getch();
		pEventHandler->turn(pRift, pedo);
	} while(sentinel != "q");
	std::cout << "Exiting pedometer demo" << std::endl;
}
