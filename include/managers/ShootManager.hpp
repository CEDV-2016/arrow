#pragma once

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI.h>

#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsStaticPlaneShape.h>
#include <Shapes/OgreBulletCollisionsBoxShape.h>

using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace OgreBulletDynamics;

class ShootManager : public Ogre::Singleton<ShootManager>
{
public:
  ShootManager( Ogre::SceneManager * sceneMgr);
  ~ShootManager();

  void initWorld();
  void shootBall();

  // Inherited from Ogre::Singleton.
  static ShootManager& getSingleton ();
  static ShootManager* getSingletonPtr ();

protected:
  Ogre::SceneManager* _sceneMgr;
  Ogre::Camera* _camera;
  OgreBulletDynamics::DynamicsWorld * _world;
  OgreBulletCollisions::DebugDrawer * _debugDrawer;
  int _numEntities;
  float _timeLastObject;

  std::deque <OgreBulletDynamics::RigidBody *>         _bodies;
  std::deque <OgreBulletCollisions::CollisionShape *>  _shapes;
};
