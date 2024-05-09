
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#define ticks_for_frame 1000/60
int main(int argc, char** argv) {

	if (SDL_Init(SDL_INIT_EVERYTHING) <0 ) {
		std::cout << SDL_GetError();
		return -1;
	}
	SDL_Window* ventana = SDL_CreateWindow("Batalla", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1020, 720, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	SDL_Renderer* ctx = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Surface* mapa_surf = IMG_Load("campo.png");
	SDL_Texture* mapa = SDL_CreateTextureFromSurface(ctx, mapa_surf);
	bool run = true;
	int start, end = SDL_GetTicks();
	int delta = 0;
	SDL_Event e;
	while (run)
	{
		start = SDL_GetTicks();
		delta = start - end;
		if (delta > ticks_for_frame) {
			end = start;
			SDL_SetRenderDrawColor(ctx, 55, 55, 55, 255);
			SDL_SetRenderDrawBlendMode(ctx, SDL_BLENDMODE_ADD);
			SDL_RenderClear(ctx);
			SDL_RenderCopy(ctx, mapa, NULL, NULL);
			
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
			default:
				break;
			}
		}
		
	}
	SDL_DestroyWindow(ventana);
	SDL_FreeSurface(mapa_surf);
	SDL_DestroyTexture(mapa);
	SDL_DestroyRenderer(ctx);
	

}