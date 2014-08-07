#ifndef PEDOMETER_H
#define PEDOMETER_H
#include "RVCInterface.h"

class Pedometer
{
private:

	float Min; // Minimum acceleration value over time
	float Max; // Maximum acceleration value over time
	float MaxPrev; // Max before last update
	float DTL; // Dynamic Threshold Level is a moving average of the Max and Min
	float CTD; // Calibrated Threshold Difference is the difference between the Max and the DTL
	float OldAcc; // n-1 acceleration data
	float NewAcc; // n acceleration data
	int LoopCounter; // Keeps track of when to update Thresh
	int TimerCounter; // Keeps track of how long it's been between each "step"
	float OldYaw; // n-1 yaw

public:
	/*
	 Constructor
	*/
	Pedometer::Pedometer(IRift *pRift);

	/*
	 Destructor
	*/
	Pedometer::~Pedometer();

	/* Updates the minimum acceleration value
	*
	* @requires
	*	The new minmimun acceleration to store
	*/
	void updateMin(float min);

	/* 
	* @returns
	*	The minmimun acceleration value
	*/
	float getMin();

	/* Updates the maximum acceleration value
	*
	* @requires
	*	The new maxmimun acceleration to store
	*/
	void updateMax(float max);

	/* 
	* @returns
	*	The maxmimun acceleration value
	*/
	float getMax();

	/* 
	* Updates the previous max to the current max
	*/
	void maxToMaxPrev();

	/* 
	* @returns
	*	The last maxmimun acceleration value before the last store
	*/
	float getMaxPrev();
	
	/* 
	* Updates the Dynamic Threshold value using the current Max and Min
	*/
	void updateDTL();
	
	/*
	* @returns
	*	The current Dynamic Threhold Level
	*/
	float getDTL();

	/* 
	* Updates the Dynamic Threshold Difference value
	*/
	void updateCTD();
	
	/*
	* @returns
	*	The current Dynamic Threshold Difference value
	*/
	float getCTD();

	/* 
	* Moves the NewAcc value to the OldAcc value
	*/
	void newToOldAcc();
	
	/* Updates the NewAcc value
	*
	* @requires
	*	The new acceleration to store
	*/
	void setNewAcc(float acc);
	
	/* 
	* @returns
	*	The OldAcc value
	*/
	float getOldAcc();

	/* 
	* @returns
	*	The NewAcc value
	*/
	float getNewAcc();

	/* 
	* Moves the NewYaw value to the OldYaw value
	*/
	void newToOldYaw(float yaw);
	
	/* 
	* @returns
	*	The OldYaw value
	*/
	float getOldYaw();

	/* 
	* Indexes the Counter by 1
	*/
	void indexLoopCounter();

	/* 
	* Resets the Counter to zero
	*/
	void resetLoopCounter();

	/* 
	* @returns
	*	The current Counter value
	*/
	int getLoopCounter();

	/* 
	* Indexes the TimerCounter by 1
	*/
	void indexTimerCounter();

	/* 
	* @returns
	*	The current TimerCounter value
	*/
	int getTimerCounter();

	/*
	* Resets the TimerCounter to zero
	*/
	void resetTimerCounter();

	/*
	* Zeros all paramters in the Pedometer class
	*/
	void zeroPedometer();
};

#endif