#include "IntroState.hpp"
#include "EndState.hpp"

template<> EndState* Ogre::Singleton<EndState>::msSingleton = 0;

EndState::EndState() {
  _endGUI = NULL;
}

void
EndState::enter ()
{
  _root = Ogre::Root::getSingletonPtr();

  _sceneMgr = _root->getSceneManager("SceneManager");
  _camera = _sceneMgr->getCamera("MainCamera");
  createGUI();

  _exitGame = false;
}

void
EndState::exit ()
{
  _endGUI->hide();
}

void
EndState::pause ()
{
}

void
EndState::resume ()
{
}

bool
EndState::frameStarted
(const Ogre::FrameEvent& evt)
{
  return true;
}

bool
EndState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
  return false;

  return true;
}

void
EndState::keyPressed
(const OIS::KeyEvent &e) {
}

void
EndState::keyReleased
(const OIS::KeyEvent &e)
{
}

void
EndState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
EndState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
EndState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

EndState*
EndState::getSingletonPtr ()
{
  return msSingleton;
}

EndState&
EndState::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}

void EndState::createGUI()
{
  if(_endGUI == NULL){
    //Config Window
    _endGUI = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("endGame.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_endGUI);

    //Config buttons
    CEGUI::Window* resumeButton = _endGUI->getChild("endWinButton");
    resumeButton->subscribeEvent(CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&EndState::finish, this));
    _titleView = _endGUI->getChild("winLabel");
    _nameView = _endGUI->getChild("nameLabel");
    _pointsView = _endGUI->getChild("pointsLabel");

    //Set data
    if (_win) {
      _titleView->setText("Has ganado");
    }else {
      _titleView->setText("Has perdido");
    }
    _nameView->setText(_name);
    _pointsView->setText(std::to_string(_points));
  } else{
    _nameView->setText(_name);
    _pointsView->setText(std::to_string(_points));
    _endGUI->show();
  }
}

bool EndState::finish(const CEGUI::EventArgs &e)
{
  this->popState();
  restartState(IntroState::getSingletonPtr());
  return true;
}

void EndState::setData(bool win, std::string name, int points)
{
  _win = win;
  _name = name;
  _points = points;
  _rankingManager = new RankingManager();
  _rankingManager->setRanking(name, points);
}
