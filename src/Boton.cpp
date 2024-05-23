#include <Boton.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <string>
#include <iostream>
#define default(x) this->x = x;
Boton::Boton(int x,int y,int gapX,int gapY, SDL_Color* color, SDL_Color* colortext,std::string text)
{
	this->text = text;
	this->x = x;
	this->y = y;
	this->w = 0;
	this->h = 0;
	this->color = color;
	this->colortext = colortext;
	this->gapX = gapX;
	this->gapY = gapY;
	SDL_Rect col = { x,y,10,10 };
	this->box = &col;
}

void Boton::getGap(int* gapX, int* gapY)
{
	*(gapX) = this->gapX;
	*(gapY) = this->gapY;
}

void Boton::setGap(int gapX, int gapY)
{
	this->gapX=gapX;
	this->gapY=gapY;
}

void Boton::getPos(int* x, int* y)
{
	*(x) = this->x;
	*(y) = this->y;
}

void Boton::setPos(int x, int y)
{
	this->x=x;
	this->y=y;
	this->box->x = x;
	this->box->y = y;
}

void Boton::getColor(SDL_Color* color, SDL_Color* colortext)
{
	*(color) = *(this->color);
	*(colortext) = *(this->colortext);
}

void Boton::setColor(SDL_Color* color, SDL_Color* colortext)
{
		this->color =color;
		this->colortext = colortext;
}

bool Boton::hover(int x, int y)
{
	return (x > this->x && x < this->x + (this->w + this->gapX)) && (y > this->y && y < this->y + (this->h + this->gapY));
}


void Boton::render(SDL_Renderer* ctx, TTF_Font* font,SDL_Color * srccolor)
{
	
	SDL_Color bg ={this->color->r,this->color->g,this->color->b,1};
	SDL_Color fg = {this->colortext->r,this->colortext->g,this->colortext->b,this->colortext->a};
	SDL_Surface* txt = TTF_RenderText_Shaded(font, this->text.c_str(), fg, bg);
	SDL_Texture* txt_text = SDL_CreateTextureFromSurface(ctx, txt);
	int w, h;
	SDL_QueryTexture(txt_text, NULL, NULL, &w, &h);
	this->w = w;
	this->h = h;
	SDL_Rect aux = { this->x ,this->y,w + (this->gapX * 2),h + (this->gapY*2) };

	SDL_SetRenderDrawColor(ctx, this->color->r, this->color->g, this->color->b, this->color->a);
	SDL_RenderFillRect(ctx, &aux);
	SDL_SetRenderDrawColor(ctx, srccolor->r, srccolor->g, srccolor->b, srccolor->a);
	
	SDL_Rect destTxt = { this->x + (this->gapX / 2),this->y + (this->gapY / 2),w + this->gapX,h + this->gapY };
	SDL_RenderCopy(ctx, txt_text, NULL, &destTxt);
	SDL_FreeSurface(txt);
	SDL_DestroyTexture(txt_text);
}
