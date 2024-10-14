//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2024/09/20
// 

//
// Handle all keyboard and mouse events. 
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


using namespace std;
using namespace Ogre;
//using namespace OIS;

void showStudentInfo() {
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    cout << "<<< 3D Game Programming <<<<<<<<<" << endl;
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    cout << "Date: 2024/09/20" << endl;
    cout << endl;
    cout << "STUDENT_INFO:" << STUDENT_INFO << endl;
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

    system("pause");
}

//
// Handle key events for controlling the active camera.
//
// Set the camera position and its lookat position.
//
bool BasicTutorial_00::handleKeyEvents_Camera(const OgreBites::KeyboardEvent& arg)
{
    bool flg_handled = false;
    Keycode key = arg.keysym.sym;

 
    if (key == 'r' || key == 'R') {
        flg_handled = true;

        mCameraMan->getCamera()->setPosition(Ogre::Vector3(120, 300, 600));
        mCameraMan->getCamera()->lookAt(Ogre::Vector3(0, 0, 0), Node::TransformSpace::TS_PARENT);

        bool flg = mTargetObj->getShowBoundingBox();
        mTargetObj->showBoundingBox(!flg); // toggle the bounding box of the large pet.
        flg = mMovableObj->getShowBoundingBox();
        mMovableObj->showBoundingBox(!flg);// toggle the bounding box of the small pet.
    }

    if ( key == '1') {
        flg_handled = true;

        mCameraMan->getCamera()
            ->setPosition(Vector3(9 - 85.21, 30.27, 597.32));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.11, -0.00, -0.99));
    }


    if (key == '2') {
        flg_handled = true;
        mCameraMan->getCamera()
            ->setPosition(500, -500, 500);
        mCameraMan->getCamera()
            ->setDirection(-1, 1, -1);
    }

    if (key == '3') {
        flg_handled = true;
        mCameraMan->getCamera()
            ->setPosition(Vector3(-1463.00, 606.45, -513.24));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.88, -0.47, 0.10));
    }

    if (key == '4') {
        flg_handled = true;

        mCameraMan->getCamera()
            ->setPosition(Vector3(-1356.16, 634.32, -964.51));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.71, -0.44, 0.55));
    }

    if (key == '5') {
        flg_handled = true;

        mCameraMan->getCamera()
            ->setPosition(50, 150, 300);
        mCameraMan->getCamera()
            ->setDirection(-0.1, -0.3, -0.6);
    }

    if (key == '6') {
        flg_handled = true;

        mCameraMan->getCamera()
            ->setPosition(0, 1000, 0);
        mCameraMan->getCamera()
            ->setDirection(0, -1, 0);
    }

    
    return flg_handled;
}

//
// Set the viewport attributes, 
// e.g., background colours, dimensions and locations.
//
bool BasicTutorial_00::handleKeyEvents_Viewport(const OgreBites::KeyboardEvent& arg)
{
    bool flg_handled = false;

    Keycode key = arg.keysym.sym;
    if (key == 'M' || key == 'm') {
        flg_handled = true;

        mRenderWindow->removeViewport(mViewportArr[0]->getZOrder());
        mRenderWindow->removeViewport(mViewportArr[1]->getZOrder());

        mTopViewportIndex = 0;
        mViewportArrangementIndex = 1;
        
        // first scene
        Camera* c_ptr = mCameraConstruct[0]->camera;
        Ogre::Viewport* vp = mRenderWindow->addViewport(
            c_ptr,
            1,
            0.75,
            0.0,
            0.25,
            0.25
        );
        vp->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 1.0));
        c_ptr->setAspectRatio(
            Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

        mViewportArr[0] = vp;
        
        // second scene
        c_ptr = mCameraConstruct[1]->camera;
        vp = mRenderWindow->addViewport(
            c_ptr,
            0, 0, 0, 1.0, 1.0 
        );
        vp->setBackgroundColour(Ogre::ColourValue(0.25, 0.25, 0.25));
        c_ptr->setAspectRatio(
            Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
        mViewportArr[1] = vp;
        vp->setOverlaysEnabled(false);
    }

    if (key == 'N' || key == 'n') {
        flg_handled = true;

        mRenderWindow->removeViewport(mViewportArr[0]->getZOrder());
        mRenderWindow->removeViewport(mViewportArr[1]->getZOrder());

        mTopViewportIndex = 1;
        mViewportArrangementIndex = 1;

        // first scene
        Camera* c_ptr = mCameraConstruct[0]->camera;
        Ogre::Viewport* vp = mRenderWindow->addViewport(
            c_ptr,
            0,
            0,
            0,
            1,
            1
        );
        vp->setBackgroundColour(Ogre::ColourValue(0, 0, 1));
        c_ptr->setAspectRatio(
            Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
        mViewportArr[0] = vp;

        // second second
        c_ptr = mCameraConstruct[1]->camera;
        vp = mRenderWindow->addViewport(
            c_ptr,
            1,
            0.75,
            0.0,
            0.25,
            0.25
        );
        vp->setBackgroundColour(Ogre::ColourValue(0.25, 0.25, 0.25));
        c_ptr->setAspectRatio(
            Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
        mViewportArr[1] = vp;
        vp->setOverlaysEnabled(false);
    }

    if (key == 'B' || key == 'b') {
        flg_handled = true;

        float left, top, width, height;
        width = mViewportDim[mViewportArrangementIndex].width;
        height = mViewportDim[mViewportArrangementIndex].height;

        if (mViewportArrangementIndex == 0 || mViewportArrangementIndex == 1) {
            left = 0.75;
        }
        else {
            left = 0.0;
        }
        if (mViewportArrangementIndex == 1 || mViewportArrangementIndex == 2) {
            top = 0.75;
        }
        else {
            top = 0.0;
        }

        mViewportArr[mTopViewportIndex]
            ->setDimensions(left, top, width, height);

        mViewportArrangementIndex = (mViewportArrangementIndex + 1) % 4;
    }

    return flg_handled;
}

//
// Set the object states for animation or simulation.
// Try not to perform complex tasks in a key handler.
//
bool BasicTutorial_00::handleKeyEvents_Animation(const OgreBites::KeyboardEvent& arg)
{
    bool flg_handled = false;
    Keycode key = arg.keysym.sym;
    if (key == 'P' || key == 'p') {
        flg_handled = true;

        mFlg_MoveObj = !mFlg_MoveObj;
    }

    if (key == 'j' || key == 'J')
    {
        flg_handled = true;

        mRealTimeSimulationFlg = !mRealTimeSimulationFlg;
    }

    if (key == SDLK_SPACE)
    {
        flg_handled = true;

        activateItems();
    }
    if (key == 'K' || key == 'k')
    {
        flg_handled = true;

        resetItems();
    }

    if (key == 'h' || key == 'H') {
        flg_handled = true;

        READER_DATA::setFlgWaveAnima();
    }

    return flg_handled;
}

//
// Get the camera position and direction.
// Save them to the log file.
//
bool BasicTutorial_00::handleKeyEvents_GetCameraInformation(const OgreBites::KeyboardEvent& arg)
{
    bool flg_handled = false;

    stringstream ss;
    Keycode key = arg.keysym.sym;
    if (key == 'C' || key == 'c') {

        flg_handled = true;

        //How to clear ss?
        ss.str("");
        ss.clear();

        //stringstream ss; // Second way

        // Third way?
        //=============

        // How to get camera position?
        //-----------------------------
        // This is incorrect.
        // Vector3 pos = mCamera->getPosition();
        // The controller may have its own 
        // set of attributes to control the camera.
        //
        //We use the controller to get the camera information.
        //-----------------------------
        //
        //
        // The following is correct.
        //
        Vector3 pos = mCameraMan->getCamera()->getPosition();
        ss << std::fixed << std::setprecision(2)
            << "CameraPosition:"
            << pos.x << "\t"
            << pos.y << "\t"
            << pos.z << "\n";
        Ogre::LogManager::getSingletonPtr()
            ->logMessage(ss.str());
        //
        ss.str("");
        ss.clear();
        //Vector3 dir = mCameraMan->getCamera()->getDirection();
        Vector3 dir = mCameraMan->getCamera()->getAutoTrackLocalDirection();

        ss << std::fixed << std::setprecision(2)
            << "CameraDirection:"
            << dir.x << "\t"
            << dir.y << "\t"
            << dir.z << "\n";

        Ogre::LogManager::getSingletonPtr()
            ->logMessage(ss.str());
    }

    return flg_handled;
}

bool BasicTutorial_00::handleKeyEvents_QuitProgram(const OgreBites::KeyboardEvent& arg)
{
    if (arg.keysym.sym == OgreBites::SDLK_ESCAPE) {
        showStudentInfo();
        Ogre::Root::getSingleton().queueEndRendering();
        return true;
    }
    return false;
}

bool BasicTutorial_00::handleKeyEvents_Lights(const OgreBites::KeyboardEvent& arg)
{
    Keycode key = arg.keysym.sym;

    if ( key == '7') {
        mLightContruct[0]->light->setDiffuseColour(0.5, 0.0, 0.0);
        mLightContruct[0]->light->setSpecularColour(1.0, 0.0, 0.0);
    }

    if ( key == '8') {
        mLightContruct[0]->light->setDiffuseColour(0.0, 0.5, 0.0);
        mLightContruct[0]->light->setSpecularColour(0.0, 1.0, 0.0);
    }

    if ( key == '9') {
        mLightContruct[0]->light->setDiffuseColour(0.0, 0.0, 0.5);
        mLightContruct[0]->light->setSpecularColour(0.0, 0.0, 1.0);
    }

    if ( key == '0') {
        mLightContruct[0]->light->setDiffuseColour(0.5, 0.5, 0.5);
        mLightContruct[0]->light->setSpecularColour(1.0, 1.0, 1.0);
    }

    //COMMA
    if (key == ',') {
        ColourValue v = mLightContruct[0]->light->getDiffuseColour();
        v -= ColourValue(0.1, 0.1, 0.0);
        v.r = v.r < 0.0 ? 0.0 : v.r;
        v.g = v.g < 0.0 ? 0.0 : v.g;
        mLightContruct[0]->light->setDiffuseColour(v);
        mLightContruct[0]->light->setSpecularColour(1.0, 1.0, 1.0);
    }

    //PERIOD
    if (key == '.') {
        ColourValue v = mLightContruct[0]->light->getDiffuseColour();
        v += ColourValue(0.1, 0.1, 0.0);
        v.r = v.r > 1.0 ? 1.0 : v.r;
        v.g = v.g > 1.0 ? 1.0 : v.g;
        mLightContruct[0]->light->setDiffuseColour(v);
        mLightContruct[0]->light->setSpecularColour(1.0, 1.0, 1.0);
    }

    if (key == 'U' || key == 'u') {
        mLight_SecondScene->light->setDiffuseColour(0.8, 0.0, 0.0);
        mLight_SecondScene->light->setSpecularColour(1.0, 0.0, 0.0);
    }

    if (key == 'I' || key == 'i') {
        mLight_SecondScene->light->setDiffuseColour(0.0, 0.8, 0.0);
        mLight_SecondScene->light->setSpecularColour(0.0, 1.0, 0.0);
    }

    if (key == 'O' || key == 'o') {
        mLight_SecondScene->light->setDiffuseColour(0.0, 0.0, 0.8);
        mLight_SecondScene->light->setSpecularColour(0.0, 0.0, 1.0);
    }
    return true;
}

//
// return true if the key event has been handled
//
bool BasicTutorial_00::handleKeyEvents(const OgreBites::KeyboardEvent& arg)
{
    bool flg_handled = false;

    //
    // Use the OR operator to turn on the flag
    //
    // Make sure that the same key is not used in
    // two or more functions.
    //

    if (handleKeyEvents_QuitProgram(arg)) {
        return false;
    }

    flg_handled |= handleKeyEvents_GetCameraInformation(arg);
    flg_handled |= handleKeyEvents_Camera(arg);
    flg_handled |= handleKeyEvents_Viewport(arg);
    flg_handled |= handleKeyEvents_Lights(arg);
    flg_handled |= handleKeyEvents_Animation(arg);

    return flg_handled;
}

bool BasicTutorial_00::keyPressed(const OgreBites::KeyboardEvent& arg)
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::keyPressed()");

    bool flg = true;

    Keycode keycode = arg.keysym.sym;

    mCameraMan->keyPressed(arg);

    return handleKeyEvents(arg);
}

//
// What is stored in the file for arg.key?
// ASCII code? If no, what is it?
// 
// To find out the answer:
// Go to see the definition of KeyEvent
//

bool BasicTutorial_00::keyReleased(const OgreBites::KeyboardEvent& arg)
{

    bool flg = true;
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::keyReleased(const OgreBites::KeyboardEvent& evt)", arg.keysym.sym, false);

    mCameraMan->keyReleased(arg);

    return flg;
}

bool BasicTutorial_00::mouseWheelRolled(const MouseWheelEvent& arg)
{
    bool flg = true;

    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::mouseWheelRolled(const OgreBites::KeyboardEvent& arg)", arg.y, false);

    mCameraManArr[0]->mouseWheelRolled(arg);

    mTrayMgr->mouseWheelRolled(arg);

    return flg;
}

bool BasicTutorial_00::mousePressed(const MouseButtonEvent& arg)
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::mousePressed(const MouseButtonEvent& arg)", arg.button, false);

    mCameraManArr[0]->mousePressed(arg);
    if (mTrayMgr->mousePressed(arg)) return true;
    

    return true;
}

bool BasicTutorial_00::mouseReleased(const MouseButtonEvent& evt)
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::mouseReleased(const MouseButtonEvent& evt)", evt.button, false);

    mCameraManArr[0]->mouseReleased(evt);
    if (mTrayMgr->mouseReleased(evt)) return true;
    

    return true;
}

bool BasicTutorial_00::mouseMoved(const MouseMotionEvent& evt)
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::mouseMoved(const MouseButtonEvent& evt):x:", evt.x, false);
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::mouseMoved(const MouseButtonEvent& evt):y:", evt.y, false);

    if (mTrayMgr->mouseMoved(evt)) return true;

    return true;
}


