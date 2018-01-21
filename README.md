# cpp-blocks

![blocks](cpp-blocks.png)

To build via VC++:

clone the `libSDL2pp` repo: https://github.com/libSDL2pp/libSDL2pp

Place the repo in a folder named `extlib/libSDL2pp` at the root of the project

A copy of SDL2 in the right format has been provided, but you can get the latest at https://www.libsdl.org/download-2.0.php

`cmake .. -G "Visual Studio 15 2017 Win64" -DSDL2PP_WITH_TTF=OFF -DSDL2PP_WITH_MIXER=OFF -DCMAKE_PREFIX_PATH="<your_sdl2_location>;<your_sdl2_image_location>"`

`MSBuild cpp-blocks.sln`
