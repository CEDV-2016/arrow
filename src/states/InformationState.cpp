#include "InformationState.hpp"
#include "MainState.hpp"
#include "MapManager.hpp"
#include "MyOverlayManager.hpp"
#include "SoundFXManager.hpp"

template<> InformationState* Ogre::Singleton<InformationState>::msSingleton = 0;

void
InformationState::enter ()
{
  _root = Ogre::Root::getSingletonPtr();
  _sceneMgr = _root->getSceneManager("SceneManager");

  createGUI();
  loadInformationOverlay();
  _exitGame = false;

  SoundFXManager::getSingletonPtr()->load("menu_item.wav")->play();
}

void
InformationState::exit()
{
  Ogre::OverlayManager::getSingletonPtr()->getByName("InformationOverlay")->hide();
  _infoCEGUI->hide();
}

void
InformationState::pause ()
{
  Ogre::OverlayManager::getSingletonPtr()->getByName("InformationOverlay")->hide();
  _infoCEGUI->hide();
}

void
InformationState::resume ()
{
  Ogre::OverlayManager::getSingletonPtr()->getByName("InformationOverlay")->show();
  _infoCEGUI->show();
}

bool
InformationState::back(const CEGUI::EventArgs &e)
{
  popState();
  return true;
}

bool
InformationState::frameStarted
(const Ogre::FrameEvent& evt)
{
  MapManager::getSingletonPtr()->update( evt.timeSinceLastFrame );

  return true;
}

bool
InformationState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
  return false;

  return true;
}

void
InformationState::keyPressed
(const OIS::KeyEvent &e)
{
}

void
InformationState::keyReleased
(const OIS::KeyEvent &e )
{
  if (e.key == OIS::KC_ESCAPE)
  {
    popState();
  }
}

void
InformationState::mouseMoved
(const OIS::MouseEvent &e)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(e.state.X.abs, e.state.Y.abs);
}

void
InformationState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
InformationState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

InformationState*
InformationState::getSingletonPtr ()
{
  return msSingleton;
}

InformationState&
InformationState::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}

void InformationState::createGUI()
{
  if(_infoCEGUI == NULL)
  {
    //Config Window
    _infoCEGUI = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("information.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_infoCEGUI);

    //Config buttons
    CEGUI::Window* backButton = _infoCEGUI->getChild("BackButton");
    backButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&InformationState::back, this));
  }
  else
  {
    _infoCEGUI->show();
  }
}

void InformationState::loadInformationOverlay()
{
  Ogre::OverlayManager::getSingletonPtr()->getByName("InformationOverlay")->show();
}
