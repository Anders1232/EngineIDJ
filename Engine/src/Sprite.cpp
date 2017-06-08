#include "Sprite.h"

#include "Camera.h"
#include "Error.h"
#include "Game.h"
#include "Resources.h"

// Alterar esses valores altera a parte da textura que será renderizada
#define SPRITE_OPEN_X (0)
#define SPRITE_OPEN_Y (0)

Sprite::Sprite(void): Sprite("", 0, 1) {}

Sprite::Sprite(std::string file, float frameTime, int frameCount)
		: colorMultiplier(255, 255, 255), blendMode(ALPHA_BLEND)
		, alpha(255), frameCount(frameCount)
		, currentFrame(0), timeElapsed(0)
		, frameTime(frameTime), scaleX(1.), scaleY(1.) {
	REPORT_I_WAS_HERE;
	if(file.empty()) {
		texture = nullptr;
	} else {
		Open(file);
	}
	REPORT_I_WAS_HERE;
}

Sprite::~Sprite() {}

void Sprite::Open(std::string file) {
	REPORT_I_WAS_HERE;
	texture = Resources::GetImage(file);
	REPORT_I_WAS_HERE;
	if(nullptr == texture) {
		Error(SDL_GetError());
	}
	REPORT_I_WAS_HERE;
	// Verificar se houve erro na chamada
	if(SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height)) {
		Error(SDL_GetError());
	}
	REPORT_I_WAS_HERE;
	SetClip(SPRITE_OPEN_X, SPRITE_OPEN_Y, width/frameCount, height);
	REPORT_I_WAS_HERE;
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render(Rect world, float angle, bool isCoordOnWorld) const {
	Game& game = Game::GetInstance();
	
	if( -1 == SDL_SetTextureAlphaMod( texture.get(), alpha ) ) {
		CHECK_SDL_ERROR;
	}
	if( -1 == SDL_SetTextureBlendMode( texture.get(), blendMode ) ) {
		CHECK_SDL_ERROR;
	}
	if( -1 == SDL_SetTextureColorMod( texture.get(), colorMultiplier.r, colorMultiplier.g, colorMultiplier.b ) ) {
		CHECK_SDL_ERROR;
	}

	if(0 >= world.w || 0 >= world.h) {
		world.w = GetWidth();
		world.h = GetHeight();
	}

	if(isCoordOnWorld) {
		world = Camera::WorldToScreen(world);
	}
	SDL_Rect dst = world;
	if(SDL_RenderCopyEx(game.GetRenderer(), texture.get(), &clipRect, &dst, angle, NULL, SDL_FLIP_NONE) ){
		// Verifica se haverá erro
		Error(SDL_GetError());
	}
}

int Sprite::GetHeight(void) const {
	return height*scaleY;
}

int Sprite::GetWidth(void) const {
	return width/frameCount*scaleX;
}

bool Sprite::IsOpen(void) const {
	return (nullptr != texture);
}

/*void Sprite::Rotate(double angle) {
	this->angle= angle;
}
*/
std::shared_ptr<SDL_Texture> Sprite::GetTexture(void) const {
	return texture;
}

void Sprite::SetScaleX(float scale) {
	scaleX = scale;
}

void Sprite::SetScaleY(float scale) {
	scaleY = scale;
}

void Sprite::SetScale(float scale) {
	scaleX = scale;
	scaleY = scale;
}

void Sprite::ScaleX(float scale) {
	scaleX *= scale;
}

void Sprite::ScaleY(float scale) {
	scaleY *= scale;
}

void Sprite::Scale(float scale) {
	scaleX *= scale;
	scaleY *= scale;
}

void Sprite::Update(float dt) {
	timeElapsed += dt;
	if(timeElapsed > frameTime) {
		timeElapsed -= frameTime;
		currentFrame = (currentFrame+1)%frameCount;
		clipRect.x = currentFrame*(width/frameCount);
	}
}

void Sprite::SetFrame(int frame) {
	currentFrame = frame%frameCount;
	int newXRect = currentFrame*(width/frameCount);
	clipRect.x = newXRect;
}

void Sprite::SetFrameCount(int frameCount) {
	this->frameCount = frameCount;
	clipRect.w = width/frameCount;
}
void Sprite::SetFrameTime(float frameTime) {
	this->frameTime=frameTime;
}
