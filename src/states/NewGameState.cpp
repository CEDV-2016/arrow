#include "NewGameState.hpp"
#include "PlayState.hpp"
#include "SoundFXManager.hpp"
#include "MapManager.hpp"

template<> NewGameState* Ogre::Singleton<NewGameState>::msSingleton = 0;

NewGameState::NewGameState() {
  _newgameGUI = NULL;
  _nameText = NULL;
}

void
NewGameState::enter ()
{
  _root = Ogre::Root::getSingletonPtr();

  _sceneManager = _root->getSceneManager("SceneManager");
  _camera = _sceneManager->getCamera("MainCamera");
  createGUI();

  SoundFXManager::getSingletonPtr()->load("menu_item.wav")->play();

  _exitGame = false;
}

void
NewGameState::exit ()
{
  _newgameGUI->hide();
}

void
NewGameState::pause ()
{
  _newgameGUI->hide();
}

void
NewGameState::resume ()
{
  _newgameGUI->show();
}

bool
NewGameState::frameStarted
(const Ogre::FrameEvent& evt)
{
  MapManager::getSingletonPtr()->update( evt.timeSinceLastFrame );

  return true;
}

bool
NewGameState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
    return false;

  return true;
}

void
NewGameState::keyPressed
(const OIS::KeyEvent &e)
{
}

void
NewGameState::keyReleased
(const OIS::KeyEvent &e)
{
}

void
NewGameState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
NewGameState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
NewGameState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

NewGameState*
NewGameState::getSingletonPtr ()
{
return msSingleton;
}

NewGameState&
NewGameState::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}

void NewGameState::createGUI(){
    if(_newgameGUI == NULL){
    //Config Window
    _newgameGUI = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("newGame.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_newgameGUI);

    //Config Buttons
    CEGUI::Window* newGameButton = _newgameGUI->getChild("PlayButton");
    newGameButton->subscribeEvent(CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&NewGameState::newGame, this));
    CEGUI::Window* backButton = _newgameGUI->getChild("BackButton");
    backButton->subscribeEvent(CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&NewGameState::back, this));
    _nameText = _newgameGUI->getChild("NameEditBox");
  } else{
    _nameText->setText("");
    _newgameGUI->show();
  }
}

bool NewGameState::newGame(const CEGUI::EventArgs &e)
{
  /*CEGUI::AnimationManager& animMgr = CEGUI::AnimationManager::getSingletonPtr();
  animMgr.loadAnimationsFromXML("Animations.anims");

  CEGUI::Animation* startButtAnim = animMgr.getAnimation("NewGameAnim");
  CEGUI::AnimationInstance* startButtAnimInstance = animMgr.instantiateAnimation(startButtAnim);
  startButtAnimInstance->setTargetWindow(_nameText);
  startButtAnimInstance->start();*/
  _newgameGUI->hide();
  MapManager::getSingletonPtr()->fadeOut( std::bind(&NewGameState::changeState, this) );
  return true;
}

void NewGameState::changeState()
{
  PlayState* playState = PlayState::getSingletonPtr();
  playState->setPlayerName(_nameText->getText().c_str());
  pushState(playState);
}

bool NewGameState::back(const CEGUI::EventArgs &e)
{
  popState();
  return true;
}
