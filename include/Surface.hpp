#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_syswm.h>
#include <cstddef>
#pragma once
namespace SDL_OOP{
	class Surface {
	private:
		SDL_Surface* surface;
		void* pixels = NULL;
	public:
		Surface(int width, int height, int depth,Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) {
			this->surface = SDL_CreateRGBSurface(0, width, height, depth, Rmask, Gmask, Bmask, Amask);
			
		}
		Surface(void* pixels, int width, int height, int depth, int pitch, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) {
			this->surface = SDL_CreateRGBSurfaceFrom(pixels,width,height,depth,pitch,Rmask,Gmask,Bmask,Amask);
			
		}
		Surface(Uint32 flags, int width,int height, int depth,Uint32 format) {
			this->surface = SDL_CreateRGBSurfaceWithFormat(flags,width,height,depth,format);
			
		}
		Surface(void* pixels, int width, int height, int depth, int pitch, Uint32 format) {
			this->surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels,width,height,depth,pitch, format);
			
		}
		Surface(SDL_Surface* surface) { this->surface = surface; }
		~Surface() { SDL_FreeSurface(this->surface);}
		SDL_Surface* GetRaw() {
			 return this->surface;
		}
		int Lock() {
			this->pixels = this->surface->pixels;
			return SDL_LockSurface(this->surface);
		}
		void UnLock() {
			this->pixels = NULL;
			SDL_UnlockSurface(this->surface);
		}
		void* Getpixels() {
			if (this->pixels != NULL) {
				return this->pixels;
			}
			else {
				return NULL;
				SDL_SetError("Not loked Surface!! use Lock()");
			}
		}
		void GetDimensions(int* w, int* h,int* pitch) {
			*(w) = this->surface->w;
			*(h) = this->surface->h;
			*(pitch) = this->surface->pitch;
		}
		void Setpixels(void* pixels) {
			this->surface->pixels = pixels;
		}
		void blit(Surface dest,SDL_Rect *src = NULL,SDL_Rect *dst = NULL ){
			SDL_BlitSurface(this->surface,src,dest.GetRaw(),dst);
		}
		
};
}
