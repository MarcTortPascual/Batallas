#include "Boton.h"
#define default(x) this->x = x;
Boton::Boton(int x,int  y,int gapX,int gapY, SDL_Color* color, SDL_Color* colortext)
{
	default(x)
	default(y)
	default(color)
	default(colortext)
	default(gapX)
	default(gapY)
	*(this->box) = { 0,0,0,0 };
}

void Boton::getGap(int* gapX, int* gapY)
{
	*(gapX) = this->gapX;
	*(gapY) = this->gapY;
}

void Boton::setGap(int gapX, int gapY)
{
	default(gapX)
	default(gapY)
}

void Boton::getPos(int* x, int* y)
{
	*(x) = this->x;
	*(y) = this->y;
}

void Boton::setPos(int x, int y)
{
	default(x)
	default(y)
}

void Boton::getColor(SDL_Color* color, SDL_Color* colortext)
{
	*(color) = *(this->color);
	*(colortext) = *(this->colortext);
}

void Boton::setColor(SDL_Color* color, SDL_Color* colortext)
{
		default(color)
		default(colortext)
}

bool Boton::hover(int x, int y)
{
	return (x > this->box->x && x < this->box->x + this->box->w) && (y > this->box->y && y < this->box->y + this->box->h);
}


void Boton::render(SDL_Renderer* ctx, TTF_Font* font,SDL_Color * srccolor)
{
	SDL_Surface* txt = TTF_RenderText_Shaded(font, this->text.c_str(), *(this->colortext), *(this->color));
	SDL_Texture* txt_text = SDL_CreateTextureFromSurface(ctx, txt);
	int w, h;
	SDL_QueryTexture(txt_text, NULL, NULL, &w, &h);

	*(this->box) = { this->x,this->y,w + this->gapX,h + this->gapY };
	SDL_SetRenderDrawColor(ctx, this->color->r, this->color->g, this->color->b, this->color->a);
	SDL_RenderFillRect(ctx, this->box);
	SDL_SetRenderDrawColor(ctx, srccolor->r, srccolor->g, srccolor->b, srccolor->a);
	
	SDL_Rect destTxt = { this->x + (this->gapX / 2),this->y + (this->gapY / 2),w + (this->gapX / 2),h + (this->gapY / 2) };
	SDL_FreeSurface(txt);
	SDL_DestroyTexture(txt_text);
}
