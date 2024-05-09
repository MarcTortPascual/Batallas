
#include <SDL2/SDL.h>
#include "Window.hpp"
#pragma once

namespace SDL_OOP{
	
	class Texture {
		private:
			SDL_Texture* texture;
			void** pixels = NULL;
			int pitch;
		public:
			Texture(Renderer renderer ,int w,int h, Uint32 format = SDL_PIXELFORMAT_RGBA32, int access = SDL_TEXTUREACCESS_STREAMING) {
			
				this->texture = SDL_CreateTexture(renderer.GetRaw(), format, access, w, h);
			}
		
			Texture(SDL_Texture* texture) { this->texture = texture; }
			~Texture() { SDL_DestroyTexture(this->texture);}
			SDL_Texture* GetRaw() {
				return this->texture;
			}	
			int Lock(SDL_Rect *rect) {
				if (this->GetAccess() == SDL_TEXTUREACCESS_STREAMING) {
					SDL_LockTexture(this->texture, rect, this->pixels, &this->pitch);
					return 1;
				}
				else {
					return 0;
				}
			}
			void UnLock() {
				SDL_UnlockTexture(this->texture);
			}
			void* Getpixels() {
				return this->pixels;
			}
		
			void GetDimensions(int* w, int* h) {
				SDL_QueryTexture(this->texture, NULL, NULL, w, h);
			}
			int GetAccess(){
				int a;
				SDL_QueryTexture(this->texture, NULL, &a, NULL, NULL);
				return a;
			}
			Uint32 GetFormat(){
				Uint32 format;
				SDL_QueryTexture(this->texture, &format, NULL, NULL, NULL);
				return format;

			}
			void Setpixels(void** pixels) {
				this->pixels = pixels;
			}
	};
	class Renderer {
	private:
		SDL_Renderer* renderer;
	public:
		Renderer(Window window, int index, Uint32 flags) {
			this->renderer = SDL_CreateRenderer(window.Getraw(), index, flags);
		}
		Renderer(Window window, int index, Uint32 flags, SDL_BlendMode blendMode, Uint32 color) {
			this->renderer = SDL_CreateRenderer(window.Getraw(), index, flags);
			SDL_SetRenderDrawBlendMode(this->renderer, blendMode);
			SDL_SetRenderDrawColor(this->renderer, color >> 24 & 0xff, color >> 16 & 0xff, color >> 8 & 0xff, color & 0xff);
		}
		~Renderer() {
			SDL_DestroyRenderer(this->renderer);
		}
		void copy(Texture texture, SDL_Rect* srcrect, SDL_Rect* dtsrect) {
			SDL_RenderCopy(this->renderer, texture.GetRaw(), srcrect, dtsrect);
		}
		void present() {
			SDL_RenderPresent(this->renderer);
		}
		void clear() {
			SDL_RenderClear(this->renderer);
		}
		SDL_Renderer* GetRaw() { return this->renderer; }
	};
}