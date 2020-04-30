#ifndef MUSIC_EFFECT_PLAYER_H
#define MUSIC_EFFECT_PLAYER_H

#include <SDL.h>
#include <SDL_mixer.h>
#include "IMusicPlayer.h"

class MusicPlayer : public IMusicPlayer {
   public:
    MusicPlayer();
    virtual ~MusicPlayer();
    virtual void free();
    virtual void load(std::string path);
    virtual void setVolume(int volume);
    virtual void play(int fadeInTicks = 0);
    virtual void stop(int fadeOutTicks = 0);
   private:
    bool mIsPlaying;
    Mix_Music* mMusic;
};
#endif