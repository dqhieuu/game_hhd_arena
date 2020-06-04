#ifndef SETTINGS_H
#define SETTINGS_H

#include <SDL.h>
#include <string>
#include <cereal/archives/json.hpp>
#include <fstream>

enum Degree {
        LOW, MEDIUM, HIGH
};

struct Settings {
    SDL_Scancode buttonUp = SDL_SCANCODE_UP;
    SDL_Scancode buttonDown = SDL_SCANCODE_DOWN;
    SDL_Scancode buttonLeft = SDL_SCANCODE_LEFT;
    SDL_Scancode buttonRight = SDL_SCANCODE_RIGHT;
    SDL_Scancode buttonJump = SDL_SCANCODE_Z;
    SDL_Scancode buttonMelee = SDL_SCANCODE_X;
    SDL_Scancode buttonRanged = SDL_SCANCODE_C;
    SDL_Scancode buttonSpecialMove = SDL_SCANCODE_A;
    int musicVolume = 60;
    int effectsVolume = 40;
    Degree gameQuality = HIGH;
    bool isFullScreen = false;
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive( CEREAL_NVP(buttonUp), CEREAL_NVP(buttonDown), CEREAL_NVP(buttonLeft), CEREAL_NVP(buttonRight), CEREAL_NVP(buttonJump), CEREAL_NVP(buttonMelee), CEREAL_NVP(buttonRanged), CEREAL_NVP(buttonSpecialMove), CEREAL_NVP(musicVolume), CEREAL_NVP(effectsVolume), CEREAL_NVP(gameQuality), CEREAL_NVP(isFullScreen));
    }
};



#endif