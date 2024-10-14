//
// 3D Game Programming
// 
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
//
//
// Purpose: Set the scenes. 
//
//
//
#include "TutorialApplication.h"
#include "BasicTools.h"
#include "reader_data.h"

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "TutorialApplication.h"
#include "BasicTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>

using namespace Ogre;

void BasicTutorial_00::createObjectGroup1_SphereGroup(void) {
    mItemGroupRadius = 250;
    mNumOfItems = READER_DATA::getNumberOfItems();
    mItemScale = READER_DATA::getItemScale();
    std::string meshName = READER_DATA::getMeshName_Item();

    for (int i = 0; i < mNumOfItems;++i) {
        double x, y, z;
        x = y = z = 0;
        double a = (i / (double)mNumOfItems) * PI * 2;
        mItemAngle[i] = a;
        x = mItemGroupRadius * cos(a);
        z = mItemGroupRadius * sin(a);

        String ename;
        genNameUsingIndex("item", i, ename);
        /*Entity *ent = mSceneMgr->createEntity(
            ename, "sphere.mesh");*/

        Entity* ent = mSceneMgr->createEntity(
            ename, meshName);

        //ent->setMaterialName("Examples/SceneCubeMap1");
        //ent->setMaterialName("Examples/MorningCubeMap");
        ent->setMaterialName("Examples/SphereMappedRustySteel");


        SceneNode* snode = mSceneMgr
            ->getRootSceneNode()
            ->createChildSceneNode();
        double scaleFactor = mItemScale;
        snode->setScale(scaleFactor, scaleFactor, scaleFactor);
        snode->setPosition(x, y, z);
        snode->attachObject(ent);

        const AxisAlignedBox bb = ent->getBoundingBox();
        Real itemSize = bb.getMaximum().x - bb.getMinimum().x;
        snode->translate(0, scaleFactor * itemSize / 2.0, 0);
        mItemArr[i] = snode;
        mItemStatus[i] = ITEM_STATE_INACTIVE;
        //
        //
        // Set velocity
        mVelocityArr[i] = -mItemArr[i]->getPosition();
        mVelocityArr[i].normalise();
        mVelocityArr[i].y = 2.0;
        mVelocityArr[i].normalise();
        mVelocityArr[i] = 3 * mVelocityArr[i];
    }

}

void BasicTutorial_00::createObjectGroup2_WavyCircle()
{
    int numCubes = 128;
    double L = 255;
    
    for (int i = 0; i < numCubes; ++i)
    {
        String name;
        genNameUsingIndex("c", i, name);
        Entity* ent = mSceneMgr->createEntity(
            name, "cube.mesh");
        ent->setMaterialName("Examples/SphereMappedRustySteel");

        SceneNode* snode = mSceneMgr
            ->getRootSceneNode()
            ->createChildSceneNode();
        snode->attachObject(ent);

        const AxisAlignedBox bb = ent->getBoundingBox();
        Real cubeSize = bb.getMaximum().x - bb.getMinimum().x;
        double x, y = 50, z;
        double fx;
        double h;
        double circle_radius = 100;

        fx = i / (double)(numCubes - 1);
        h = (1 + sin(fx * PI * 8)) * 50;
        Real unitF = 1.0 / cubeSize / numCubes * L * 0.8;

        x = 100 * sin(fx * PI * 2);
        z = 100 * cos(fx * PI * 2);
        
        snode->scale(unitF, h / cubeSize, unitF);
        snode->setPosition(x, 50, z);
    }
}

void BasicTutorial_00::createObjectGroup3_Wave()
{
    mNumOfWaveCubes = 128;
    double L = 255;
    int v = 1;

    for (int i = 0; i < mNumOfWaveCubes; ++i)
    {
        String name;
        genNameUsingIndex("d", i, name);
        Entity* ent = mSceneMgr->createEntity(
            name, "cube.mesh");
        ent->setMaterialName("Examples/Chrome");
        
        SceneNode* snode = mSceneMgr
            ->getRootSceneNode()
            ->createChildSceneNode();
        snode->attachObject(ent);

        const AxisAlignedBox bb = ent->getBoundingBox();
        Real cubeSize = bb.getMaximum().x - bb.getMinimum().x;
        double fx;
        double h;

        //
        // need to scale the object and set its position
        //
        double x, y = 20, z = 125;              // position (x,y,z)
        fx = 2 * i / (double)(mNumOfWaveCubes - 1);    // f in [0, 2]
        x = fx * L - L / 2.0;                   // compute x-coordinate
        h = (sin(fx * PI * 8) + 1) * 10 / cubeSize;       // HERE. Related to the height scale

        Real unitF = 1.0 / cubeSize / mNumOfWaveCubes * L * 0.8;   // x- and z-scales
        snode->scale(unitF, h, unitF);
        snode->setPosition(x, y, z);

        mWaveCubeArr[i] = snode;


    }

}

void BasicTutorial_00::createLights()
{
    mSceneMgr->setAmbientLight(ColourValue(0.25, 0.25, 0.25));
    mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);

    LightConstruct* lightC = new LightConstruct(mSceneMgr);
    // 
//    light = mSceneMgr->createLight("Light1"); 
    lightC->light->setType(Light::LT_SPOTLIGHT);
    lightC->setDirection(-1, -1, 0);
    lightC->setPosition(Vector3(300, 300, 0));
    lightC->setDiffuseColour(0.5, 0.5, 0.5);
    lightC->setSpecularColour(1.0, 1.0, 1.0);
    mLightContruct[0] = lightC;

    //lightC = createPointLight(mSceneMgr, "Light2");
    lightC = new LightConstruct(mSceneMgr);
    lightC->light->setType(Light::LT_POINT);
    lightC->setDirection(0, -1, -1);
    lightC->setPosition(Vector3(0, 150, 250));
    lightC->setDiffuseColour(0.5, 0.5, 0.5);
    lightC->setSpecularColour(1.0, 1.0, 1.0);
    mLightContruct[1] = lightC;

}

//
// Create a small pet
// Create a large pet
//
// auto-place the two pets on top of the floor.
//
void BasicTutorial_00::createPets()
{
    // double scale = READER_DATA::getMeshScale_Pet();
    double scale = READER_DATA::getMeshScale_Pet();
    String mesh_name = READER_DATA::getMeshName_Pet();
    Vector3 largeObjectScaleFactor(2, 3, 2);

    Entity* ent_large_penguin
        = mSceneMgr
        ->createEntity("LargePenguin", mesh_name);

    ent_large_penguin->setCastShadows(true);
    SceneNode* node_large_penguin
        = mSceneMgr
        ->getRootSceneNode()
        ->createChildSceneNode(
            "LargePenguinNode", Vector3(0, 0, 0));

    
    node_large_penguin->yaw(Degree(READER_DATA::getYawAngleDegreeOffset_Pet()));
    node_large_penguin->setScale(scale * largeObjectScaleFactor);
    node_large_penguin->attachObject(ent_large_penguin);

    Entity* ent_small_penguin
        = mSceneMgr
        ->createEntity("small_penguin", mesh_name);

    ent_small_penguin->setCastShadows(true);
    SceneNode* node_small_penguin
        = mSceneMgr
        ->getRootSceneNode()
        ->createChildSceneNode(
            "SmallPenguinNode", Vector3(150, 0, 0));

    node_small_penguin->yaw(Degree(- READER_DATA::getYawAngleDegreeOffset_Pet()));
    node_small_penguin->setScale(scale, -scale, scale);// I don't know why my small penguin is upside down, so I set scale.y as -scale.
    node_small_penguin->attachObject(ent_small_penguin);

    if (READER_DATA::getFlgAutoPlaceObj()) {
        Ogre::LogManager::getSingletonPtr()->logMessage("READER_DATA::getFlgAutoPlaceObj()***");

        AxisAlignedBox bb;
        Real obj_min_y;
        //
        // 
        // Auto-place the small pet on the floor
        // 
        bb = ent_small_penguin->getBoundingBox();
        obj_min_y = bb.getMinimum().y;
        node_small_penguin->translate(0, -scale * obj_min_y, 0);
        node_small_penguin->showBoundingBox(true);
        //
        //******************************************** 
        // Auto-place the large pet on the floor
        //********************************************  
        bb = ent_large_penguin->getBoundingBox();
        obj_min_y = bb.getMinimum().y;
        node_large_penguin->translate(0, -scale * largeObjectScaleFactor.y * obj_min_y, 0);
        node_large_penguin->showBoundingBox(true);
    }

    mTargetObj = node_large_penguin;
    mMovableObj = node_small_penguin;

}

// 
// Create a mesh and assign it a name. 
// After that, we use the mesh name to create entities.
//
void BasicTutorial_00::createPlaneObjectResource()
{
    Plane plane(Vector3::UNIT_Y, 0);
    MeshManager::getSingleton().createPlane(
        "plane_object_resource",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane,
        1500, 1500, 	// width, height
        20, 20, 		// x- and y-segments
        true, 		// normal
        1, 			// num texture sets
        5, 5, 		// x- and y-tiles
        Vector3::UNIT_Z	// upward vector
    );
}

void BasicTutorial_00::createFloor()
{
    Entity* ent = mSceneMgr->createEntity(
        "GroundEntity", "plane_object_resource");
    //ent->setMaterialName("Examples/BeachStones");
    //ent->setMaterialName("Examples/Rockwall");

    ent->setMaterialName(READER_DATA::getMaterialName_Floor());

    mSceneMgr
        ->getRootSceneNode()
        ->createChildSceneNode()
        ->attachObject(ent);
    ///////////////////////////////////////////////////////////////////////////
    //
    // create another layer of floor at the bottom
    //
    ent = mSceneMgr->createEntity(
        "BottomLayerFloor", "plane_object_resource");
    ent->setMaterialName("Examples/BeachStones");
    //ent->setMaterialName("Examples/Rockwall");

    //ent->setMaterialName(READER_DATA::getMaterialName_Floor());

    mSceneMgr
        ->getRootSceneNode()
        ->createChildSceneNode(Vector3(0, -20, 0))
        ->attachObject(ent);

}

void BasicTutorial_00::createWall()
{
    Entity* ent = mSceneMgr->createEntity(
        "Background", "plane_object_resource");
    //ent->setMaterialName("Examples/BeachStones");
    //ent->setMaterialName("Examples/Rockwall");
    ent->setMaterialName(READER_DATA::getMaterialName_Wall());

    //Radian angle((45/180.0)*3.141592654);
    Radian angle(3.141952654 / 2.0);

    Vector3 axis(1.0, 0.0, 0.0);
    mSceneMgr
        ->getRootSceneNode()
        ->createChildSceneNode(
            Vector3(0.0, 0.0, -750.0),
            Quaternion(angle, axis))
        ->attachObject(ent);
}

//
// Set mSceneMgr = mSceneMgrArr[0];
// Then we use mSceneMgr to create objects in the second scene.
// Because we use mSceneMgr, we keep our code consistent.
// But need to bear in mind that which scene manager that we are using.
// 
void BasicTutorial_00::createScene_00(void)
{
    mSceneMgr = mSceneMgrArr[0];
    ////////////////////////////////////////////////////
    // Now we can use mSceneMgr to create objects as usual.
    ////////////////////////////////////////////////////

    ////////////////////////////////////////////////////
    // Enjoy modular programming experience
    ////////////////////////////////////////////////////
    createLights();
    createPets();
    updateMovableObjPosition();
    createPlaneObjectResource();
    createFloor();
    createWall();
    //
    createObjectGroup1_SphereGroup();
    createObjectGroup2_WavyCircle();
    createObjectGroup3_Wave();
}


//
// Set mSceneMgr = mSceneMgrArr[1];
// Then we use mSceneMgr to create objects in the second scene.
// Because we use mSceneMgr, we keep our code consistent.
// But need to bear in mind that which scene manager that we are using.
// 
void BasicTutorial_00::createScene_01(void)
{
    ////////////////////////////////////////////////////
    mSceneMgr = mSceneMgrArr[1];
    ////////////////////////////////////////////////////
    // Now we can use mSceneMgr to create objects as usual.
    ////////////////////////////////////////////////////

    /*mSceneMgr->setAmbientLight(ColourValue(1.0, 1.0, 1.0));*/
    mSceneMgr->setAmbientLight(ColourValue(0.0, 0.0, 0.0));  
    //mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE); 


    LightConstruct* light = new LightConstruct(mSceneMgr);
    light->light->setType(Light::LT_POINT);
    light->setPosition(Vector3(25, 150, -50));
    light->setDiffuseColour(0.0, 0.8, 0.0);
    light->setSpecularColour(0.0, 1.0, 0.0);
    mLight_SecondScene = light;

    Entity* ent3
        = mSceneMgr
        ->createEntity("SphereGreen", "sphere.mesh");
    //ent2->setCastShadows(true);
    SceneNode* node3
        = mSceneMgr
        ->getRootSceneNode()
        ->createChildSceneNode(
            "SphereGreenNode", Vector3(25, 0, 0));
    ent3->setMaterialName("Examples/green");
    node3->attachObject(ent3);
    node3->translate(0, 30, 0);
    node3->scale(0.4, 0.2, 0.2);

    ////////////////////////////////////////////////////
    ent3
        = mSceneMgr
        ->createEntity("SphereYellow", "sphere.mesh");
    //ent2->setCastShadows(true);
    node3
        = mSceneMgr
        ->getRootSceneNode()
        ->createChildSceneNode(
            "SphereYellowNode", Vector3(0, 0, 0));
    ent3->setMaterialName("Examples/yellow");
    node3->attachObject(ent3);
    node3->translate(-25, 30, -25);
    node3->scale(0.1, 0.2, 0.2);
    ////////////////////////////////////////////////////
    Plane plane(Vector3::UNIT_Y, 0);
    MeshManager::getSingleton().createPlane(
        "ground",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane,
        1500, 1500, 	// width, height
        20, 20, 		// x- and y-segments
        true, 		// normal
        1, 		// num texture sets
        10, 10, 		// x- and y-tiles
        Vector3::UNIT_Z	// upward vector
    );

    Entity* ent = mSceneMgr->createEntity(
        "GroundEntity", "ground");
    ent->setMaterialName("Examples/myMaterial");
    mSceneMgr
        ->getRootSceneNode()
        ->createChildSceneNode()
        ->attachObject(ent);
}
