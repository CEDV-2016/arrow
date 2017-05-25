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
  _timer = new MyTimer();
}

void
PlayState::enter ()
{
  _timer->start();

  _root = Ogre::Root::getSingletonPtr();

  _sceneMgr = _root->getSceneManager("SceneManager");
  _camera = _sceneMgr->getCamera("MainCamera");
  _mapManager = MapManager::getSingletonPtr();
  _camManager = CameraManager::getSingletonPtr();
  _shootManager = ShootManager::getSingletonPtr();

  _sceneMgr->clearScene(); //deleting background image
  Ogre::Camera* cam = _sceneMgr->getCamera("MainCamera");
  cam->setPosition( Ogre::Vector3(0, 0, 0) );
  //_sceneMgr->getCamera("MainCamera")->lookAt( Ogre::Vector3(-5, 5, -9) );
  cam->setNearClipDistance(0.001);
  cam->setFarClipDistance(10000);

  createScene();
  createHUD();

  _camManager->initCamera();
  _shootManager->initWorld();

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
  _timer->pause();
}

void
PlayState::resume()
{
  _timer->resume();
}

bool
PlayState::frameStarted
(const Ogre::FrameEvent& evt)
{
  Ogre::Real deltaT = evt.timeSinceLastFrame;

  _mapManager->update( deltaT );

  MyOverlayManager::getSingletonPtr()->setTime( _timer->getGameplayTime() );

  _camManager->moveCamera();

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
  _camManager->keyPressed(e);
}

void
PlayState::keyReleased
(const OIS::KeyEvent &e)
{
  if (e.key == OIS::KC_ESCAPE) pushState(PauseState::getSingletonPtr());

  _camManager->keyReleased(e);
}

void
PlayState::mouseMoved
(const OIS::MouseEvent &e)
{
  _camManager->mouseMoved(e);
}

void
PlayState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  //if (e.key == OIS::MB_Left) {
    _shootManager->shootBall();
  //}
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
  MyOverlayManager::getSingletonPtr()->setDianasLeft( "x5" );
  MyOverlayManager::getSingletonPtr()->setArrowsLeft( "x4" );
}

void PlayState::setPlayerName(std::string name)
{

}
