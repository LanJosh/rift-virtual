#ifndef SAMPLES_H
#define SAMPLES_H

/*
 These samples should show you around the code with varying levels of depth. I would suggest you use these samples to see how things
 are done within this codebase and the structure we came up with for dealing with multiple technologies. 
*/

/*
 Getting orientation data from the Oculus Rift. 
*/
void Orientation();

/*
 Getting acceleration data from the Oculus Rift. 
*/
void Acceleration();

/*
 Using peak analysis to determine movement. (1 DOF)
*/
void PeakAnalysisDemo();

/*
 Using peak analysis along with head tracking orientation to determine movement. (2 DOF)
*/
void PeakAnalysisWithHeadtrackingDemo();

/*
 Headtracking using the Orientation List object
*/
void HeadtrackingWithList();

/*
 Movement controlled by a pedometer algorithm instead of an inertial system.
*/
void PedometerDemo();

#endif