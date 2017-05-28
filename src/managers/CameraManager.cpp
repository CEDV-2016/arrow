#include "CameraManager.hpp"
#include "ShootManager.hpp"
#include "MyPhysicsManager.hpp"

#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsStaticPlaneShape.h>
#include <Shapes/OgreBulletCollisionsBoxShape.h>
#include "Shapes/OgreBulletCollisionsConvexHullShape.h"
#include "Shapes/OgreBulletCollisionsTrimeshShape.h"
#include "Utils/OgreBulletCollisionsMeshToShapeConverter.h"
#include "Shapes/OgreBulletCollisionsSphereShape.h"
#include "OgreBulletCollisionsRay.h"

template<> CameraManager* Ogre::Singleton<CameraManager>::msSingleton = 0;

CameraManager::CameraManager( Ogre::SceneManager * sceneMgr )
{
  _sceneMgr = sceneMgr;

  moveScale = 1.15f;
  rotateScale = 1;
  rotX = 0;
  rotY = 0;
  translateVector = Ogre::Vector3::ZERO;
}

void
CameraManager::keyPressed
(const OIS::KeyEvent &e)
{
    if(e.key == OIS::KC_W)
    {
      this->translateVector.z = this->moveScale * _last_deltaT;
    }
    if(e.key == OIS::KC_S)
    {
      this->translateVector.z = -(this->moveScale * _last_deltaT);
    }
    if(e.key == OIS::KC_A)
    {
      this->translateVector.x = this->moveScale * _last_deltaT;
    }
    if(e.key == OIS::KC_D)
    {
      this->translateVector.x = -(this->moveScale * _last_deltaT);
    }
}

void
CameraManager::keyReleased
(const OIS::KeyEvent &e)
{
  if(e.key == OIS::KC_W || e.key == OIS::KC_S)
  {
    this->translateVector.z = 0;
  }
  if(e.key == OIS::KC_A || e.key == OIS::KC_D)
  {
    this->translateVector.x = 0;
  }
}

void
CameraManager::mouseMoved
(const OIS::MouseEvent &e)
{
  float scale = 0.001f;

  rotX = Ogre::Degree(-e.state.X.rel);
  rotY = Ogre::Degree(-e.state.Y.rel);

  // Yaws the camera according to the mouse relative movement.
	this->cameraYawNode->yaw(this->rotX * scale / _last_deltaT);

  // Pitches the camera according to the mouse relative movement.
	Ogre::Real pitchAng = (2 * Ogre::Degree(Ogre::Math::ACos(this->cameraPitchNode->getOrientation().w)).valueDegrees());
  Ogre::Real pitchAngSig = this->cameraPitchNode->getOrientation().x;
  Ogre::Real pitchDegree = rotY.valueDegrees();

  if (((pitchAng < 179.030f && pitchAngSig >= 0) ||
 		 (pitchAng > 179.030f && pitchAngSig >= 0 && pitchDegree < 0)) ||
 		  ((pitchAng < 179.010f && pitchAngSig < 0) ||
      (pitchAng > 179.010f && pitchAngSig < 0 && pitchDegree > 0))) {
	 			this->cameraPitchNode->pitch(this->rotY * scale / _last_deltaT);
	 }
}

void CameraManager::initCamera()
{
  Ogre::Camera* cam = _sceneMgr->getCamera("MainCamera");
  cam->setPosition( Ogre::Vector3(0, 1, 3) );
  //_sceneMgr->getCamera("MainCamera")->lookAt( Ogre::Vector3(-5, 5, -9) );
  cam->setNearClipDistance(0.0001);
  cam->setFarClipDistance(10000);

  Ogre::SceneNode *_node = _sceneMgr->getSceneNode("Player");
  this->cameraNode = _node->createChildSceneNode();
  this->cameraNode->setPosition(1, 0, 0);
    // Create the camera's yaw node as a child of camera's top node.
  this->cameraYawNode = this->cameraNode->createChildSceneNode();
  Ogre::Entity* playerEntity = _sceneMgr->createEntity("Player", "Arrow.mesh");
  this->cameraYawNode->attachObject(playerEntity);
  this->cameraYawNode->setScale(0.05, 0.05, 0.05);

  OgreBulletCollisions::StaticMeshToShapeConverter *trimeshConverter =
    new OgreBulletCollisions::StaticMeshToShapeConverter( playerEntity );
  Ogre::Vector3 *vertices = (Ogre::Vector3*)trimeshConverter->getVertices();
  int num = trimeshConverter->getVertexCount();
  for (int i = 0; i < num; ++i)
  {
    vertices[i]*=0.18;
  }
  OgreBulletCollisions::TriangleMeshCollisionShape *dartboard_trimesh = trimeshConverter->createTrimesh();
  OgreBulletDynamics::RigidBody *physic_dartboard =
    new OgreBulletDynamics::RigidBody( "playerBody", MyPhysicsManager::getSingletonPtr()->getPhysicWorld() );
  physic_dartboard->setShape( this->cameraYawNode, dartboard_trimesh, 0.8, 0.95, 0, Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY );

  // Create the camera's pitch node as a child of camera's yaw node.
  this->cameraPitchNode = this->cameraYawNode->createChildSceneNode();
  this->cameraPitchNode->attachObject(cam);
  this->cameraPitchNode->yaw(Ogre::Degree(179));
}

void CameraManager::moveCamera(Ogre::Real deltaT)
{
  this->cameraNode->translate(this->cameraYawNode->getOrientation() * translateVector, Ogre::SceneNode::TS_LOCAL);
  _last_deltaT = deltaT;
}

CameraManager& CameraManager::getSingleton() {
  assert(msSingleton);
  return (*msSingleton);
}

CameraManager* CameraManager::getSingletonPtr() {
  assert(msSingleton);
  return msSingleton;
}
