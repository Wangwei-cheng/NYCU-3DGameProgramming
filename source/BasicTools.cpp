//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2024/09/20
// 

#include "BasicTools.h"

void genNameUsingIndex(const Ogre::String & prefix, int index, Ogre::String &out_name)
{
	out_name= prefix + Ogre::StringConverter::toString(static_cast<int>(index));
}

/**
 This function uses a scene manager to create a light and a scene node.
 Then it initializes the light and the scene node. 
 After that, attach the light to the scene node.
 */
LightConstruct::LightConstruct(Ogre::SceneManager* creator)
{
    light = creator->createLight();
    lightNode = creator
        ->getRootSceneNode()
        ->createChildSceneNode();
    lightNode->attachObject(light);
}

void LightConstruct::setPosition(float x, float y, float z)
{
    lightNode->setPosition(x, y, z);
}
void  LightConstruct::setPosition(const Ogre::Vector3& p)
{
    lightNode->setPosition(p);
}
void LightConstruct::setDirection(float x, float y, float z)
{
    lightNode->setDirection(x, y, z);
}
void  LightConstruct::setDirection(const Ogre::Vector3& p)
{
    lightNode->setDirection(p);
}
void LightConstruct::setDiffuseColour(float r, float g, float b)
{
    light->setDiffuseColour(r, g, b);
}
void LightConstruct::setSpecularColour(float r, float g, float b)
{
    light->setSpecularColour(r, g, b);
}

/**
 This function uses a scene manager to create a camera with a name and a scene node.
 The camera is attached to the scene node.
 */
CameraConstruct::CameraConstruct(
    const Ogre::String& cameraName
    , Ogre::SceneManager* creator)
{
    camera = creator->createCamera(cameraName);
    cameraNode = creator
        ->getRootSceneNode()
        ->createChildSceneNode();
    cameraNode->setFixedYawAxis(true); // important. Read the manual for details
    cameraNode->attachObject(camera);
}

void CameraConstruct::setPosition(float x, float y, float z)
{
    cameraNode->setPosition(x, y, z);
}

void CameraConstruct::setPosition(const Ogre::Vector3& p)
{
    cameraNode->setPosition(p);

}
