#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
class Boton
{
	private:
		int x, y,w,h;
		int gapX, gapY;
		SDL_Rect* box;
		SDL_Color* color;
		SDL_Color* colortext;
		std::string text;
	public:
		Boton(int x, int  y, int gapX, int gapY, SDL_Color* color, SDL_Color* colortext,std::string text);
		void getGap(int* gapX, int* gapY);
		void setGap(int gapX, int gapY);
		void getPos(int* x, int* y);
		void setPos(int x, int y);
		void getColor(SDL_Color* color, SDL_Color* colortext);
		void setColor(SDL_Color* color, SDL_Color* colortext);
		bool hover(int x , int y);
		void render(SDL_Renderer* ctx, TTF_Font* font, SDL_Color* srccolor);
};

