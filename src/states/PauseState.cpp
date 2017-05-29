#include "PauseState.hpp"
#include "IntroState.hpp"
#include "PlayState.hpp"

template<> PauseState* Ogre::Singleton<PauseState>::msSingleton = 0;

void
PauseState::enter ()
{
  _root = Ogre::Root::getSingletonPtr();

  _sceneMgr = _root->getSceneManager("SceneManager");
  _camera = _sceneMgr->getCamera("MainCamera");
  createGUI();

  _exitGame = false;
}

void
PauseState::exit ()
{
  _pauseGUI->hide();
}

void
PauseState::pause ()
{
}

void
PauseState::resume ()
{
}

bool
PauseState::frameStarted
(const Ogre::FrameEvent& evt)
{
  return true;
}

bool
PauseState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
    return false;

  return true;
}

void
PauseState::keyPressed
(const OIS::KeyEvent &e) {
}

void
PauseState::keyReleased
(const OIS::KeyEvent &e)
{
  if (e.key == OIS::KC_P) popState();
}

void
PauseState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
PauseState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
PauseState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

PauseState*
PauseState::getSingletonPtr ()
{
  return msSingleton;
}

PauseState&
PauseState::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}

void PauseState::createGUI()
{
  if(_pauseGUI == NULL){
    //Config Window
    _pauseGUI = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("pause.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_pauseGUI);

    //Config Buttons
    CEGUI::Window* resumeButton = _pauseGUI->getChild("ResumeButton");
    resumeButton->subscribeEvent(CEGUI::PushButton::EventClicked,
			     CEGUI::Event::Subscriber(&PauseState::back,
						      this));
    CEGUI::Window* exitButton = _pauseGUI->getChild("ExitButton");
    exitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
			     CEGUI::Event::Subscriber(&PauseState::exitPause,
						      this));
  } else{
    _pauseGUI->show();
  }
}

bool PauseState::back(const CEGUI::EventArgs &e)
{
  popState();
  return true;
}

bool PauseState::exitPause(const CEGUI::EventArgs &e)
{
  restartState(IntroState::getSingletonPtr());
  return true;
}
