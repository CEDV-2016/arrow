#include "PlayState.hpp"
#include "PauseState.hpp"
#include "EndState.hpp"
#include "SoundFXManager.hpp"
#include "MyOverlayManager.hpp"

template<> PlayState* Ogre::Singleton<PlayState>::msSingleton = 0;

PlayState::PlayState()
{
  _game = new Game();
  _playGUI = NULL;
  _timer = new Timer();
}

void
PlayState::enter ()
{
  _timer->start();

  _root = Ogre::Root::getSingletonPtr();

  _sceneMgr = _root->getSceneManager("SceneManager");
  _camera = _sceneMgr->getCamera("MainCamera");
  _mapManager = MapManager::getSingletonPtr();

  _sceneMgr->clearScene(); //deleting background image
  Ogre::Camera* cam = _sceneMgr->getCamera("MainCamera");
  cam->setPosition( Ogre::Vector3(0, 0, 0) );
  //_sceneMgr->getCamera("MainCamera")->lookAt( Ogre::Vector3(-5, 5, -9) );
  cam->setNearClipDistance(0.001);
  cam->setFarClipDistance(10000);

  createScene();
  createHUD();

  Ogre::SceneNode *_node = _sceneMgr->getSceneNode("Player");
  this->cameraNode = _node->createChildSceneNode();
  this->cameraNode->setPosition(0, 0.5, 0);
  // Create the camera's yaw node as a child of camera's top node.
  this->cameraYawNode = this->cameraNode->createChildSceneNode();
  //Ogre::Entity* playerEntity = _sceneMgr->createEntity("Player", "Player.mesh");
  //this->cameraYawNode->attachObject(playerEntity);
  // Create the camera's pitch node as a child of camera's yaw node.
  this->cameraPitchNode = this->cameraYawNode->createChildSceneNode();
  this->cameraPitchNode->attachObject(this->_camera);

  moveScale = 0.01f;
  rotateScale = 1;
  rotX = 0;
  rotY = 0;
  translateVector = Ogre::Vector3::ZERO;

  _exitGame = false;
}

void
PlayState::exit ()
{
  _mapManager->destroyAllMaps();
  _playGUI->hide();
  _sceneMgr->clearScene();
  _root->getAutoCreatedWindow()->removeAllViewports();
}

void
PlayState::pause()
{
}

void
PlayState::resume()
{
}

bool
PlayState::frameStarted
(const Ogre::FrameEvent& evt)
{
  Ogre::Real deltaT = evt.timeSinceLastFrame;

  _mapManager->update( deltaT );

  MyOverlayManager::getSingletonPtr()->setTime( _timer->getGameplayTime() );

  moveCamera();

  return true;
}

bool
PlayState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
  {
    return false;
  }
  else
  {
    return true;
  }
}

void
PlayState::keyPressed
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
PlayState::keyReleased
(const OIS::KeyEvent &e)
{
  if (e.key == OIS::KC_ESCAPE) pushState(PauseState::getSingletonPtr());

  if(e.key == OIS::KC_UP || e.key == OIS::KC_DOWN){
    this->translateVector.z = 0;
  }
  if(e.key == OIS::KC_LEFT || e.key == OIS::KC_RIGHT){
    this->translateVector.x = 0;
  }
}

void
PlayState::mouseMoved
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
  if (((pitchAng < 15.0f && pitchAngSig >= 0) ||
 		 (pitchAng > 15.0f && pitchAngSig >= 0 && pitchDegree < 0)) ||
 		  ((pitchAng < 10.0f && pitchAngSig < 0) ||
      (pitchAng > 10.0f && pitchAngSig < 0 && pitchDegree > 0))) {
	 			this->cameraPitchNode->pitch(this->rotY);
	 }
}

void
PlayState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
PlayState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

PlayState*
PlayState::getSingletonPtr ()
{
  return msSingleton;
}

PlayState&
PlayState::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}

void PlayState::createScene()
{
  _mapManager->changeMap( enumerations::Maps::ROOM, false );
  Ogre::SceneNode* nodePlayer = _sceneMgr->createSceneNode("Player");
  nodePlayer->setScale(3.5,3.5,3.5);
  _sceneMgr->getRootSceneNode()->addChild(nodePlayer);
}

void PlayState::createHUD()
{
  MyOverlayManager::getSingletonPtr()->createHUD();
  MyOverlayManager::getSingletonPtr()->setPlayerName( "Pedro" );
  MyOverlayManager::getSingletonPtr()->setTime( "1.59" );
  MyOverlayManager::getSingletonPtr()->setDianasLeft( "x6" );
  MyOverlayManager::getSingletonPtr()->setArrowsLeft( "x4" );
}

void PlayState::moveCamera()
{
  this->cameraNode->translate(this->cameraYawNode->getOrientation() *
                             translateVector,
                             Ogre::SceneNode::TS_LOCAL);
}

void PlayState::setPlayerName(std::string name)
{

}
