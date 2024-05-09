#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#pragma once
namespace SDL_OOP {
    class CastBool {
        public:
            static bool toBool(SDL_bool x){
                return x==1?true:false;
            }
            static SDL_bool toSDLBool(bool x){
                return x?SDL_TRUE:SDL_FALSE;
            }
    };
    
}
