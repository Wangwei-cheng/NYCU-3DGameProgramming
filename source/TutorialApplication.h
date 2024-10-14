//
// Student Name:
// Student ID:
// Student Email Address:
//
//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2024/09/20
// 

#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include "BaseApplication.h"
#include "BasicTools.h"

using namespace Ogre;

#define STUDENT_INFO "3DGP 2024. STUDENT_NAME English Name: Wei-Cheng Wang  Student ID: 313551170"

#define PI 3.141592654

#define VIS_MASK_MINMAP 0x0001

#define MOTION_TYPE_NONE 0
#define MOTION_TYPE_IDLE 1
#define MOTION_TYPE_WALK 2

/**
* Viewport dimension structure
*/
struct ViewportDim {
	float left, top, width, height;
};


/**
 * BasicTutorial_00 is derived from BaseApplication.
 * Use BasicTutorial_00 to create a game.
 * It supports
 * scene managers
 * viewports
 * cameras
 * lights
 * keyboard events
 * mouse events, and so on.
 */
class BasicTutorial_00 : public BaseApplication
{

protected:

	/**
	* ITEM_STATE is used to set the state of an item.
	* Use the state of the item for updating the game logic of the item.
	*
	*/
	enum ITEM_STATE {
		ITEM_STATE_INACTIVE = 0,
		ITEM_STATE_ACTIVE = 1,
		ITEM_STATE_DONE = 2
	};
public:
	/**
	* No-arg constructor.
	*/
	BasicTutorial_00(void);

	/**
	* Constructor accepts a string for its application name.
	*/
	BasicTutorial_00(const Ogre::String& appName);
	//
protected:

	/**
	* Initialize data members.
	*/
	virtual void init();

	/**
	* Initialize viewport dimensions.
	*/
	virtual void initViewportDimensions();

	/**
	* Create viewports.
	*/
	virtual void createViewports(void);

	/**
	* Create scenes.
	*/
	virtual void createScene(void);

	/**
	* Create cameras.
	*/
	virtual void createCameras(void);

	/**
	* Create scene managers.
	*/
	virtual void chooseSceneManagers(void);
	
	/**
	* A runtime callback for updating game logic.
	*/
	virtual void frameRendered(const Ogre::FrameEvent& evt) override;


	/*!
	\brief Create a viewport

	Create a viewport for the entire screen.

	\return The sum of two integers.
	*/
	virtual void createViewport_00(void);

	/**
	* Create a viewport in a scene based on a scene manager.
	*/
	virtual void createViewport_01(void);
	//
	virtual void createCamera_00();
	virtual void createCamera_01();
	//
	virtual void createObjectGroup1_SphereGroup();
	virtual void createObjectGroup2_WavyCircle();
	virtual void createObjectGroup3_Wave();
	virtual void createScene_00();
	//
	virtual void createScene_01();

	//
	virtual void createPlaneObjectResource();
	virtual void createFloor();
	virtual void createWall();
	virtual void createLights();
	virtual void createPets();

	virtual void updatePets(double time_step);
	virtual void updateItems(double time_step);
	//

	virtual void updateWave(double time_step);

	// return true if the key event has been handled
	virtual bool handleKeyEvents_QuitProgram(const OgreBites::KeyboardEvent& arg);
	virtual bool handleKeyEvents_GetCameraInformation(const OgreBites::KeyboardEvent& arg);
	virtual bool handleKeyEvents_Camera(const OgreBites::KeyboardEvent& arg);
	virtual bool handleKeyEvents_Lights(const OgreBites::KeyboardEvent& arg);
	virtual bool handleKeyEvents_Viewport(const OgreBites::KeyboardEvent& arg);
	virtual bool handleKeyEvents_Animation(const OgreBites::KeyboardEvent& arg);

	//
	// return true if the key event has been handled
	//
	virtual bool handleKeyEvents(const OgreBites::KeyboardEvent& arg);
	virtual bool updateGameState(double dt);    // dt time step size
	//
	virtual void resetItems();
	virtual void activateItems();
	//
	virtual void updateMovableObjPosition(bool flg_large = false);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& arg) override;
	virtual bool keyReleased(const OgreBites::KeyboardEvent& arg) override;
	virtual bool mousePressed(const MouseButtonEvent& arg) override;
	virtual bool mouseReleased(const MouseButtonEvent& arg) override;
	virtual bool mouseMoved(const MouseMotionEvent& arg) override;
	virtual bool mouseWheelRolled(const MouseWheelEvent& arg) override;

protected:
	Ogre::Viewport* mViewportArr[8];
	CameraConstruct* mCurrentCameraConstruct;
	CameraConstruct* mCameraConstruct[8];
	// Ogre::SceneNode* mCameraNodeArr[8];
	Ogre::SceneManager* mSceneMgrArr[8];
	CameraMan* mCameraManArr[8];
	//
	LightConstruct* mLightContruct[8];
	LightConstruct* mLight_SecondScene;
	//
	bool mRealTimeSimulationFlg;
	//
	double mAngle;
	double mRadius;
	double mAngularSpeed;
	double mAngularAcceleration;
	double mMaxSpeed;
	Ogre::SceneNode* mMovableObj;
	Ogre::SceneNode* mTargetObj;
	bool mFlg_MoveObj;
	bool mFlg_CounterClockwise;
	Ogre::Vector3 mVelocity;
	//
	int mNumOfItems;
	Ogre::SceneNode* mItemArr[256];		// CAUTIOUS: maximum 256 items
	double mItemAngle[256];
	ITEM_STATE mItemStatus[256];
	Ogre::Vector3 mVelocityArr[256];
	double mItemScale;
	double mItemGroupRadius;
	//
	ViewportDim mViewportDim[4];
	int mTopViewportIndex;
	int mViewportArrangementIndex;

	int mNumOfWaveCubes;
	int mWaveBias;
	Ogre::SceneNode* mWaveCubeArr[256];
};

#endif // #ifndef __BasicTutorial_00_h_