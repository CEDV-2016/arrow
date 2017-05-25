#include "ShootManager.hpp"

#include "Shapes/OgreBulletCollisionsConvexHullShape.h"
#include "Shapes/OgreBulletCollisionsTrimeshShape.h"
#include "Utils/OgreBulletCollisionsMeshToShapeConverter.h"
#include "OgreBulletCollisionsRay.h"
#include "MapManager.hpp"

template<> ShootManager* Ogre::Singleton<ShootManager>::msSingleton = 0;

ShootManager::ShootManager( Ogre::SceneManager * sceneMgr)
{
  _sceneMgr = sceneMgr;
  _camera = _sceneMgr->getCamera("MainCamera");

  _world = MapManager::getSingletonPtr()->getPhysicWorld();
}

ShootManager::~ShootManager()
{
  // Eliminar cuerpos rigidos --------------------------------------
  std::deque <OgreBulletDynamics::RigidBody *>::iterator
  itBody = _bodies.begin();
  while (_bodies.end() != itBody)
  {
    delete *itBody;
    ++itBody;
  }

  // Eliminar formas de colision -----------------------------------
  std::deque<OgreBulletCollisions::CollisionShape *>::iterator
  itShape = _shapes.begin();
  while (_shapes.end() != itShape)
  {
    delete *itShape;
    ++itShape;
  }

  _bodies.clear();
  _shapes.clear();

  _sceneMgr = nullptr;
}

void ShootManager::initWorld()
{
  // Creamos forma de colision para el plano -----------------------
  OgreBulletCollisions::CollisionShape *Shape;
  Shape = new OgreBulletCollisions::StaticPlaneCollisionShape(Ogre::Vector3(0,1,0), 0);   // Vector normal y distancia
  OgreBulletDynamics::RigidBody *rigidBodyPlane = new OgreBulletDynamics::RigidBody("rigidBodyPlane", _world);

  // Creamos la forma estatica (forma, Restitucion, Friccion) ------
  rigidBodyPlane->setStaticShape(Shape, 0.1, 0.8);

  // Anadimos los objetos Shape y RigidBody ------------------------
  _shapes.push_back(Shape);
  _bodies.push_back(rigidBodyPlane);
}

void ShootManager::shootBall()
{
  Vector3 position = (_camera->getDerivedPosition() + _camera->getDerivedDirection().normalisedCopy() * 10);

  Entity *entity = NULL;
  entity = _sceneMgr->createEntity("Ball" + StringConverter::toString(_numEntities), "ball.mesh");

  SceneNode *node = _sceneMgr->getRootSceneNode()->createChildSceneNode();
  node->attachObject(entity);

  OgreBulletCollisions::StaticMeshToShapeConverter *trimeshConverter = NULL;
  OgreBulletCollisions::CollisionShape *bodyShape = NULL;
  OgreBulletDynamics::RigidBody *rigidBody = NULL;

  trimeshConverter = new OgreBulletCollisions::StaticMeshToShapeConverter(entity);
  bodyShape = trimeshConverter->createConvex();

  rigidBody = new OgreBulletDynamics::RigidBody("rigidBody" + StringConverter::toString(_numEntities), _world);
  // Restitucion, friccion y masa
  rigidBody->setShape(node, bodyShape, 0.6, 0.6, 5.0 , position, Quaternion::IDENTITY);

  rigidBody->setLinearVelocity( _camera->getDerivedDirection().normalisedCopy() * 10.0);

  _numEntities++;

  // Anadimos los objetos a las deques
  _shapes.push_back(bodyShape);
  _bodies.push_back(rigidBody);
}

ShootManager& ShootManager::getSingleton() {
  assert(msSingleton);
  return (*msSingleton);
}

ShootManager* ShootManager::getSingletonPtr() {
  assert(msSingleton);
  return msSingleton;
}
