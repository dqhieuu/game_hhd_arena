#include <SDL.h>
#include <SDL_mixer.h>

#include <iostream>
#include <string>

#include "IMusicPlayer.h"
#include "MusicPlayer.h"

MusicPlayer::MusicPlayer() {
    mIsPlaying = false;
    mMusic = nullptr;
}
void MusicPlayer::free() {
    if (mMusic != nullptr) {
        Mix_FreeMusic(mMusic);
        mMusic = nullptr;
        mIsPlaying = false;
    }
}
MusicPlayer::~MusicPlayer() {
    free();
}
void MusicPlayer::load(std::string path) {
    // Deallocate preexisting music
    free();

    mMusic = Mix_LoadMUS(path.c_str());
    if (mMusic == nullptr)
        std::cout << "Error: Music not found, Mix_LoadMUS: " << Mix_GetError() << "\n";
}
void MusicPlayer::setVolume(int volume) {
    Mix_VolumeMusic(volume);
}
void MusicPlayer::play(int fadeInTicks) {
    if (mMusic != nullptr) {
        if (fadeInTicks != 0) {
            Mix_FadeInMusic(mMusic, -1, fadeInTicks);
        } else
            Mix_PlayMusic(mMusic, -1);
        mIsPlaying = true;
    }
}
void MusicPlayer::stop(int fadeOutTicks) {
    if (mMusic != nullptr && mIsPlaying) {
        if (fadeOutTicks != 0) {
            Mix_FadeOutMusic(fadeOutTicks);
        } else
            Mix_HaltMusic();
        mIsPlaying = false;
    }
}