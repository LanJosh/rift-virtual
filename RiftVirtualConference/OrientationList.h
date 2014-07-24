#ifndef ORIENTATIONLIST_H
#define ORIENTATIONLIST_H
#include <vector>
#include "OListInterface.h"
#include "RVC.h"

/*
Represents body position based on the position of the Oculus Rift.
Head position is given by virtual keystrokes, which translate to
position within this list.

if physical head is facing foward, left.length == right.length.

*/
class OList : public IList
{
public:
	INPUT ip;
	// The current virtual representation position
	int currPos;
	// The "left" side of the virtual representation (180 - 0)
	std::vector<int> left;
	// The "right" side of the virtual representation (0 - -180)
	std::vector<int> right;

	// Note that advance and retreat may seem to be illogical as they oppose the standard number line
	// This is due to Oculus angles--'left' yaw is POSITIVE and 'right' yaw is NEGATIVE

	/* 
	 Advance one position in the list. 
     Move virtual head LEFT but INCREASES position in list. 
	*/
	void advance();

	/* 
	   Retreat one position in the list
	   Move virtual head RIGHT but DECREASES position in list.
	*/
	void retreat();

	// Return the current position
	int position();
};

#endif