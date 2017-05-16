#include "PlayState.hpp"
#include "PauseState.hpp"
#include "EndState.hpp"
#include "SoundFXManager.hpp"
#include "OgreOverlayManager.h"

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
  // createGUI();

  Ogre::Overlay *overlay = Ogre::OverlayManager::getSingletonPtr()->getByName("HUD");

  Ogre::OverlayElement *oe;
  oe = Ogre::OverlayManager::getSingletonPtr()->getOverlayElement("nameTextArea");
  oe->setCaption("Pedro");

  oe = Ogre::OverlayManager::getSingletonPtr()->getOverlayElement("dianaTextArea");
  oe->setCaption("x4");

  oe = Ogre::OverlayManager::getSingletonPtr()->getOverlayElement("arrowTextArea");
  oe->setCaption("x6");

  overlay->show();

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
  // TODO Delegate all the gameplay's logic to a GameplayManager
  _mapManager->changeMap( enumerations::Maps::ROOM, false );
}

void PlayState::createGUI()
{
  if(_playGUI == NULL){
    //Config Window
    _playGUI = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("play.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_playGUI);

    //Config Buttons
    CEGUI::Window* _layout = _playGUI->getChild("FrameWindow");
    _nameView = _layout->getChild("NameLabel");
  }
  else
  {
    _playGUI->show();
  }
}

void PlayState::setPlayerName(std::string name)
{

}
