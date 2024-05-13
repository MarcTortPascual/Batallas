
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Personaje.hpp"
#define ticks_for_frame 1000/60
int main(int argc, char** argv) {
	srand(time(NULL));
	if (SDL_Init(SDL_INIT_EVERYTHING) <0 ) {
		std::cout << SDL_GetError();
		return -1;
	}
	SDL_Window* ventana = SDL_CreateWindow("Batalla", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1020, 720, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	SDL_Renderer* ctx = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Surface* personaje_surf = IMG_Load("personaje.png");
	SDL_Texture* personaje_text = SDL_CreateTextureFromSurface(ctx, personaje_surf);
	SDL_Surface* mapa_surf = IMG_Load("campo.png");
	SDL_Texture* mapa = SDL_CreateTextureFromSurface(ctx, mapa_surf);
	bool run = true;
	int start, end = SDL_GetTicks();
	int delta = 0;
	SDL_Event e;
	int mapaa[100];
	memset(mapaa, 0, sizeof(int) * 100);
	int ww, wh = 0;
	int x, y;
	Personaje marc = Personaje("Marc", 10, 20);
	marc.setPos(0, 0);
	
	while (run)
	{
		SDL_GetWindowSizeInPixels(ventana, &ww, &wh);
		start = SDL_GetTicks();
		delta = start - end;
		if (delta > ticks_for_frame) {
			end = start;
			SDL_SetRenderDrawColor(ctx, 55, 55, 55, 255);
			SDL_SetRenderDrawBlendMode(ctx, SDL_BLENDMODE_ADD);
			SDL_RenderClear(ctx);
			for (int y = 0; y < 10; y++) {
				for (int x = 0; x < 10; x++) {
					SDL_Rect dest = { x * (ww / 10),y * (wh / 10),(ww/10),(wh/10)};
					SDL_RenderCopy(ctx, mapa, NULL, &dest);
				}
			}
			
			marc.getPos(&x, &y);
			SDL_Rect destpe = { x * (ww / 10),y * (wh / 10),(ww / 10),(wh / 10) };
			SDL_RenderCopy(ctx, personaje_text, NULL, &destpe);
			SDL_RenderPresent(ctx);
		}
		else {
			SDL_Delay(floor(ticks_for_frame - delta));
		}
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				run = false;
				break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_w:
					marc.getPos(&x, &y);
					y--;
					marc.setPos(SDL_clamp(x,0,9), SDL_clamp(y, 0, 9));
					break;
				case SDLK_s:
					marc.getPos(&x, &y);
					y++;
					marc.setPos(SDL_clamp(x, 0, 9), SDL_clamp(y, 0, 9));
					break;
				case SDLK_d:
					marc.getPos(&x, &y);
					x++;
					marc.setPos(SDL_clamp(x, 0, 9), SDL_clamp(y, 0, 9));
					break;
				case SDLK_a:
					marc.getPos(&x, &y);
					x--;
					marc.setPos(SDL_clamp(x, 0, 9), SDL_clamp(y, 0, 9));
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
		
	}
	SDL_DestroyWindow(ventana);
	SDL_FreeSurface(mapa_surf);
	SDL_DestroyTexture(mapa);
	SDL_FreeSurface(personaje_surf);
	SDL_DestroyTexture(personaje_text);
	SDL_DestroyRenderer(ctx);
	

}