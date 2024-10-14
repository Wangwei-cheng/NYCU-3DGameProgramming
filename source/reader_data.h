//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2024/09/20
// 
//header guard
#ifndef __READER_DATA_H__
#define __READER_DATA_H__

#include <string>

/**
 * READER_DATA reads data from a data file to set the data members accordingly.
 * Invoke the get functions to retrieve the values of the data members.
 *
 *
 */
class READER_DATA {
protected:

	static double mSimulationStepSize;

	static std::string mMeshName_Pet;
	static double mYawAngleDegreeOffset_Pet;
	static double mMeshScale_Pet;
	static bool mEnabledAutoPlaceObject;
	//
	static std::string mMeshName_Item;
	static int mNumberOfItems;
	static double mItemScale;
	//
	static std::string mMaterialName_Floor;
	static std::string mMaterialName_Wall;
	//
	static bool mEnabledShadow;

	static double mAimAtSphereAngleDeviation;
	//
	static bool mFlg_WaveAnima;
	//
public:
	READER_DATA();
	static void readData();
	//
	static double getSimulationStepSize();

	//
	static std::string getMeshName_Pet();
	static double getYawAngleDegreeOffset_Pet();
	static double getMeshScale_Pet();
	static bool getFlgAutoPlaceObj();
	//
	static std::string getMeshName_Item();
	static int getNumberOfItems();
	static double getItemScale();
	//
	static std::string getMaterialName_Floor();
	static std::string getMaterialName_Wall();

	//
	static double getAimAtSphereAngleDeviation();
	static bool isEnabledShadow();
	//
	static bool getFlgWaveAnima();
	static void setFlgWaveAnima();
	//
	static void report();
};

#endif