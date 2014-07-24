#include "Samples.h"
#include "RVC.h"
#include "EventInterfacing.h"
#include "OrientationList.h"
#include <conio.h>

void Orientation()
{
	// Connect to rift
	IRift *pRift = new RVC();
	while (true)
	{
		// Get the Euler angles. It is possible to get orientation
		// in different structures--check the documentation 
		EulerAngles ang = pRift->RawEulerAngles();
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
			break;
		}
	};
};

void Acceleration()
{
	std::cout << "Connecting to Oculus Rift" << std::endl;
	IRift *pRift = new RVC();
	std::cout << "Begin printing acceleration data" << std::endl;
	while (true)
	{
		// Again we use something from rift outside of the rift class.
		// This should NOT be done as the rift is still in development
		// and this may change. We use it here simply to show the data hiding.
		// (though that seems contradictory, we do it simply to maintain transparency
		// and because we might not be here to maintain backend and you will need to know how)

		OVR::Vector3f acc = pRift->RawAcceleration();
		OVR::Vector3f cAcc = pRift->CorrectedAcceleration();
		std::cout << "rX: " << acc.x 
			<< "rY: " << acc.y
			<< "rZ: " << acc.z << std::endl;
		std::cout << "cX: " << cAcc.x
			<< "cY: " << cAcc.y
			<< "cZ: " << cAcc.z << std::endl;
		if (_kbhit())
		{
			break;
		}
	};
};

void PeakAnalysisDemo()
{
	/*
	* Code for a test demo using Rift Virtual Conference.
	* 
	* For future interns: This demonstrates the usage of our classes and how to set up a basic virtual conference.
	* There will be an excess of comments here as it is possible the new intern team has no experience programming.
	* These comments will server as a light introduction to using our codebase and try to get some basics of programming
	* down.
	*/

	/*
	* IRift is the abstract base class. This is used to simulate an interface (if you are a java person). Our convention is to
	* have contracts within the interface. The reason for this is to allow for different components to be programmed to this interface
	* that may do things on the backend that change things--but this doesn't matter to who ever is using the object. It is only important
	* to fufill the contract, however it is done does not matter (Hopefully you will soon learn that this works because there is not
	* one way to solve a problem, and having multiple ways in multiple objects allows for more options). 
	 
	* *pRift is a pointer to this abstract base class. The reason this has to be a pointer is because you cannot instantiate an abstract
	* base class! This makes sense as the abstract base class is exactly that, a class that serves as a base for other classes that is 
	* abstract (you can't use abstract!). We put a 'p' before the moniker 'Rift' as a form of Apps Hungarian notation. This notation is 
	* used because it gives some important information about the object. Do not go as far as labeling all everthing by type, but knowing 
	* if something is a pointer or not is pretty important. 
	 
	* The 'new' operator returns a new instance of the RVC class. This is extremely simplified but full explanation of 'new' goes a little
	* beyond scope. Look this up to learn more (which is something that goes hand and hand in programming and especially DLab).

	* EventInterfacing(pRift, (float) -1, (float)1.5)) creates the RVC class instance. This class implements the IRift abstract base class,
	* so the object will actually do something! 

	* That is in general how we set things up in our codebase. You can find information about contracts in the .h files with the word 'Interface'
	* in them. Implementation of the interfaces (abstract base classes) have a name that is just like the interfaces, but without the word 'Interface'
	* Implementations share the same name in both the .h and .cpp files. Implementations will contain comments that give a information about how things
	* are done and handled within the implementation. These are details that can be ignored by people who just want to use the code, but should be
	* noted if you plan on writing another implementation or changing/updating them. There are a lot of helpful comments in the code, but many of the
	* intricacies of working on this project are left to the user to find out. Not everything can be accounted for and not everything should be 
	* accounted for, you will need to learn by doing if you want to make some meaningful changes to the program.
	*/
	std::cout << "Connecting to Oculus Rift" << std::endl;
	IRift *pRift = new RVC();

	// Set up the event handler for controlling the rift.
	// Constants -1 and -1.5 are threshold values for acceleration and decceleration--here they are hard coding for simplicity.
	std::cout << "Opening connection to OpenSim" << std::endl;
	IEvent *pEventHandler = new EventInterfacing(pRift, (float) -1, (float)-1.5);
	
	// Set up an infite loop to continually poll the event handler.
	std::cout << "Begin Sync to Virtual World" << std::endl;
	std::cout << "Press enter to exit Virtual Conferencing" << std::endl;
	while (true)
	{
		// Tell the event handler to coordinate rift with virtual world. 
		pEventHandler->move();

		// Allow the user to  exit!
		if (_kbhit())
		{
			std::cout << "Ending connection to virtual world" << std::endl;
			pRift->clear();
			delete pRift;
			delete pEventHandler;
			break;
		};
	};
};

void PeakAnalysisWithHeadtrackingDemo()
{
	std::cout << "Connecting to Oculus Rift" << std::endl;
	IRift *pRift = new RVC();

	// Set up the event handler for controlling the rift.
	// Constants -1 and -1.5 are threshold values for acceleration and decceleration--here they are hard coding for simplicity.
	std::cout << "Opening connection to OpenSim" << std::endl;
	IEvent *pEventHandler = new EventInterfacing(pRift, (float) -1, (float)-1.5);

	// Set up the orientation as a virtual representation and data structure.
	std::cout << "Configuring your virtual representation" << std::endl;
	IList *pVirtRep = new OList();

	// Set up an infite loop to continually poll the event handler.
	std::cout << "Begin Sync to Virtual World" << std::endl;
	std::cout << "Press enter to exit Virtual Conferencing" << std::endl;
	while (true)
	{
		// Tell the event handler to coordinate rift with virtual world. 
		pEventHandler->move();

		// Orient body with virtual world
		pEventHandler->orientBody(pVirtRep);
		// Allow the user to  exit!
		if (_kbhit())
		{
			std::cout << "Ending connection to virtual world" << std::endl;
			pRift->clear();
			delete pRift;
			delete pEventHandler;
			delete pVirtRep;
			break;
		};
	};
};