#pragma once

#include "OgreMaterialManager.h"
#include "OgreOverlayManager.h"
#include "OgreTechnique.h"
#include "OgreBlendMode.h"
#include <string>

#include "Enumerations.hpp"

class Fader
{
public:
     static constexpr float FADE_DURATION = 0.5f;

     Fader();
     ~Fader();

     void startFadeIn( std::function<void ()> callback = nullptr );
     void startFadeOut( std::function<void ()> callback = nullptr );
     void update( double timeSinceLastFrame );
     void setNextMap( enumerations::Maps newMap );

protected:

     const std::string& _overlay_name  = "Overlays/Fader";
     const std::string& _material_name = "Materials/OverlayMaterial";

     double _alpha;
     double _current_dur;
     double _total_dur;
     Ogre::TextureUnitState *_tex_unit;
     Ogre::Overlay *_overlay;

     enumerations::Maps _newMap;
     std::function<void ()> _callback_fade_in;
     std::function<void ()> _callback_fade_out;

     enum _fadeop
     {
          FADE_NONE,
          FADE_IN,
          FADE_OUT,
     } _fadeop;
};
