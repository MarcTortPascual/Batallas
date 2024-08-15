#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <Personaje.hpp>
#include <Magias.hpp>
#include <Enemigo.hpp>
#include <vector>
#include <Boton.h>
#include <string>
#define ticks_for_frame 1000/60
int main(int argc, char** argv) {
	TTF_Init();
	TTF_Font * font = TTF_OpenFont("calibri.ttf", 64);
	std::string nombres [] = {"Antonio","Ana","Maria","Jose","Luis","Oscar","Pedro","Daniel"};
	bool combate = false;
	srand(time(NULL));
	if (SDL_Init(SDL_INIT_EVERYTHING) <0 ) {
		std::cout << SDL_GetError();
		return -1;
	}
	bool gameover = false;
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

	SDL_Surface* estados_surf = IMG_Load("estados.png");
	SDL_Texture* estados = SDL_CreateTextureFromSurface(ctx, estados_surf);

	bool run = true;
	int start, end = SDL_GetTicks();
	int delta = 0;
	SDL_Event e;
	int mapaa[100];
	memset(mapaa, 0, sizeof(int) * 100);
	int ww, wh = 0;
	int x, y;
	int mx = 0;
	int my = 0;
	SDL_Color  color = {0,0,0,0};
	Boton atacar = Boton(0,0,26,26,&color,&color,"ATACAR!!!",&e);
	Personaje marc = Personaje("Marc", 10, 25);
	EnemigoFinal boss = EnemigoFinal("Campeon", 5, 100);
	vector<Personaje> enemigos;
	int num;
	for (int i = 1; i < 9; i++) {
		num = rand() % 7;
		Personaje  enemigo = Personaje(nombres[num], 3, 30);
		enemigo.setPos(rand() % 9, i);
		enemigo.getPos(&x, &y);
		mapaa[10 * y + x] = 1;
		enemigos.push_back(enemigo);
		
	}
	boss.setPos(rand() % 9, 9);
	boss.getPos(&x, &y);
	mapaa[10 * y + x] = 2;
	
	marc.setPos(0, 0);
	string gameovertext = "GAMEOVER";
	while (run)
	{
		SDL_GetWindowSizeInPixels(ventana, &ww, &wh);
		start = SDL_GetTicks();
		delta = start - end;
		if (delta > ticks_for_frame) {
			if (gameover) {
				TTF_SetFontSize(font, 1024);
				SDL_Surface* final = TTF_RenderText_Shaded(font, gameovertext.c_str(), { 255,255,0,255 }, { 0,0,0,1 });
				
				SDL_Texture* text_final = SDL_CreateTextureFromSurface(ctx, final);
				SDL_RenderClear(ctx);
				SDL_Rect rec = { 0,0,ww,wh };
				SDL_RenderCopy(ctx, text_final, NULL, &rec);
				SDL_RenderPresent(ctx);
				while (SDL_PollEvent(&e))
				{
					atacar.set_evento(&e);
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
			else {
				end = start;
				SDL_SetRenderDrawColor(ctx, 55, 55, 55, 255);
				SDL_SetRenderDrawBlendMode(ctx, SDL_BLENDMODE_BLEND);
				SDL_RenderClear(ctx);
				Personaje* enem = &enemigos.at(SDL_clamp(y - 1, 0, enemigos.size() - 1));
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
					
					SDL_Color source = { 55, 55, 55, 255 };
					if (atacar.Is_hover()) {
						SDL_Color text = { 0,0,0,255 };
						SDL_Color bot = { 155,155,0,255 };
						atacar.setColor(&bot, &text);
					}
					else {
						SDL_Color bot = { 155,155,155,255 };
						SDL_Color botcol = { 255,255,255,255 };

						atacar.setPos(0, wh / 4 * 3);
						atacar.setColor(&bot, &botcol);

					}


					int w, h;


					SDL_SetRenderDrawColor(ctx, 255, 175, 0, 255);
					SDL_Rect info = { 0,0,ww / 2,wh / 2 };
					SDL_RenderFillRect(ctx, &info);

					SDL_SetRenderDrawColor(ctx, 255, 125, 0, 255);
					info = { ww / 2,wh / 2,ww / 2,wh / 2 };
					SDL_RenderFillRect(ctx, &info);

					SDL_SetRenderDrawColor(ctx, 55, 55, 55, 255);
					SDL_Color fg = { 0,0,0,255 };
					SDL_Color bg = { 255,255, 255, 1 };

					SDL_Surface* text = TTF_RenderText_Shaded(font, marc.getNombre().c_str(), fg, bg);
					SDL_Texture* text_texture = SDL_CreateTextureFromSurface(ctx, text);

					SDL_Surface* textene = TTF_RenderText_Shaded(font, enem->getNombre().c_str(), fg, bg);
					SDL_Texture* text_texturene = SDL_CreateTextureFromSurface(ctx, textene);
					SDL_Surface* textene2 = TTF_RenderText_Shaded(font, to_string(boss.getHechizos()).c_str(), fg, bg);
					SDL_Texture* text2 = SDL_CreateTextureFromSurface(ctx, textene2);
					if (mapaa[10 * y + x] == 1) {
						textene = TTF_RenderText_Shaded(font, enem->getNombre().c_str(), fg, bg);
						text_texturene = SDL_CreateTextureFromSurface(ctx, textene);
					}
					else if (mapaa[10 * y + x] == 2) {
						textene = TTF_RenderText_Shaded(font, boss.getNombre().c_str(), fg, bg);
						textene2 = TTF_RenderText_Shaded(font, to_string(boss.getHechizos()).c_str(), fg, bg);
						text_texturene = SDL_CreateTextureFromSurface(ctx, textene);
						text2 = SDL_CreateTextureFromSurface(ctx, textene2);
					}


					SDL_QueryTexture(text_texture, NULL, NULL, &w, &h);
					int steplife = (ww / 2) / marc.getMaxVida();
					int enesteplife = 0;
					if (mapaa[10 * y + x] == 1) {
						enesteplife = (ww / 2) / enem->getMaxVida();
					}
					else if (mapaa[10 * y + x] == 2) {
						enesteplife = (ww / 2) / boss.getMaxVida();
					}
					SDL_SetRenderDrawColor(ctx, 55, 55, 55, 255);
					info = { 0,70,ww / 2,10 };
					SDL_RenderFillRect(ctx, &info);

					info = { ww / 2,(wh / 2) + 70,ww / 2,10 };
					SDL_RenderFillRect(ctx, &info);

					SDL_SetRenderDrawColor(ctx, 0, 255, 0, 255);
					info = { 0,70,marc.getVida() * steplife,10 };
					SDL_RenderFillRect(ctx, &info);
					if (mapaa[10 * y + x] == 1) {

						info = { ww / 2,(wh / 2) + 70,enem->getVida() * enesteplife,10 };
					}
					else if (mapaa[10 * y + x] == 2) {
						info = { ww / 2,(wh / 2) + 70,boss.getVida() * enesteplife,10 };
					}

					SDL_RenderFillRect(ctx, &info);
					SDL_Rect dest = { 0,0,w,h };
					SDL_RenderCopy(ctx, text_texture, NULL, &dest);
					SDL_QueryTexture(text_texturene, NULL, NULL, &w, &h);
					dest = { ww / 2,wh / 2,w,h };
					SDL_RenderCopy(ctx, text_texturene, NULL, &dest);
					dest = { ww / 4 - ((ww / 4) / 2),wh / 8,ww / 4,wh / 3 };
					SDL_RenderCopy(ctx, personaje_text, NULL, &dest);
					dest = { (ww / 2) + ww / 4 - ((ww / 4) / 2),wh / 8 + (wh / 2),ww / 4,wh / 3 };
					if (mapaa[10 * y + x] == 1) {
						SDL_RenderCopy(ctx, enemigo_text, NULL, &dest);
					}
					else if (mapaa[10 * y + x] == 2) {
						SDL_RenderCopy(ctx, boss_text, NULL, &dest);
						dest = { (ww / 2) + ww / 16,wh / 8 + (wh / 2)+16,ww / 10,wh / 6 };
						SDL_RenderCopy(ctx, text2, NULL, &dest);
					}

					atacar.render(ctx, font, &source);
					SDL_Rect estpost = { 10,100,32,32 };
					SDL_Rect estsrc = { marc.getEstado() * 16,0,16,16 };
					SDL_RenderCopy(ctx, estados, &estsrc, &estpost);
					SDL_FreeSurface(textene2);
					SDL_DestroyTexture(text2);
					SDL_FreeSurface(text);
					SDL_DestroyTexture(text_texture);
					SDL_FreeSurface(textene);
					SDL_DestroyTexture(text_texturene);
					SDL_SetRenderDrawColor(ctx, 55, 55, 55, 255);




				}
				if (mapaa[10 * y + x] != 0) {
					combate = true;
				}
				else {
					combate = false;
				}

				if (atacar.Is_clicked()){
					int x, y;
					marc.getPos(&x, &y);
					if (mapaa[10 * y + x] == 1) {
						if (marc.getVida() >=  0 && enem->getVida() > 0) {
							marc.atacar(enem);
							enem->atacar(&marc);
						}
						else {
							if (enem->getVida() <= 0) {
								mapaa[10 * y + x] = 0;
							}
							if (marc.getVida() <= 0) {
								gameover = true;

							}
							combate = false;
						}
					}
					else if(mapaa[10 * y + x] == 2) {
						if (marc.getVida() > 0 && boss.getVida() > 0) {
							if (marc.getEstado() != CONFUSO && marc.getEstado() != PARALIZADO){
								marc.atacar(&boss);
							}
										
							int mov = rand() % 101;
							if (boss.getHechizos() > 0){
								if (mov <= 18) {
									int mov2 = 1 + rand() %3;
									boss.hechizar(mov2,marc);
								}
								else {
									enem->atacar(&marc);			
								}
							}
							else{
								boss.atacar(&marc);
							}
						}
						else {
							mapaa[10 * y + x] = 0;
							if (boss.getVida() <= 0) {
							
								gameovertext = "victoria";
								gameover = true;
							}
							if (marc.getVida() <= 0) {
								gameover = true;

							}
							combate = false;
						}
					}
				}
				
				while (SDL_PollEvent(&e))
				{
					atacar.set_evento(&e);
					switch (e.type)
					{
					case SDL_QUIT:
						run = false;
						break;
					case SDL_KEYDOWN:
						switch (e.key.keysym.sym)
						{
						case SDLK_w:
							if (!combate) {
								marc.getPos(&x, &y);
								y--;
								marc.setPos(SDL_clamp(x, 0, 9), SDL_clamp(y, 0, 9));
							}

							break;
						case SDLK_s:
							if (!combate) {
								marc.getPos(&x, &y);
								y++;
								marc.setPos(SDL_clamp(x, 0, 9), SDL_clamp(y, 0, 9));
							}
							break;
						case SDLK_d:
							if (!combate) {
								marc.getPos(&x, &y);
								x++;
								marc.setPos(SDL_clamp(x, 0, 9), SDL_clamp(y, 0, 9));
							}
							break;
						case SDLK_a:
							if (!combate) {
								marc.getPos(&x, &y);
								x--;
								marc.setPos(SDL_clamp(x, 0, 9), SDL_clamp(y, 0, 9));
							}
							break;
						default:
							break;
						}
					case SDL_MOUSEMOTION:
						mx = e.motion.x;
						my = e.motion.y;

						break;
					default:
						break;
					}
				}
			}
			SDL_RenderPresent(ctx);
		}
		else {
			SDL_Delay(floor(ticks_for_frame - delta));
		}
		
		
	}
	SDL_FreeSurface(estados_surf);
	SDL_DestroyTexture(estados);
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
