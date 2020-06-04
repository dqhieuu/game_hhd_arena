#ifndef I_SOUND_EFFECT_PLAYER_H
#define I_SOUND_EFFECT_PLAYER_H

#include "SoundEffect.h"
class SoundEffect;

class ISoundEffectPlayer {
   public:
    virtual ~ISoundEffectPlayer(){};
    virtual void setVolume(int volume) = 0;
    virtual void loadSoundEffect(std::string name, std::string path) = 0;
    virtual void play(std::string name, int loops = 0, int time = -1) = 0;
    virtual void stop(int channel = -1) = 0;
    virtual void stop(std::string name) = 0;
    virtual void free(std::string name) = 0;
    virtual void free() = 0;
};

#endif