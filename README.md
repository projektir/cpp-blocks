# cpp-blocks

To build via VC++:

clone the `libSDL2pp` repo: https://github.com/libSDL2pp

Place the repo in a folder named `extlib/libSDL2pp` at the root of the project

`cmake .. -G "Visual Studio 15 2017 Win64" -DSDL2PP_WITH_TTF=OFF -DSDL2PP_WITH_MIXER=OFF -DCMAKE_PREFIX_PATH="<your_sdl2_location>;<your_sdl2_image_location>"`

`MSBuild cpp-blocks.sln`
