#include "MainState.hpp"
#include "NewGameState.hpp"
#include "CreditsState.hpp"
#include "RankingState.hpp"
#include "SoundFXManager.hpp"

template<> MainState* Ogre::Singleton<MainState>::msSingleton = 0;

MainState* MainState::getSingletonPtr () {
    return msSingleton;
}

MainState& MainState::getSingleton () {
    assert (msSingleton);
    return *msSingleton;
}

void MainState::enter () {
  _root = Ogre::Root::getSingletonPtr();

  _sceneManager = _root->getSceneManager("SceneManager");
  _camera = _sceneManager->getCamera("MainCamera");
  _viewport = _root->getAutoCreatedWindow()->getViewport(0);

  SoundFXManager::getSingletonPtr()->load("menu_item.wav")->play();

  createGUI();

  _exit = false;
}

void MainState::exit() {
  _sceneManager->clearScene();
  _root->getAutoCreatedWindow()->removeAllViewports();
}

void MainState::pause () {
  _main->hide();
}

void MainState::resume () {
  _main->show();
}

bool MainState::frameStarted (const Ogre::FrameEvent &evt) {
    return true;
}

bool MainState::frameEnded (const Ogre::FrameEvent &evt) {
    return !_exit;
}

void MainState::keyPressed (const OIS::KeyEvent &e) {
}

void MainState::keyReleased (const OIS::KeyEvent &e) {
}

void MainState::mouseMoved (const OIS::MouseEvent &e) {
}

void MainState::mousePressed (const OIS::MouseEvent &e, OIS::MouseButtonID id) {}

void MainState::mouseReleased (const OIS::MouseEvent &e, OIS::MouseButtonID id) {}

void MainState::createGUI()
{
  if(_main == NULL){
    //Config Window
    _main = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("main.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_main);

    //Config Buttons
    CEGUI::Window* _newButton = _main->getChild("NewButton");
    _newButton->subscribeEvent(CEGUI::PushButton::EventClicked,
			     CEGUI::Event::Subscriber(&MainState::newGame,this));
    CEGUI::Window* _creditsButton = _main->getChild("CreditsButton");
    _creditsButton->subscribeEvent(CEGUI::PushButton::EventClicked,
       		 CEGUI::Event::Subscriber(&MainState::navigateToCredits,this));
    CEGUI::Window* _rankingButton = _main->getChild("RankingButton");
    _rankingButton->subscribeEvent(CEGUI::PushButton::EventClicked,
           CEGUI::Event::Subscriber(&MainState::navigateToRanking,this));
    CEGUI::Window* _exitButton = _main->getChild("ExitButton");
    _exitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
			     CEGUI::Event::Subscriber(&MainState::quit,this));
  } else{
    _main->show();
  }
}

bool MainState::newGame(const CEGUI::EventArgs &e)
{
  pushState(NewGameState::getSingletonPtr());
  return true;
}

bool MainState::navigateToCredits(const CEGUI::EventArgs &e)
{
  pushState(CreditsState::getSingletonPtr());
  return true;
}

bool MainState::navigateToRanking(const CEGUI::EventArgs &e)
{
  pushState(RankingState::getSingletonPtr());
  return true;
}

bool MainState::quit(const CEGUI::EventArgs &e)
{
  _exit = true;
  return true;
}
