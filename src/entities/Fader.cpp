#include "Fader.hpp"
#include "MapManager.hpp"

Fader::Fader()
{
  _fadeop = FADE_NONE;
  _alpha = 0.0;

  // Get the material by name
  Ogre::ResourcePtr resptr = Ogre::MaterialManager::getSingleton().getByName( _material_name );
  Ogre::Material * mat = dynamic_cast<Ogre::Material*>(resptr.getPointer());

  Ogre::Technique *tech = mat->getTechnique(0);
  Ogre::Pass *pass = tech->getPass(0);
  _tex_unit = pass->getTextureUnitState(0);

  // Get the _overlay
  _overlay = Ogre::OverlayManager::getSingleton().getByName( _overlay_name );
  _overlay->hide();
}

Fader::~Fader(){}

void Fader::startFadeIn( std::function<void ()> callback )
{
  _alpha = 1.0;
  _total_dur = FADE_DURATION;
  _current_dur = FADE_DURATION;
  _callback_fade_in = callback;
  _fadeop = FADE_IN;
  _overlay->show();
}

void Fader::startFadeOut( std::function<void ()> callback )
{
  _alpha = 0.0;
  _total_dur = FADE_DURATION;
  _current_dur = 0.0;
  _callback_fade_out = callback;
  _fadeop = FADE_OUT;
  _overlay->show();
}

void Fader::update( double timeSinceLastFrame )
{
  if( _fadeop != FADE_NONE && _tex_unit )
  {
    // Set the _alpha value of the _overlay
    _tex_unit->setAlphaOperation( Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, _alpha );

    // If fading in, decrease the _alpha until it reaches 0.0 (completely transparent)
    if( _fadeop == FADE_IN )
    {
      // 0.05 is due to the single frame in which loads the map, which takes longer than usual. Otherwise, the fade gets messed up
      if (timeSinceLastFrame > 0.05) timeSinceLastFrame = 0.05;
      _current_dur -= timeSinceLastFrame;
      _alpha = _current_dur / _total_dur;
      if( _alpha < 0.0 )
      {
        _overlay->hide();
        _fadeop = FADE_NONE;

        if ( _callback_fade_in )
        {
          _callback_fade_in();
        }
      }
    }

    // If fading out, increase the _alpha until it reaches 1.0 (completely black)
    else if( _fadeop == FADE_OUT )
    {
      _current_dur += timeSinceLastFrame;
      _alpha = _current_dur / _total_dur;
      if( _alpha > 1.0 )
      {
        _fadeop = FADE_NONE;

        // When the overlay gets completely black executes the callback (normally load the new map)
        if( _callback_fade_out )
        {
          _callback_fade_out();
        }
      }
    }
  }
}

void Fader::setNextMap( enumerations::Maps newMap )
{
  _newMap = newMap;
}
