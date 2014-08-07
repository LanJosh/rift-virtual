#include "Pedometer.h"


Pedometer::Pedometer(IRift *pRift)
{
	this->zeroPedometer();
	this->OldAcc = pRift->RawAcceleration().z;
	this->NewAcc = pRift->RawAcceleration().z;
	this->OldYaw = pRift->RawEulerAngles().yaw;
}

Pedometer::~Pedometer()
{
}

/* Updates the minimum acceleration value
*
* @requires
*	The new minmimun acceleration to store
*/
void Pedometer::updateMin(float min)
{
	Min = min;
}

/* 
* @returns
*	The minmimun acceleration value
*/
float Pedometer::getMin()
{
	return Min;
}

/* Updates the maximum acceleration value
*
* @requires
*	The new maxmimun acceleration to store
*/
void Pedometer::updateMax(float max)
{
	Max = max;
}

/* 
* @returns
*	The maxmimun acceleration value
*/
float Pedometer::getMax()
{
	return Max;
}

/* 
* Updates the previous max to the current max
*/
void Pedometer::maxToMaxPrev()
{
	MaxPrev = Max;
}

/* 
* @returns
*	The last maxmimun acceleration value before the last store
*/
float Pedometer::getMaxPrev()
{
	return MaxPrev;
}
	
/* 
* Updates the threshold value using the current Max and Min
*/
void Pedometer::updateDTL()
{
	DTL = (Max + Min)/2;
}
	
/*
* @returns
*	The current Thresh value
*/
float Pedometer::getDTL()
{
	return DTL;
}

/* 
* Updates the Dynamic Threshold Difference value
*/
void Pedometer::updateCTD()
{
	CTD = Max - DTL;
}
	
/*
* @returns
*	The current Dynamic Threshold Difference value
*/
float Pedometer::getCTD()
{
	return CTD;
}

/* 
* Moves the NewAcc value to the OldAcc value
*/
void Pedometer::newToOldAcc()
{
	OldAcc = NewAcc;
}

/* Updates the NewAcc value
*
* @requires
*	The new acceleration to store
*/
void Pedometer::setNewAcc(float acc)
{
	NewAcc = acc;
}

/* 
* @returns
*	The OldAcc value
*/
float Pedometer::getOldAcc()
{
	return OldAcc;
}

/* 
* @returns
*	The NewAcc value
*/
float Pedometer::getNewAcc()
{
	return NewAcc;
}

/* 
* Updates the OldYaw value
*
* @requires 
*	a yaw value
*/
void Pedometer::newToOldYaw(float yaw)
{
	OldYaw = yaw;
}

/* 
* @returns
*	The OldYaw value
*/
float Pedometer::getOldYaw()
{
	return OldYaw;
}

/* 
* Indexes the Counter by 1
*/
void Pedometer::indexLoopCounter()
{
		LoopCounter++;
}

/* 
* Resets the Counter to zero
*/
void Pedometer::resetLoopCounter()
{
	LoopCounter = 0;
}

/* 
* @returns
*	The current Counter value
*/
int Pedometer::getLoopCounter()
{
	return LoopCounter;
}

/* 
* Indexes the TimerCounter by 1
*/
void Pedometer::indexTimerCounter()
{
	TimerCounter++;
}

/* 
* @returns
*	The current TimerCounter value
*/
int Pedometer::getTimerCounter()
{
	return TimerCounter;
}

/*
* Resets the TimerCounter to zero
*/ 
void Pedometer::resetTimerCounter()
{
	TimerCounter = 0;
}

/*
* Zeros all paramters in the Pedometer class
*/
void Pedometer::zeroPedometer()
{
	Max = 0;
	Min = 0;
	DTL = 0;
	CTD = 0;
	OldAcc = 0;
	NewAcc = 0;
	LoopCounter = 0;
	TimerCounter = 0;
}