#include "RVC.h"
#include "EulerAngles.h"
#include "filter.h"

using namespace OVR;
	/*
	 Initializes the connection to the Oculus Rift. More about this and clear is shown in the Minimal Oculus 
	 tutorial for SDK 0.2.5c. This is deprecated as of DK2 (SDK 0.3.x), but at the time of implementation we
	 did not have DK2s and therefore choose not to use SDK 0.3.x. If new Oculus Rifts are bought by the 
	 lab or the consumer version is release it is EXTREMELY important to update this program. Though direct changes
	 are clearly needed within these functions, it is likely this entire program will be
	 deprecated by the time of release (as the API will change on release). All conventions and algorithms will likely hold,
	 updates should just be rolling in new functions/updating deprecated ones. 
	*/
	void RVC::init()
	{
		System::Init();
		pFusionResult = new SensorFusion();
		pManager = *DeviceManager::Create();
		pHMD = *pManager->EnumerateDevices<HMDDevice>().CreateDevice();

		if (pHMD)
		{
			InfoLoaded = pHMD->GetDeviceInfo(&Info);

			pSensor = *pHMD->GetSensor();
		}
		else
		{
		   pSensor = *pManager->EnumerateDevices<SensorDevice>().CreateDevice();
		}

		if (pSensor)
		{
		   pFusionResult->AttachToSensor(pSensor);
		}
	};

	/*
		Clears all connections to the Oculus Rift and deleted the object attached to the sensors.
	*/
	void RVC::clear()
	{
		pSensor.Clear();
		pHMD.Clear();
		pManager.Clear();

		delete pFusionResult;

		System::Destroy();
	};

	/*
	 Constructor. Initializes Rift connection.
	*/
	RVC::RVC()
	{
		this->init();
	};

	RVC::~RVC()
	{
		this->clear();
	};

	/*
	 Returns a struct of yaw, pitch, and roll. 
		
	 For future interns: This is probably not going to be used for anything past testing purposes,
	 though it should be used extensively during testing for getting Euler angles and printing them
	 with a reasonable amount of code. 
	*/
	EulerAngles RVC::RawEulerAngles()
	{
		EulerAngles ang;
		float yaw, pitch, roll;
		Quatf quat = pFusionResult->GetOrientation();
		quat.GetEulerAngles<Axis_Y, Axis_X, Axis_Z>(&yaw, &pitch, &roll);
		ang.yaw = yaw;
		ang.pitch = pitch;
		ang.roll = roll;

		return ang;
	};

	/*
	 Returns raw acceleration data from the Oculus Rift. 
	
	 For future interns: This method is implemented soley to keep class
	 convention. This should almost never be called outside of testing.
	 Keep in mind that this is NOT corrected for gravity. Be sure to understand
	 the Equivalence Principle before attempting to use this or you will likely
	 receive bad results
	*/
	Vector3f RVC::RawAcceleration()
	{
		return pFusionResult->GetAcceleration();
	};

	/*
	 Returns raw orientation data from the Oculus Rift.
	
	 For future interns: This is implemented for conventions sake
	 and should almost never be used outside of testing. Before using this
	 consider using CorrectedAcceleration() or RawEulerAngles().
	*/
	Quatf RVC::RawOrientation()
	{
		return pFusionResult->GetOrientation();
	};

	/*
	 Returns complementary filtered linear acceleration.
	*/
	Vector3f RVC::CorrectedAcceleration()
	{
		float gravity = 9.81f;
		EulerAngles angles = this->RawEulerAngles();
		Vector3f acc = this->RawAcceleration();
		std::pair<EulerAngles, Vector3f> preFusion (angles, acc);
		std::pair<EulerAngles, Vector3f> postFusion = ComFilter(preFusion);

		postFusion.second.z = postFusion.second.z + (gravity * (sin(postFusion.first.pitch)));

		return postFusion.second;
	};
