#include <Boton.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <string>
#define default(x) this->x = x;
Boton::Boton(int x,int y,int gapX,int gapY, SDL_Color* color, SDL_Color* colortext,std::string text)
{
	this->text = text;
	this->x = x;
	this->y = y;
	this->color = color;
	this->colortext = colortext;
	this->gapX = gapX;
	this->gapY = gapY;
	this->box->h=0;
	this->box->w=0;
	this->box->x=0;
	this->box->y=0;
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
	return (x > this->box->x && x < this->box->x + this->box->w) && (y > this->box->y && y < this->box->y + this->box->h);
}


void Boton::render(SDL_Renderer* ctx, TTF_Font* font,SDL_Color * srccolor)
{
	SDL_Color bg ={this->color->r,this->color->g,this->color->b,this->color->a};
	SDL_Color fg = {this->colortext->r,this->colortext->g,this->colortext->b,this->colortext->a};
	SDL_Surface* txt = TTF_RenderText_Shaded(font, this->text.c_str(), fg, bg);
	SDL_Texture* txt_text = SDL_CreateTextureFromSurface(ctx, txt);
	int w, h;
	SDL_QueryTexture(txt_text, NULL, NULL, &w, &h);
	SDL_Color aux = {(Uint8) this->x ,(Uint8) this->y,(Uint8)(w + this->gapX),(Uint8)(h + this->gapY) };
	this->color = &aux;
	SDL_SetRenderDrawColor(ctx, this->color->r, this->color->g, this->color->b, this->color->a);
	SDL_RenderFillRect(ctx, this->box);
	SDL_SetRenderDrawColor(ctx, srccolor->r, srccolor->g, srccolor->b, srccolor->a);
	
	SDL_Rect destTxt = { this->x + (this->gapX / 2),this->y + (this->gapY / 2),w + (this->gapX / 2),h + (this->gapY / 2) };
	SDL_RenderCopy(ctx, txt_text, NULL, &destTxt);
	SDL_FreeSurface(txt);
	SDL_DestroyTexture(txt_text);
}
