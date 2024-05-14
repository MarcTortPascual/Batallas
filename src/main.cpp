
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <Personaje.hpp>
#include <Magias.hpp>
#include <Enemigo.hpp>
#include<vector>
#define ticks_for_frame 1000/60

int main(int argc, char** argv) {
	TTF_Init();
	TTF_Font * font = TTF_OpenFont("calibri.ttf", 64);
	string nombres [] = {"Antonio","Ana","Maria","Jose","Luis","Óscar"};
	bool combate = false;
	srand(time(NULL));
	if (SDL_Init(SDL_INIT_EVERYTHING) <0 ) {
		std::cout << SDL_GetError();
		return -1;
	}
	SDL_Window* ventana = SDL_CreateWindow("Batalla", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1020, 720, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	SDL_Renderer* ctx = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_Surface* personaje_surf = IMG_Load("personaje.png");
	SDL_Texture* personaje_text = SDL_CreateTextureFromSurface(ctx, personaje_surf);

	SDL_Surface* enemigo_surf = IMG_Load("enemigo.png");
	SDL_Texture* enemigo_text = SDL_CreateTextureFromSurface(ctx, enemigo_surf);

	SDL_Surface* boss_surf = IMG_Load("boss.png");
	SDL_Texture* boss_text = SDL_CreateTextureFromSurface(ctx, boss_surf);

	SDL_Surface* mapa_surf = IMG_Load("campo.png");
	SDL_Texture* mapa = SDL_CreateTextureFromSurface(ctx, mapa_surf);
	bool run = true;
	int start, end = SDL_GetTicks();
	int delta = 0;
	SDL_Event e;
	int mapaa[100];
	memset(mapaa, NULL, sizeof(int) * 100);
	int ww, wh = 0;
	int x, y;
	Personaje marc = Personaje("Marc", 10, 20);
	vector<Personaje> enemigos;
	int num;
	for (int i = 1; i < 9; i++) {
		num = rand() % 5;
		Personaje  enemigo = Personaje(nombres[num], 1, 10);
		enemigo.setPos(rand() % 9, i);
		enemigo.getPos(&x, &y);
		mapaa[10 * y + x] = 1;
		enemigos.push_back(enemigo);
		
	}

	marc.setPos(0, 0);
	
	while (run)
	{
		SDL_GetWindowSizeInPixels(ventana, &ww, &wh);
		start = SDL_GetTicks();
		delta = start - end;
		if (delta > ticks_for_frame) {
			end = start;
			SDL_SetRenderDrawColor(ctx, 55, 55, 55, 255);
			SDL_SetRenderDrawBlendMode(ctx, SDL_BLENDMODE_BLEND);
			SDL_RenderClear(ctx);
			if (!combate) {
				for (int y = 0; y < 10; y++) {
					for (int x = 0; x < 10; x++) {
						SDL_Rect dest = { x * (ww / 10),y * (wh / 10),(ww / 10),(wh / 10) };
						SDL_RenderCopy(ctx, mapa, NULL, &dest);
					}
				}
				marc.getPos(&x, &y);
				SDL_Rect destpe = { x * (ww / 10),y * (wh / 10),(ww / 10),(wh / 10) };
				SDL_RenderCopy(ctx, personaje_text, NULL, &destpe);
			}
			else {
				Personaje enem = enemigos.at(SDL_clamp(y - 1, 0, enemigos.size() - 1));
				SDL_Rect destpe;
				int w, h;
				if (mapaa[10 * y + x] == 1) {
				
					SDL_SetRenderDrawColor(ctx, 255, 175, 0, 255);
					SDL_Rect info = { 0,0,ww / 2,wh / 2 };
					SDL_RenderFillRect(ctx,&info);
					SDL_SetRenderDrawColor(ctx, 55, 55, 55, 255);
					SDL_Color fg = { 0,0,0,255 };
					SDL_Color bg = { 0, 0, 0, 0 };
					SDL_Surface* text = TTF_RenderText_Shaded(font,marc.getNombre().c_str(), fg, bg);
					SDL_Texture* text_texture = SDL_CreateTextureFromSurface(ctx, text);
					SDL_QueryTexture(text_texture, NULL, NULL, &w, &h);
					SDL_Rect dest = { 0,0,w,h };
					SDL_RenderCopy(ctx, text_texture, NULL, &dest);
					SDL_FreeSurface(text);
					SDL_DestroyTexture(text_texture);
				}
				
					
				
			}
			if (mapaa[10 * y + x] != 0) {
				combate = true;
			}
			else {
				combate = false;
			}
			
			
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
	SDL_FreeSurface(boss_surf);
	SDL_DestroyTexture(boss_text);
	SDL_FreeSurface(enemigo_surf);
	SDL_DestroyTexture(enemigo_text);
	SDL_DestroyRenderer(ctx);
	TTF_CloseFont(font);
}