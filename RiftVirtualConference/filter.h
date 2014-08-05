#ifndef FILTER_H
#define FILTER_H
#include "RVC.h"

/*
* A complementary filter for the readings from the accelerometer and gyroscope.
* 
* @param fusion
*	Fusion objected attached to sensor devices
* @return filteredValue
*	
*/
std::pair<EulerAngles, OVR::Vector3f> ComFilter(std::pair<EulerAngles, OVR::Vector3f> readings);

/*
* A Kalman filter for the corrected accelerometer readings
*/
OVR::Vector3f KalmanFilter(OVR::Vector3f acc);

#endif