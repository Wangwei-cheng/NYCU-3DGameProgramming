//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2024/09/20
// 

#include <fstream>
#include <iostream>
#include <string>
#include "reader_data.h"
#include "reader_config.h"

#define DATA_FILE_NAME	"00_game_data_01.txt"

using namespace std;

/**
* Initialize all the static data members.
* 
*/

double READER_DATA::mSimulationStepSize = 0.03;

std::string READER_DATA::mMeshName_Pet = "penguin.mesh";
double READER_DATA::mYawAngleDegreeOffset_Pet = 0;
double READER_DATA::mMeshScale_Pet = 1.0;
//
std::string READER_DATA::mMeshName_Item = "sphere.mesh";
int READER_DATA::mNumberOfItems = 24;
double READER_DATA::mItemScale = 1.0;
//
bool READER_DATA::mEnabledAutoPlaceObject = true;
std::string READER_DATA::mMaterialName_Floor = "Examples/WaterStream";
std::string READER_DATA::mMaterialName_Wall = "Examples/WaterStream";
bool READER_DATA::mEnabledShadow = true;
double READER_DATA::mAimAtSphereAngleDeviation = 10.0;
//
bool READER_DATA::mFlg_WaveAnima = false;
//
READER_DATA::READER_DATA()
{

}

/**
 * This function performs the following steps.
 * Set the game data file name, fileName
 * Invoke READER_CONFIG::readData() to read a data file name from the config file.
 * If the config file stores a game file name, use it to set to fileName.
 * Now, use fileName to open the file.
 * Read data from the file.
 * While reading the file, set the data members based on the tags and associated values.
 * Close the game data file after the file has been read.
 * Report the values of the data members. This is important to check whether the data are correct or not.
 */
void READER_DATA::readData()
{
	cout << "Begin READER_DATA::readData()" << endl;
	using namespace std;
	std::ifstream* fp;
	std::string fileName = DATA_FILE_NAME;

	if (READER_CONFIG::readData()) {
		fileName = READER_CONFIG::getDataFileName();
	}
	fp = new std::ifstream(fileName, ios::in | ios::binary);
	if (fp == 0 || fp->fail()) {
		cout << "Cannot open data file:" << fileName << endl;
		return;
	}

	std::string key;
	double value;
	int ivalue;
	std::string vstring;
	while (!fp->eof()) {
		*fp >> key;

		cout << "Reading:" << key << endl;

		if (key.compare("SIMUATION_STEP_SIZE") == 0) {
			*fp >> mSimulationStepSize;
		}

		if (key.compare("MESH_NAME_PET") == 0) {
			*fp >> mMeshName_Pet;
		}

		if (key.compare("MESH_SCALE_PET") == 0) {
			*fp >> mMeshScale_Pet;
		}
		


		if (key.compare("YAW_ANGLE_DEGREE_OFFSET_PET") == 0) {
			*fp >> value;
			mYawAngleDegreeOffset_Pet = value;
		}

		if (key.compare("MESH_NAME_ITEM") == 0) {
			*fp >> mMeshName_Item;
		}

		if (key.compare("NUM_ITEMS") == 0) {
			*fp >> ivalue;
			mNumberOfItems = ivalue;
		}

		if (key.compare("MESH_SCALE_ITEM") == 0) {
			*fp >> value;
			mItemScale = value;
		}




		if (key.compare("AUTO_PLACE_OBJECT") == 0) {
			*fp >> vstring;

			mEnabledAutoPlaceObject = true;
			if (vstring.compare("false") == 0) {
				mEnabledAutoPlaceObject = false;
			}
		}


		if (key.compare("MATERIAL_NAME_FLOOR") == 0) {
			*fp >> mMaterialName_Floor;
		}

		if (key.compare("MATERIAL_NAME_WALL") == 0) {
			*fp >> mMaterialName_Wall;
		}

		if (key.compare("FLAG_ENABLED_SHADOW") == 0) {
			*fp >> vstring;

			mEnabledShadow = true;
			if (vstring.compare("false") == 0) {
				mEnabledShadow = false;
			}
		}

		if (key.compare("AIM_AT_SPHERE_ANGLE_DEVIATION") == 0) {
			*fp >> mAimAtSphereAngleDeviation;
		}

		if (key.compare("MYTAG_313551170") == 0) {
			*fp >> vstring;

			mFlg_WaveAnima = true;
			if (vstring.compare("false") == 0) {
				mFlg_WaveAnima = false;
			}
		}
		//////////////////////////////////////////////
		key.clear(); // clear the key content
		//////////////////////////////////////////////
	}
	report();
	cout << "End READER_DATA::readData()" << endl;
}

double READER_DATA::getSimulationStepSize()
{
	return mSimulationStepSize;
}
std::string READER_DATA::getMeshName_Pet() {
	return mMeshName_Pet;
}

double READER_DATA::getYawAngleDegreeOffset_Pet() {
	return mYawAngleDegreeOffset_Pet;
}

double READER_DATA::getMeshScale_Pet() {
	return mMeshScale_Pet;
}

std::string READER_DATA::getMeshName_Item() {
	return mMeshName_Item;
}
int READER_DATA::getNumberOfItems() {
	return mNumberOfItems;

}
double READER_DATA::getItemScale() {
	return mItemScale;
}

bool READER_DATA::getFlgAutoPlaceObj() {
	return mEnabledAutoPlaceObject;
}
//
std::string READER_DATA::getMaterialName_Floor() {
	return mMaterialName_Floor;
}

std::string READER_DATA::getMaterialName_Wall() {
	return mMaterialName_Wall;
}

double READER_DATA::getAimAtSphereAngleDeviation()
{
	return mAimAtSphereAngleDeviation;
}

bool READER_DATA::getFlgWaveAnima() {
	return mFlg_WaveAnima;
}

void READER_DATA::setFlgWaveAnima() {
	mFlg_WaveAnima = !mFlg_WaveAnima;
}

bool READER_DATA::isEnabledShadow() {
	return mEnabledShadow;
}
void READER_DATA::report()
{
	cout << "=======================================" << endl;
	cout << "READER_DATA::report" << endl;
	cout << "mSimulationStepSize:\t" <<			mSimulationStepSize << endl;
	cout << "mMeshName_Pet:\t" <<				mMeshName_Pet << endl;
	cout << "mYawAngleDegreeOffset_Pet:\t" <<	mYawAngleDegreeOffset_Pet << endl;
	cout << "mMeshScale_Pet:\t" <<				mMeshScale_Pet << endl;
	cout << "mMeshName_Item:\t" <<				mMeshName_Item << endl;
	cout << "mNumberOfSpheres:\t" <<			mNumberOfItems << endl;
	cout << "mSphereScale:\t" <<				mItemScale << endl;
	cout << "mEnabledAutoPlaceObject:\t" <<		mEnabledAutoPlaceObject << endl;
	cout << "mMaterialName_Floor:\t" <<			mMaterialName_Floor << endl;
	cout << "mMaterialName_Wall:\t" <<			mMaterialName_Wall << endl;
	cout << "mEnabledShadow:\t" <<				mEnabledShadow << endl;
	cout << "mAimAtSphereAngleDeviation:\t" <<	mAimAtSphereAngleDeviation << endl;
	cout << "=======================================" << endl;
	//system("pause");
}