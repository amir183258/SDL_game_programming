#ifndef DOT_DEFINED
#include "Dot.h"
#endif

#ifndef SCREEN_WIDTH
#define LEVEL_WIDTH 1280
#define LEVEL_HEIGHT 960

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#endif

void initDot(Dot *dot) {
	dot->mPosX = 0;
	dot->mPosY = 0;

	dot->mVelX = 0;
	dot->mVelY = 0;
}

void handleEventDot(Dot *dot, SDL_Event *e) {
	if (e->type == SDL_KEYDOWN && e->key.repeat == 0) {
		switch (e->key.keysym.sym) {
			case SDLK_UP:
				dot->mVelY -= DOT_VEL;
				break;
			case SDLK_DOWN:
				dot->mVelY += DOT_VEL;
				break;
			case SDLK_LEFT:
				dot->mVelX -= DOT_VEL;
				break;
			case SDLK_RIGHT:
				dot->mVelX += DOT_VEL;
				break;
		}
	}
	else if (e->type == SDL_KEYUP && e->key.repeat == 0) {
		switch(e->key.keysym.sym) {
			case SDLK_UP:
				dot->mVelY += DOT_VEL;
				break;
			case SDLK_DOWN:
				dot->mVelY -= DOT_VEL;
				break;
			case SDLK_LEFT:
				dot->mVelX += DOT_VEL;
				break;
			case SDLK_RIGHT:
				dot->mVelX -= DOT_VEL;
				break;
		}
	}
}

void moveDot(Dot *dot) {
	dot->mPosX += dot->mVelX;

	if ((dot->mPosX < 0) || (dot->mPosX + DOT_WIDTH > LEVEL_WIDTH))
		dot->mPosX -= dot->mVelX;

	dot->mPosY += dot->mVelY;
	if ((dot->mPosY < 0) || (dot->mPosY + DOT_HEIGHT > LEVEL_HEIGHT))
		dot->mPosY -= dot->mVelY;
}

void renderDot(Dot *dot, LTexture *texture, SDL_Renderer *renderer, int camX, int camY) {
	renderTexture(texture, renderer, 
			dot->mPosX - camX, 
			dot->mPosY - camY,
			NULL, 0,
			NULL, SDL_FLIP_NONE);
}

int getPosXDot(Dot *dot) {
	return dot->mPosX;
}

int getPosYDot(Dot *dot) {
	return dot->mPosY;
}
