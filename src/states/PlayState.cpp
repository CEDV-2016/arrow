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
}

void
PlayState::enter ()
{
  _root = Ogre::Root::getSingletonPtr();

  _sceneMgr = _root->getSceneManager("SceneManager");
  _camera = _sceneMgr->getCamera("MainCamera");
  _mapManager = MapManager::getSingletonPtr();

  _sceneMgr->clearScene(); //deleting background image
  _sceneMgr->getCamera("MainCamera")->setPosition( Ogre::Vector3(-12, 10, 12) );
  _sceneMgr->getCamera("MainCamera")->lookAt( Ogre::Vector3(-5, 5, -9) );

  createScene();
  createHUD();



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
}

void
PlayState::keyReleased
(const OIS::KeyEvent &e)
{
  if (e.key == OIS::KC_ESCAPE) pushState(PauseState::getSingletonPtr());
}

void
PlayState::mouseMoved
(const OIS::MouseEvent &e)
{
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
}

void PlayState::createHUD()
{
  new MyOverlayManager();
  MyOverlayManager::getSingletonPtr()->createHUD();
  MyOverlayManager::getSingletonPtr()->setPlayerName( "Pedro" );
  MyOverlayManager::getSingletonPtr()->setTime( "1.59" );
  MyOverlayManager::getSingletonPtr()->setDianasLeft( "x6" );
  MyOverlayManager::getSingletonPtr()->setArrowsLeft( "x4" );
}

void PlayState::setPlayerName(std::string name)
{

}
