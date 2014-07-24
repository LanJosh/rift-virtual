#ifndef OLISTINTERFACE_H
#define OLISTINTERFACE_H

/*
Representation of body position based upon the orientation of the
Oculus Rift. 
*/
class IList
{
public:

	/*
	 Advance virtual head representation in list.
	*/
	virtual void advance() = 0;

	/*
	 Retreat virtual head representation in list.
	*/
	virtual void retreat() = 0;

	/*
	 Return the current virtual orientation
	*/
	virtual int position() = 0;

	/*
	 Virtual destructor.
	*/
	virtual ~IList(){};
};

#endif