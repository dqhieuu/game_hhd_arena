set INPUT=.\src\main.cpp
set OUTPUT=.\bin\release\HHD_Arena.exe
set COMPILER_FLAGS=-std=c++11
set LINKER_FLAGS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
set INCLUDE_DIR=-I .\libs\SDL2-2.0.12\i686-w64-mingw32\include\SDL2 -I .\libs\SDL2_image-2.0.5\i686-w64-mingw32\include\SDL2 -I .\libs\SDL2_mixer-2.0.4\i686-w64-mingw32\include\SDL2
set LIB_DIR=-L .\libs\SDL2-2.0.12\i686-w64-mingw32\lib -L .\libs\SDL2_image-2.0.5\i686-w64-mingw32\lib  -L .\libs\SDL2_mixer-2.0.4\i686-w64-mingw32\lib
set NO_CONSOLE=-Wl,-subsystem,windows

robocopy .\libs\dlls .\bin\debug
robocopy .\src\assets .\bin\debug\assets /e
robocopy .\libs\dlls .\bin\release
robocopy .\src\assets .\bin\release\assets /e
g++ %COMPILER_FLAGS% %INPUT% %INCLUDE_DIR% %LIB_DIR% %LINKER_FLAGS% %NO_CONSOLE% -o %OUTPUT%