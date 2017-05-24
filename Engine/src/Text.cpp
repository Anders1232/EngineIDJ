#include "Text.h"

Text::Text( string fontFile,
			int fontSize,
			TextStyle style,
			SDL_Color color,
			int x,
			int y )
	  : font(Resources::GetFont(fontFile, fontSize)),
		texture(nullptr),
		text(" "),
		style(style),
		fontSize(fontSize),
		color(color),
		fontFile(fontFile){
	box.x= x;
	box.y= y;
	RemakeTexture();
}

Text::~Text() {
	if(nullptr != texture) {
		SDL_DestroyTexture(texture);
	}
}

void Text::Render(int cameraX, int cameraY) const {
	SDL_Rect srcRect;
	srcRect.x= 0;
	srcRect.y= 0;
	srcRect.w= box.w;
	srcRect.h= box.h;
	SDL_Rect destRect= (SDL_Rect)(box- Vec2(cameraX, cameraY));
//	std::cout << WHERE << " srcRect.x=" << srcRect.x<< " srcRect.y=" << srcRect.y<< " srcRect.w=" << srcRect.w<< " srcRect.h=" << srcRect.h << "\n";
//	std::cout << WHERE << " destRect.x=" << destRect.x<< " destRect.y=" << destRect.y<< " destRect.w=" << destRect.w<< " destRect.h=" << destRect.h << "\n";
	if(0 !=SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &srcRect, &destRect) ) {
		Error("Render error: " << SDL_GetError());
	}
}

void Text::SetPos(int x, int y, bool centerX, bool centerY) {
	Vec2 center= Game::GetInstance().GetWindowDimensions();
	if(centerX) {
		box.x= (center.x-box.w)*0.5;
	}
	else {
		box.x= x;
	}
	if(centerY) {
		box.y= (center.y-box.h)*0.5;
	}
	else {
		box.y= y;
	}
}

void Text::SetText(string text) {
	this->text= text;
	RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
	this->color= color;
	RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
	this->style= style;
	RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
	this->fontSize= fontSize;
	RemakeTexture();
}

void Text::RemakeTexture(void) {
	if(nullptr != texture) {
		SDL_DestroyTexture(texture);
	}
	font = Resources::GetFont(fontFile, fontSize);
	SDL_Surface *temp;
	if(SOLID == style) {
		temp= TTF_RenderText_Solid(font.get(), text.c_str(), color);
	}
	else if(SHARED == style) {
		SDL_Color bgColor;
		bgColor= {0, 0, 0, 0};//preto
		temp= TTF_RenderText_Shaded(font.get(), text.c_str(), color, bgColor);
	}
	else if(BLENDED ==  style) {
		temp = TTF_RenderText_Blended(font.get(), text.c_str(), color);
	}
	texture= SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), temp);
	SDL_FreeSurface(temp);
	SDL_QueryTexture(texture, nullptr, nullptr, (int*)&box.w, (int*)&box.h);
	box.w= *((int*)&box.w);
	box.h= *((int*)&box.h);
}

Vec2 Text::GetSize(void)const {
	return Vec2(box.w, box.h);
}

