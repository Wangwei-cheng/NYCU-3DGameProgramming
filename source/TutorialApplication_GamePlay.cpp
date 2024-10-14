//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2024/09/20
// 

//
// The main function: bool BasicTutorial_00::updateGameState(double dt)
// 
// Purpose: Update the game state, 
// including object states, game progress, physics simulation, 
// collision detection, collision response, and etc.
//
//
// The functions will be invoked at the runtime stage.
//
// Example: 
// Handle key events to control the camera.
// Handle key events to set viewports.
// Handle key events to obtain the camera information.
// Handle key events to activate the items, i.e., spheres.
// Update the spheres.
// Update the pets.
// And others
// 
// A key handler handles simple tasks, 
// such as setting the states of game objects. 
//
//

#include "TutorialApplication.h"
#include "BasicTools.h"
#include "reader_data.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>

//
// using namespace Ogre;
// Enable to use the functions/structures defined in the namespace Ogre.
//
using namespace Ogre;



//
// Set the position, status, and velocity of each item.
// 
// 
void BasicTutorial_00::resetItems() {
    for (int i = 0; i < mNumOfItems; ++i) {

        //
        // Organze the items as a circle.
        //
        double x, y, z;
        x = y = z = 0;
        double a = i / (double)mNumOfItems * PI * 2;
        x = mItemGroupRadius * cos(a);
        z = mItemGroupRadius * sin(a);
        mItemArr[i]->setPosition(x, y, z);
        //
        // WOW. There are many magic numbers!! 
        // Are they good or bad?
        //
        mVelocityArr[i] = -mItemArr[i]->getPosition();
        mVelocityArr[i].normalise();
        mVelocityArr[i].y = 2.0;
        mVelocityArr[i].normalise();
        mVelocityArr[i] = 3 * mVelocityArr[i];
        //

        mItemStatus[i] = ITEM_STATE_INACTIVE;
    }
}

//
// Find one item or more and activate it (them).
// To activate an item, set its state properly.
//
// The item is pointed to by the small pet 
// rotating about the center pet.
//
// The center pet is at the original, 
// Thus use the position vector of the small pet and the position vector
// of the item (i.e., the sphere). 
// If the angle deviation between these two vectors is smaller than 
// a threshold, pick the item and activate it.
// So, use dot product? do we need to compute the actual angle? 
// use acos?
//
// We will update the item based on the state of the item 
// in the main update function.
//
void BasicTutorial_00::activateItems() {
    double angle_deviation = READER_DATA::getAimAtSphereAngleDeviation();
    double target_deviation = angle_deviation / 180.0 * PI;
    //
    for (int i = 0; i < mNumOfItems; ++i) {
        if (mItemStatus[i] != ITEM_STATE_INACTIVE) continue;

        if (abs(mItemAngle[i] - mAngle) < target_deviation) {
            mItemStatus[i] = ITEM_STATE_ACTIVE;
        }
    }
}

//
// Update the states of objects.
// The states of objects include positions, 
// velocities, colours, materials, etc.
//
void BasicTutorial_00::updateMovableObjPosition(bool flg_large)
{
    Vector3 pos = mMovableObj->getPosition();
    pos.x = mRadius * cos(mAngle);
    pos.z = mRadius * sin(mAngle);
    mMovableObj->setPosition(pos);

    Vector3 q = mTargetObj->getPosition();
    //
    //q.y = pos.y; //object may be tilted
    //
    mMovableObj->lookAt(q, Node::TransformSpace::TS_WORLD);
    mMovableObj->yaw(Degree(360 - 90 - READER_DATA::getYawAngleDegreeOffset_Pet()));
    
    pos.y = mTargetObj->getPosition().y;

    if (flg_large) {
        mTargetObj->lookAt(pos, Node::TransformSpace::TS_WORLD);
        mTargetObj->yaw(Degree(READER_DATA::getYawAngleDegreeOffset_Pet() + 90));
    }

}

//
// Update the states of the spheres.
// In our case, the states include positions and velocities.
// Furthermore, if a sphere position is lower than the floor, 
// set the status of the sphere as ITEM_STATE_DONE. 
//
void BasicTutorial_00::updateItems(double time_step)
{
    double mag = 0.01;
    Vector3 force_gravity = mag * Vector3(0.0, 2.0, 0.0);
    double dt = time_step;

    for (int i = 0; i < mNumOfItems; ++i) {
        if (mItemStatus[i] == ITEM_STATE_INACTIVE
            ||
            mItemStatus[i] == ITEM_STATE_DONE
            ) continue;

        Vector3 p = mItemArr[i]->getPosition();
        mVelocityArr[i] = mVelocityArr[i] - force_gravity;
        p = p + mVelocityArr[i];
        mItemArr[i]->setPosition(p);

        if (p.y >= 200.0) { // above plane?
            p.y = 200.0;
            mItemArr[i]->setPosition(p);

            mVelocityArr[i].y = -mVelocityArr[i].y;
        }
        else if (p.y <= 0.0) { // below plane?
            p.y = 0.0;
            mItemArr[i]->setPosition(p);

            mVelocityArr[i].y = -mVelocityArr[i].y;
        }
    }
}

//
// Update the pets.
//
// Rotate the two pets and make them look at each other.
// Rotate the small pet in counter-clockwise direction 
// and then clockwise direction. Repeat the process.
//
// dt is the simulation time step size.
//
void BasicTutorial_00::updatePets(double dt)
{
    if (!mFlg_MoveObj) return;

    if (mFlg_CounterClockwise) {

        mAngularSpeed += mAngularAcceleration * dt;

        mAngle += mAngularSpeed * dt;

        if (mAngularSpeed > mMaxSpeed) {
            mAngularSpeed = mMaxSpeed;
        }

        if (mAngle > 2 * PI) {
            mAngle = 2 * PI;
            mFlg_CounterClockwise = false;
            mAngularSpeed = 0;
        }
        updateMovableObjPosition(true);


    }
    else { //!mFlg_CounterClockwise

        mAngularSpeed += mAngularAcceleration * dt;

        mAngle -= mAngularSpeed * dt;

        if (mAngularSpeed > mMaxSpeed) {
            mAngularSpeed = mMaxSpeed;
        }

        if (mAngle < 0) {
            mAngle = 0;
            mFlg_CounterClockwise = true;
            mAngularSpeed = 0;
        }

        updateMovableObjPosition(true);
    }
}

void BasicTutorial_00::updateWave(double time_step) {
    if (!READER_DATA::getFlgWaveAnima())    return;
    double wait_time = 0.01;
    double dt = time_step;
    static double time_accumulated = 0;
    time_accumulated += dt;
    if (time_accumulated < wait_time)   return;

    time_accumulated = 0;

    for (int i = 0; i < mNumOfWaveCubes; ++i) {
        Vector3 s = mWaveCubeArr[(i + mWaveBias) % mNumOfWaveCubes]->getScale();
        
        const AxisAlignedBox bb = mWaveCubeArr[(i + mWaveBias) % mNumOfWaveCubes]->getAttachedObject(0)->getBoundingBox();
        Real cubeSize = bb.getMaximum().x - bb.getMinimum().x;
        double fx = 2 * i / (double)(mNumOfWaveCubes - 1);
        s.y = (sin(fx * PI * 8) + 1) * 10 / cubeSize;
        mWaveCubeArr[(i + mWaveBias) % mNumOfWaveCubes]->setScale(s);
    }

    mWaveBias = (mWaveBias + 1) % mNumOfWaveCubes;
}

//
// Purpose: Update the game state based on the game logic.
//
// return true if everything is normal. 
// return false to quit the program.
// 
// dt is the simulation time step size
//
bool BasicTutorial_00::updateGameState(double dt)
{
    bool flg = true;

    updatePets(dt);
    updateItems(dt);
    updateWave(dt);

    return flg;
}