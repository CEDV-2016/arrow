#pragma once

#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsStaticPlaneShape.h>
#include <Shapes/OgreBulletCollisionsBoxShape.h>

#include <iostream>

class MyCollisionManager : public Ogre::Singleton<MyCollisionManager>
{
public:

  MyCollisionManager(Ogre::SceneManager * sceneMgr);
  ~MyCollisionManager();

  void update( Ogre::Real deltaT );

  // Inherited from Ogre::Singleton.
  static MyCollisionManager& getSingleton ();
  static MyCollisionManager* getSingletonPtr ();

private:
  Ogre::SceneManager * _sceneMgr;
  OgreBulletDynamics::DynamicsWorld * _world;

  void detectCollision();
};
