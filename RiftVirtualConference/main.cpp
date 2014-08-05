#include <cmath>
#include "RVC.h"
#include "EventInterfacing.h"
#include "Samples.h"
#include <Windows.h>
#include <WinUser.h>

#define STD_WALK_SPEED 1.3582 //Average human walking speed

int main()
{
	IRift *pRift = new RVC();
	IEvent *pEvent = new EventInterfacing(pRift, (float) -1, (float) -1.5);
};