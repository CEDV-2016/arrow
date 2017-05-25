#pragma once

#include <Ogre.h>
#include <OgreSingleton.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsStaticPlaneShape.h>
#include <Shapes/OgreBulletCollisionsBoxShape.h>

class MyPhysicsManager : public Ogre::Singleton<MyPhysicsManager>
{
public:

  MyPhysicsManager( Ogre::SceneManager * sceneMgr );
  ~MyPhysicsManager();

  void update( Ogre::Real deltaT );

  // Inherited from Ogre::Singleton
  static MyPhysicsManager& getSingleton ();
  static MyPhysicsManager* getSingletonPtr ();

  OgreBulletDynamics::DynamicsWorld * getPhysicWorld();


private:
  Ogre::SceneManager * _sceneMgr;

  OgreBulletDynamics::DynamicsWorld * _world;
  OgreBulletCollisions::DebugDrawer * _debugDrawer;

  void initMaps();
};
