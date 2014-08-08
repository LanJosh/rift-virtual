#include "OrientationList.h"

int OList::position()
{
	return this->currPos;
};

void OList::advance()
{
	// move our position in the OList
	this->currPos -= 1;
	// move virtual representation in OpenSim (hit 'a' key)
	this->ip.ki.wVk = 0x41;
	this->ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));
	this->ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

	// TODO change list sizes to reflect new orientation
};

void OList::retreat()
{
	// move our position in the OList
	this->currPos += 1;
	// move virtual representation in OpenSim (hit 'd' key)
	this->ip.ki.wVk = 0x44;
	this->ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));
	this->ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

	// TODO change list sizes to reflect new orientation
};

OList::OList()
{
	this->currPos = 0;
	this->ip.type = INPUT_KEYBOARD;
	this->ip.ki.wScan = 0;
	this->ip.ki.time = 0;
	this->ip.ki.dwExtraInfo = 0;
	// Initilize the 'right' side
	for (int i = 0; i <= 12; i++)
	{
		this->right.push_back(i);
	}
	// Initialize the 'left' side
	for (int j = -12; j < 0; j++)
	{
		this->right.push_back(j);
	}
	// See resource file OList for a representation.
};
