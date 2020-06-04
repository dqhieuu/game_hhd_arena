#ifndef SOUND_EFFECT_H
#define SOUND_EFFECT_H

#include <SDL_mixer.h>

struct SoundEffect {
    SoundEffect() {
        id = -1;
        chunk = nullptr;
    }
    SoundEffect(Mix_Chunk* chunk_, int id_) {
        id = id_;
        chunk = chunk_;
    }
    Mix_Chunk* chunk;
    int id;
};

#endif