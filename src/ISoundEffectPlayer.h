#ifndef I_SOUND_EFFECT_PLAYER_H
#define I_SOUND_EFFECT_PLAYER_H

#include "SoundEffect.h"

class ISoundEffectPlayer {
   public:
    virtual ~ISoundEffectPlayer(){};
    virtual void loadSoundEffect(SoundEffect& effect) = 0;
    virtual void play(int id, int channel = -1, int loops = 0, int time = -1) = 0;

   private:
    virtual int getUniqueChannelId() = 0;
};

#endif