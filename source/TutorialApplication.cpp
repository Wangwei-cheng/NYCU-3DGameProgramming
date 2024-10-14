//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2024/09/20
// 

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "TutorialApplication.h"
#include "BasicTools.h"
#include "reader_data.h"

#include "SystemParameter.h"

using namespace std;
using namespace Ogre;

BasicTutorial_00::BasicTutorial_00(void) : BasicTutorial_00("Hello World!")
{
  
}

BasicTutorial_00::BasicTutorial_00(const Ogre::String& appName)
    : BaseApplication(appName)
{
    init();
}

void BasicTutorial_00::init() {
    //
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::init(void)");
    //
    mRealTimeSimulationFlg = false; // run as fast as possible
    mRealTimeSimulationFlg = true;  // match to wall-clock time. "real life" time
    //
    mAngularAcceleration = SystemParameter::acceleration;
    mMaxSpeed = SystemParameter::maxSpeed;
    mRadius = SystemParameter::radius;
    mAngularSpeed = 0.0;
    mFlg_CounterClockwise = false;
    mAngle = 0.0;
    mFlg_MoveObj = false;
    //
    mFlg_MoveObj = false;
    mFlg_CounterClockwise = true;
    //
    mItemScale = 1.0;
    //
    mWaveBias = 0;
    //
    initViewportDimensions();

}

void BasicTutorial_00::initViewportDimensions()
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::initViewportDimensions(void)");

    mTopViewportIndex = 1;
    mViewportArrangementIndex = 1;

    mViewportDim[0].left = 0.75;
    mViewportDim[0].top = 0;
    mViewportDim[0].width = 0.25;
    mViewportDim[0].height = 0.25;
    //
    mViewportDim[1].left = 0.75;
    mViewportDim[1].top = 0.75;
    mViewportDim[1].width = 0.25;
    mViewportDim[1].height = 0.25;
    //
    mViewportDim[2].left = 0;
    mViewportDim[2].top = 0.75;
    mViewportDim[2].width = 0.25;
    mViewportDim[2].height = 0.25;
    //
    mViewportDim[3].left = 0.0;
    mViewportDim[3].top = 0.0;
    mViewportDim[3].width = 0.25;
    mViewportDim[3].height = 0.25;
}

//
// chooseSceneManagers( ) is invoked in the setup process.
// We will create two scene managers.
// 
// Call createSceneManager( ) to create a scene manager.
// e.g.,
// scene manager = createSceneManager( );
//
// Store the scene managers to the pointer array, mSceneMgrArr[ ]
//
// For example,
// mSceneMgrArr[0] = createSceneManager();
// mSceneMgrArr[1] = createSceneManager();
//
// You can use mSceneMgr to point to a current scene manager.
// So you set it up here too.
// For example, set mSceneMgr to point to the first scene manager as 
// mSceneMgr = mSceneMgrArr[0];
//
void BasicTutorial_00::chooseSceneManagers()
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::chooseSceneManagers()");

    //
    mSceneMgrArr[0] = createSceneManager();
    mSceneMgrArr[1] = createSceneManager();
    //
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::mSceneMgrArr[0]:", mSceneMgrArr[0]);
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::mSceneMgrArr[1]:", mSceneMgrArr[1]);

    mSceneMgr = mSceneMgrArr[0]; // active scene manager

    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::mSceneMgr:", mSceneMgr);
}

//
// Create a camera for mSceneMgrArr[0]
//
// Set the camera position, lookat position.
// Set the clip distances, i.e., near and far distances
//
// To create a controller for the camera,
// call 
// mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);
//
//
// Later on, we can use mCameraManArr[0] 
// to receive mouse and keyboard events. 
//
void BasicTutorial_00::createCamera_00(void)
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::createCamera_00(void)");

    mSceneMgr = mSceneMgrArr[0];
    mCameraConstruct[0] = new CameraConstruct("PlayerCamera", mSceneMgr);
    //mCamera = mCameraArr[0] = mSceneMgr->createCamera("PlayerCamera");
    mCameraConstruct[0]->cameraNode->setPosition(Ogre::Vector3(120, 300, 600));
    mCameraConstruct[0]->cameraNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TransformSpace::TS_PARENT);
    //
    // near clipping distance
    //
    mCameraConstruct[0]->camera->setNearClipDistance(5);
    //
    // create a default camera controller
    //

    mCameraManArr[0] = new CameraMan(mCameraConstruct[0]->cameraNode);

    mCurrentCameraConstruct = mCameraConstruct[0];
    //mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);

    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::createCamera_00(void):mCameraConstruct[0]", mCameraConstruct[0]);

}

//
// Create a camera for mSceneMgrArr[1]
//
// Set the camera position, lookat position.
// Set the clip distances, i.e., near and far distances
//
// To create a controller for the camera,
// call 
// mCameraManArr[1] = new OgreBites::SdkCameraMan(mCamera);
//
//
// Later on, we can use mCameraManArr[1] 
// to receive mouse and keyboard events. 
//
void BasicTutorial_00::createCamera_01(void)
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::createCamera_01(void)");


    mSceneMgr = mSceneMgrArr[1];

    mCameraConstruct[1] = new CameraConstruct("PlayerCamera", mSceneMgr);
    
    mCameraConstruct[1]->setPosition(Ogre::Vector3(0, 350, 0));
    mCameraConstruct[1]->cameraNode->lookAt(
        Ogre::Vector3(0.00001, 0, 0)
        , Node::TransformSpace::TS_PARENT
    );

    mCameraConstruct[1]->camera->setNearClipDistance(5);
    //
    mCameraManArr[1] = new CameraMan(mCameraConstruct[1]->cameraNode);

    mCurrentCameraConstruct = mCameraConstruct[1];

    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::createCamera_00(void):mCameraConstruct[1]", mCameraConstruct[1]);

}


//
// Create a viewport for the camera, mCameraArr[0].
//
// 1.Call mWindow->addViewport(mCamera) to create the viewport.
// 2.Set the background colour.
// 3.Set the aspect ratio.
// 
//
void BasicTutorial_00::createViewport_00(void)
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::createViewport_00(void)");

    mCurrentCameraConstruct = mCameraConstruct[0];
    mCamera = mCurrentCameraConstruct->camera;

    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::mCurrentCameraConstruct:", mCurrentCameraConstruct);

    // By default the Z-order of this viewport is ZERO
    Ogre::Viewport* vp = mRenderWindow->addViewport(
        mCamera
    );

    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::vp:", vp);


    //vp->setBackgroundColour(Ogre::ColourValue(0.0, 1.0, 0.0));  // green
    //vp->setBackgroundColour(Ogre::ColourValue(1.0, 0.0, 0.0)); // red
    vp->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 1.0));  // blue

    double viewport_width = Ogre::Real(vp->getActualWidth());
    double viewport_height = Ogre::Real(vp->getActualHeight());

    mCamera->setAspectRatio(viewport_width/viewport_height);

    //
    // Store the viewport point vp. 
    // So we can use the pointer later.
    //
    mViewportArr[0] = vp;
}

//
// Create a viewport for the camera, mCameraArr[1].
//
// 1.Call mWindow->addViewport(mCamera) to create the viewport.
// 2.Set the background colour.
// 3.Set the aspect ratio.
// 
//

void BasicTutorial_00::createViewport_01(void)
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::createViewport_01(void)");


    mCurrentCameraConstruct = mCameraConstruct[1];
    mCamera = mCurrentCameraConstruct->camera;

    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::mCurrentCameraConstruct:", mCurrentCameraConstruct);


    Ogre::Viewport* vp = mRenderWindow->addViewport(
        mCamera,
        1,      // z-order
        0.75,   // left
        0.0,   // top
        0.25,   // width
        0.25    // height
    );

    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::vp:", vp);


    vp->setBackgroundColour(Ogre::ColourValue(0, 0, 1));

    double viewport_width = Ogre::Real(vp->getActualWidth());
    double viewport_height = Ogre::Real(vp->getActualHeight());

    mCamera->setAspectRatio(viewport_width / viewport_height);
    //
    // Make the overlay invisible in this viewport.
    //
    vp->setOverlaysEnabled(false);
    //
    mViewportArr[1] = vp;
}

//
// createViewports is invoked in the setup process.
//
void BasicTutorial_00::createViewports(void)
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::createViewports(void)");


    createViewport_00();
    createViewport_01();
}

//
// createCamera is invoked in the setup process.
//
void BasicTutorial_00::createCameras(void) {
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::createCamera(void)");

    BaseApplication::createCameras( ); // create the camera for the base class
    //
    createCamera_00(); // for the main scene
    createCamera_01(); // for the secondary scene

    //
    // A controller recieves mouse and keyboard events.
    // In this system, only one controller can be active.
    // and the other controllers are inactive.
    //
    // Set one controller as active.
    // In this case, we set mCameraManArr[0] to be active.
    // mCameraMan is used in the base class, BaseApplication.
    // The mouse and keyboard events are passed to mCameraMan.
    // Thus, we set mCameraMan = mCameraManArr[0] for the main scene.
    //

    // Set mCameraManArr[0] as active.
    mCamera = mCameraConstruct[0]->camera;
    mCameraMan = mCameraManArr[0];

    // Set mCameraManArr[1] as active.
    //mCameraMan = mCameraManArr[1];    
}


//
// We invokde the data reader to read parameter values
// which are stored in a text file.
// After that, we use the data reader READER_DATA 
// to access the parameter values.
// 
// At the end of this function, set the active camera.
//
void BasicTutorial_00::createScene(void) {

    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::createScene(void)");


    Ogre::LogManager::getSingletonPtr()->logMessage("DATA_Reader::Read");
    READER_DATA::readData();
    
    SystemParameter::simulationTimeStep = READER_DATA::getSimulationStepSize();

    //
    createScene_00();
    createScene_01();
    mSceneMgr = mSceneMgrArr[0];  // active SceneManager
    //mSceneMgr = mSceneMgrArr[1];    // active SceneManager
    //
    //
    mCurrentCameraConstruct = mCameraConstruct[0];  // active camera
    mCamera = mCurrentCameraConstruct->camera;

    mCameraMan = mCameraManArr[0];

    //mCamera = mCameraArr[1];      // active camera
}
