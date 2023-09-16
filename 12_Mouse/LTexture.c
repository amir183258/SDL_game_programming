#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "./LTexture.h"

int loadFromFile(LTexture *texture, SDL_Renderer *renderer, char *path) {
	freeTexture(texture);

	SDL_Texture *newTexture = NULL;

	SDL_Surface *loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface); if (newTexture == NULL)
			printf("Unable to create texture %s! SDL Error: %s\n", path, SDL_GetError());
		else {
			texture->mWidth = loadedSurface->w;
			texture->mHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	texture->mTexture = newTexture;
	return texture->mTexture != NULL;
}

void freeTexture(LTexture *texture) {
	if (texture->mTexture != NULL) {
		SDL_DestroyTexture(texture->mTexture);
		texture->mTexture = NULL;
		texture->mWidth = 0;
		texture->mHeight= 0;
	}
}
void renderTexture(LTexture *texture, SDL_Renderer *renderer, int x, int y, SDL_Rect *clip, 
		double angle, SDL_Point* center, SDL_RendererFlip flip) {

	SDL_Rect renderQuad = {x, y, texture->mWidth, texture->mHeight};

	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(renderer, texture->mTexture, clip, &renderQuad, angle, center, flip);
}

int getTextureWidth(LTexture *texture) {
	return texture->mWidth;
}

int getTextureHeight(LTexture *texture) {
	return texture->mHeight;
}

void initTexture(LTexture *texture) {
	texture->mTexture = NULL;
	texture->mWidth = 0;
	texture->mHeight = 0;
}

void setColor(LTexture *texture, Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(texture->mTexture, red, green, blue);
}

void setBlendMode(LTexture *texture, SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(texture->mTexture, blending);
}

void setAlpha(LTexture *texture, Uint8 alpha) {
	SDL_SetTextureAlphaMod(texture->mTexture, alpha);
}

#if defined(SDL_TTF_MAJOR_VERSION)
int loadFromRenderedText(LTexture *texture, SDL_Renderer *renderer, TTF_Font *font, char *textureText, SDL_Color textColor) {
	free(texture);

	SDL_Surface *textSurface = TTF_RenderText_Solid(font, textureText, textColor);
	if (textSurface == NULL)
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	else {
		texture->mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture->mTexture == NULL)
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		else {
			texture->mWidth = textSurface->w;
			texture->mHeight = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}

	return texture->mTexture != NULL;
}
#endif
