#ifndef IEVENT_H
#define IEVENT_H

/*
* Interface for event handler to move in character in OpenSim. 
*/
class IEvent
{
public:
	// This (move) is likely the function that will change the most if future interns are able to establish a direct connection to OpenSim
	// or build a viewer. Much of the other algorithms should require NO change and future interns should be careful
	// to discard the work already done. 

	/*
	 Moves the avatar in virtual world. 
	
	 @requires
		There is a connection to OpenSim.
	*/
	virtual void move() = 0;

	/*
	 Virtual destructor
	*/
	virtual ~IEvent(){};
};

#endif