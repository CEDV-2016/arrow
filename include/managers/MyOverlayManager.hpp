#pragma once

#include <Ogre.h>
#include <OgreOverlaySystem.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>
#include <string>

class MyOverlayManager : public Ogre::Singleton<MyOverlayManager>
{
public:

  MyOverlayManager();
  ~MyOverlayManager();

  void createHUD();
  void destroyHUD();

  void setPlayerName(std::string name);
  void setTime(std::string time);
  void setArrowsLeft(std::string arrows);
  void setDianasLeft(std::string dianas);

  // Inherited from Ogre::Singleton.
  static MyOverlayManager& getSingleton ();
  static MyOverlayManager* getSingletonPtr ();

private:
  Ogre::OverlayManager * _ogreOverlayMgr;
  Ogre::Overlay * _overlay;
  Ogre::OverlayElement * _overlayElement;
};
