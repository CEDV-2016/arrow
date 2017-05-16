#include <sstream>

#include "RankingState.hpp"
#include "SoundFXManager.hpp"

template<> RankingState* Ogre::Singleton<RankingState>::msSingleton = 0;

RankingState::RankingState() {
  _rankingGUI = NULL;
  _rankingManager = new RankingManager;
}

void
RankingState::enter ()
{
  _root = Ogre::Root::getSingletonPtr();

  _sceneMgr = _root->getSceneManager("SceneManager");
  _camera = _sceneMgr->getCamera("MainCamera");
  createGUI();

  SoundFXManager::getSingletonPtr()->load("menu_item.wav")->play();

  _exitGame = false;
}

void
RankingState::exit ()
{
  _rankingGUI->hide();
}

void
RankingState::pause ()
{
}

void
RankingState::resume ()
{
}

bool
RankingState::frameStarted
(const Ogre::FrameEvent& evt)
{
  return true;
}

bool
RankingState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
    return false;

  return true;
}

void
RankingState::keyPressed
(const OIS::KeyEvent &e)
{
}

void
RankingState::keyReleased
(const OIS::KeyEvent &e)
{
  if (e.key == OIS::KC_ESCAPE)
  {
    _exitGame = true;
  }
}

void
RankingState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
RankingState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
RankingState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

RankingState*
RankingState::getSingletonPtr ()
{
return msSingleton;
}

RankingState&
RankingState::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}

void RankingState::createGUI(){
    if(_rankingGUI == NULL){
    //Config Window
    _rankingGUI = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("ranking.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_rankingGUI);

    //Config Buttons
    CEGUI::Window* backButton = _rankingGUI->getChild("BackButton");
    backButton->subscribeEvent(CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&RankingState::back, this));

    std::vector<std::string> ranking = _rankingManager->getRanking();
    std::string name, score;
    for (unsigned int i=0; i<ranking.size(); i+=2){
       name = std::string("Name") + std::to_string(i/2+1);
       score = std::string("Point") + std::to_string(i/2+1);
       CEGUI::Window* name_record = _rankingGUI->getChild(name);
       name_record->setText(ranking[i]);
       CEGUI::Window* score_record = _rankingGUI->getChild(score);
       score_record ->setText(ranking[i+1]);
    }
  } else{
    std::vector<std::string> ranking = _rankingManager->getRanking();
    std::string name, score;
    for (unsigned int i=0; i<ranking.size(); i+=2){
       name = std::string("Name") + std::to_string(i/2+1);
       score = std::string("Point") + std::to_string(i/2+1);
       CEGUI::Window* name_record = _rankingGUI->getChild(name);
       name_record->setText(ranking[i]);
       CEGUI::Window* score_record = _rankingGUI->getChild(score);
       score_record ->setText(ranking[i+1]);
    }
    _rankingGUI->show();
  }
}

bool RankingState::back(const CEGUI::EventArgs &e)
{
  popState();
  return true;
}
