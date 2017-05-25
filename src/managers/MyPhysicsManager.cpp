#include "MyPhysicsManager.hpp"

template<> MyPhysicsManager* Ogre::Singleton<MyPhysicsManager>::msSingleton = 0;

MyPhysicsManager::MyPhysicsManager( Ogre::SceneManager * sceneMgr )
{
  _sceneMgr = sceneMgr;

  Ogre::AxisAlignedBox worldBounds = Ogre::AxisAlignedBox( Ogre::Vector3 (-100, -100, -100), Ogre::Vector3 (100,  100,  100) );
  Ogre::Vector3 gravity = Ogre::Vector3( 0, -9.8, 0 );
  _world = new OgreBulletDynamics::DynamicsWorld( _sceneMgr, worldBounds, gravity );

  _debugDrawer = new OgreBulletCollisions::DebugDrawer();
  _debugDrawer->setDrawWireframe( true );
  Ogre::SceneNode *node = _sceneMgr->getRootSceneNode()->createChildSceneNode("debugNode", Ogre::Vector3::ZERO);
  node->attachObject(static_cast <Ogre::SimpleRenderable *>( _debugDrawer ));

  _world->setDebugDrawer(_debugDrawer);

  #ifdef _DEBUG
  _world->setShowDebugShapes(true); // paint green wires around physic bodies
  #endif
}

MyPhysicsManager::~MyPhysicsManager()
{
  delete _debugDrawer;
  delete _world;
}

OgreBulletDynamics::DynamicsWorld * MyPhysicsManager::getPhysicWorld()
{
  return _world;
}

void MyPhysicsManager::update( Ogre::Real deltaT )
{
  _world->stepSimulation( deltaT );
}

MyPhysicsManager& MyPhysicsManager::getSingleton()
{
  assert(msSingleton);
  return (*msSingleton);
}

MyPhysicsManager* MyPhysicsManager::getSingletonPtr()
{
  assert(msSingleton);
  return msSingleton;
}
