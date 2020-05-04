#ifndef SOUND_EFFECT_PLAYER_H
#define SOUND_EFFECT_PLAYER_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <unordered_map>
#include "ISoundEffectPlayer.h"

class SoundEffectPlayer : public ISoundEffectPlayer {
   public:
    SoundEffectPlayer();
    virtual void setVolume(int volume);
    virtual void loadSoundEffect(SoundEffect& effect);
    virtual void play(int id, int channel = -1, int loops = 0, int time = -1);

   private:
    int getUniqueChannelId();
    int mPlayerVolume;
    int mChannelIndex;
    std::unordered_map<int, Mix_Chunk*> storage;
};

#endif