#ifndef I_MUSIC_PLAYER_H
#define I_MUSIC_PLAYER_H
#include <string>

class IMusicPlayer {
   public:
    virtual ~IMusicPlayer(){};
    virtual void load(std::string path) = 0;
    virtual void play(int fadeInTicks = 0) = 0;
    virtual void stop(int fadeOutTicks = 0) = 0;
    virtual void setVolume(int volume) = 0;
    virtual void setInternalVolume(int volume) = 0;
};
#endif