//
// 3D Game Programming
// 
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
//
// For runtime stuff.
// Simple entry point for updating game logic.
// The high level workflow should be placed here.
// Avoid implementing low level stuff here.
//

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>

#include "TutorialApplication.h"
#include "BasicTools.h"
#include "reader_data.h"
#include "SystemParameter.h"

//
// This function is called every frame.
//
void BasicTutorial_00::frameRendered(const Ogre::FrameEvent& evt)
{
    bool flg = true;

    double dt = evt.timeSinceLastFrame; // simulation time step size

    if (!mRealTimeSimulationFlg) { // Run in real time? That is, match to our wall-clock time?
        // No.
        // So this is not real time simulation.
        // So our program runs with a fixed time step size. 
        // If a faster computer is used, 
        // the resulting animation is faster under a fixed time duration.
        dt = SystemParameter::simulationTimeStep;
    }
    flg = updateGameState( dt );

    
    mTrayMgr->frameRendered(evt);
    mCameraManArr[0]->frameRendered(evt);
    //mTrayMgr->frameRenderingQueued(evt);
    /*
    mTrayMgr->showTrays();
    if ( true || !mTrayMgr->isDialogVisible())
    {
        mCameraMan->frameRendered(evt);   // if dialog isn't up, then update the camera
        if (mDetailsPanel->isVisible())   // if details panel is visible, then update its contents
        {
            mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(mCamera->getDerivedPosition().x));
            mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(mCamera->getDerivedPosition().y));
            mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(mCamera->getDerivedPosition().z));
            mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().w));
            mDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().x));
            mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().y));
            mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().z));
        }
    }
    */
  //  return flg;
}