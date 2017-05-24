#include "CameraManager.hpp"

template<> CameraManager* Ogre::Singleton<CameraManager>::msSingleton = 0;

CameraManager::CameraManager( Ogre::SceneManager * sceneMgr )
{
  _sceneMgr = sceneMgr;

  moveScale = 0.01f;
  rotateScale = 1;
  rotX = 0;
  rotY = 0;
  translateVector = Ogre::Vector3::ZERO;
}

void
CameraManager::keyPressed
(const OIS::KeyEvent &e)
{
    if(e.key == OIS::KC_UP){
      this->translateVector.z = -(this->moveScale);
    }
    if(e.key == OIS::KC_DOWN){
      this->translateVector.z = this->moveScale;
    }
    if(e.key == OIS::KC_LEFT){
      this->translateVector.x = -(this->moveScale);
    }
    if(e.key == OIS::KC_RIGHT){
      this->translateVector.x = this->moveScale;
    }
}

void
CameraManager::keyReleased
(const OIS::KeyEvent &e)
{
  if(e.key == OIS::KC_UP || e.key == OIS::KC_DOWN){
    this->translateVector.z = 0;
  }
  if(e.key == OIS::KC_LEFT || e.key == OIS::KC_RIGHT){
    this->translateVector.x = 0;
  }
}

void
CameraManager::mouseMoved
(const OIS::MouseEvent &e)
{
  rotX = Ogre::Degree(-e.state.X.rel);
  rotY = Ogre::Degree(-e.state.Y.rel);

  // Yaws the camera according to the mouse relative movement.
	this->cameraYawNode->yaw(this->rotX);

  // Pitches the camera according to the mouse relative movement.
	Ogre::Real pitchAng = (2 * Ogre::Degree(Ogre::Math::ACos(this->cameraPitchNode->getOrientation().w)).valueDegrees());
  Ogre::Real pitchAngSig = this->cameraPitchNode->getOrientation().x;
  Ogre::Real pitchDegree = rotY.valueDegrees();
  if (((pitchAng < 25.0f && pitchAngSig >= 0) ||
 		 (pitchAng > 25.0f && pitchAngSig >= 0 && pitchDegree < 0)) ||
 		  ((pitchAng < 10.0f && pitchAngSig < 0) ||
      (pitchAng > 10.0f && pitchAngSig < 0 && pitchDegree > 0))) {
	 			this->cameraPitchNode->pitch(this->rotY);
	 }
}

void CameraManager::initCamera()
{
  Ogre::Camera* cam = _sceneMgr->getCamera("MainCamera");
  cam->setPosition( Ogre::Vector3(0, 1, 2) );
  //_sceneMgr->getCamera("MainCamera")->lookAt( Ogre::Vector3(-5, 5, -9) );
  cam->setNearClipDistance(0.001);
  cam->setFarClipDistance(10000);

  Ogre::SceneNode *_node = _sceneMgr->getSceneNode("Player");
  this->cameraNode = _node->createChildSceneNode();
  this->cameraNode->setPosition(0, 0, 0);
    // Create the camera's yaw node as a child of camera's top node.
  this->cameraYawNode = this->cameraNode->createChildSceneNode();
  Ogre::Entity* playerEntity = _sceneMgr->createEntity("Player", "Arrow.mesh");
  this->cameraYawNode->attachObject(playerEntity);
  this->cameraYawNode->setScale(0.05, 0.05, 0.05);
  // Create the camera's pitch node as a child of camera's yaw node.
  this->cameraPitchNode = this->cameraYawNode->createChildSceneNode();
  this->cameraPitchNode->attachObject(cam);
}

void CameraManager::moveCamera()
{
  this->cameraNode->translate(this->cameraYawNode->getOrientation() *
                             translateVector,
                             Ogre::SceneNode::TS_LOCAL);
}

CameraManager& CameraManager::getSingleton() {
  assert(msSingleton);
  return (*msSingleton);
}

CameraManager* CameraManager::getSingletonPtr() {
  assert(msSingleton);
  return msSingleton;
}
