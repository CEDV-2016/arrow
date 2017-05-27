#include "MyCollisionManager.hpp"
#include "MyPhysicsManager.hpp"

#include "Shapes/OgreBulletCollisionsTrimeshShape.h"
#include "Shapes/OgreBulletCollisionsSphereShape.h"
#include "Utils/OgreBulletCollisionsMeshToShapeConverter.h"

template<> MyCollisionManager* Ogre::Singleton<MyCollisionManager>::msSingleton = 0;

MyCollisionManager::MyCollisionManager(Ogre::SceneManager * sceneMgr)
{
  _sceneMgr = sceneMgr;
  _world = MyPhysicsManager::getSingletonPtr()->getPhysicWorld();
}

MyCollisionManager::~MyCollisionManager()
{
}

void MyCollisionManager::update( Ogre::Real deltaT ){
  detectCollision();
}

void MyCollisionManager::detectCollision()
{
  btCollisionWorld *bulletWorld = _world->getBulletCollisionWorld();
  int numManifolds = bulletWorld->getDispatcher()->getNumManifolds();

  for (int i=0;i<numManifolds;i++) {
    btPersistentManifold* contactManifold =
      bulletWorld->getDispatcher()->getManifoldByIndexInternal(i);
    btCollisionObject* obA =
      (btCollisionObject*)(contactManifold->getBody0());
    btCollisionObject* obB =
      (btCollisionObject*)(contactManifold->getBody1());

    std::stringstream dartboard_id;
    for(int j=0; j<5; j++){
      dartboard_id.str("");
      dartboard_id << "Dartboard" << j;
      Ogre::SceneNode* drain = _sceneMgr->getSceneNode(dartboard_id.str());

      OgreBulletCollisions::Object *obDrain = _world->findObject(drain);
      OgreBulletCollisions::Object *obOB_A = _world->findObject(obA);
      OgreBulletCollisions::Object *obOB_B = _world->findObject(obB);

      if ((obOB_A == obDrain) || (obOB_B == obDrain)) {
        Ogre::SceneNode* node = NULL;
        if ((obOB_A != obDrain) && (obOB_A)) {
  	       node = obOB_A->getRootNode();
           delete obOB_A;
        }
        else if ((obOB_B != obDrain) && (obOB_B)) {
  	       node = obOB_B->getRootNode();
           delete obOB_B;
        }
        if (node) {
  	       std::cout << node->getName() << std::endl;
  	       _sceneMgr->getRootSceneNode()->removeAndDestroyChild (node->getName());
        }
      }
    }
  }
}

MyCollisionManager& MyCollisionManager::getSingleton() {
  assert(msSingleton);
  return (*msSingleton);
}

MyCollisionManager* MyCollisionManager::getSingletonPtr() {
  assert(msSingleton);
  return msSingleton;
}
