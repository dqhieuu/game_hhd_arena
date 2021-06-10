set INPUT= .\src\Vector2D.cpp   .\src\utils.cpp   .\src\SoundEffect.cpp   .\src\SoundEffectPlayer.cpp   .\src\MusicPlayer.cpp   .\src\Renderer.cpp   .\src\Locator.cpp   .\src\Timer.cpp   .\src\Texture.cpp   .\src\Sprite.cpp   .\src\JumpingState.cpp   .\src\StandingState.cpp   .\src\WallSlidingState.cpp   .\src\DoNothingState.cpp .\src\KhaBanhState.cpp  .\src\RangedAttackingState.cpp   .\src\MeleeAttackingState.cpp   .\src\Bullet.cpp .\src\StageResult.cpp  .\src\Character.cpp   .\src\Game.cpp   .\src\Intro.cpp   .\src\MainMenu.cpp   .\src\CharacterSelectionScreen.cpp   .\src\Stage1.cpp   .\src\main.cpp 
set OUTPUT=.\bin\release\HHD_Arena.exe .\src\meta\my.res
set COMPILER_FLAGS=-std=c++11
set LINKER_FLAGS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
set INCLUDE_DIR=-I .\libs\SDL2-2.0.12\i686-w64-mingw32\include\SDL2 -I .\libs\SDL2_image-2.0.5\i686-w64-mingw32\include\SDL2 -I .\libs\SDL2_mixer-2.0.4\i686-w64-mingw32\include\SDL2 -I .\libs\SDL2_ttf-2.0.15\i686-w64-mingw32\include\SDL2
set LIB_DIR=-L .\libs\SDL2-2.0.12\i686-w64-mingw32\lib -L .\libs\SDL2_image-2.0.5\i686-w64-mingw32\lib  -L .\libs\SDL2_mixer-2.0.4\i686-w64-mingw32\lib -L .\libs\SDL2_ttf-2.0.15\i686-w64-mingw32\lib -I .\libs\cereal\include
set NO_CONSOLE=-Wl,-subsystem,windows

robocopy .\libs\dlls .\bin\debug
robocopy .\src\assets .\bin\debug\assets /e
robocopy .\libs\dlls .\bin\release
robocopy .\src\assets .\bin\release\assets /e
g++ %COMPILER_FLAGS% %INPUT% %INCLUDE_DIR% %LIB_DIR% %LINKER_FLAGS% %NO_CONSOLE% -o %OUTPUT%