

#include "stdafx.h"
#include <SDL.h>
#include <iostream>
#include "SDL_ttf.h"


using namespace std;

int main(int argc, char *argv[])
{
	printf("hello"); 
	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}


	// load font.ttf at size 72 into font
	TTF_Font *font;
	font = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", 72);
	if (!font) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		exit(2);
	}

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	std::string imagePath = "C:\\Users\\loic\\Documents\\Visual Studio 2015\\Projects\\Win32Project1\\hello.bmp";
	SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
	if (bmp == nullptr) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if (tex == nullptr) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	SDL_Rect positionID; 
	positionID.x = 200; 
	positionID.y = 200;
	positionID.w = 300;
	positionID.h = 100;
	
	SDL_Color couleur;
	couleur = { 255, 0, 0};
	SDL_Surface *ttfSur = TTF_RenderText_Blended(font, "Salut les Zér0s !", couleur);
	SDL_Surface *Blanc = TTF_RenderText_Blended(font, "XXXXX", { 130, 0, 120,255 });
	// SDL_Surface *blankSurface = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);
	if (!SDL_BlitSurface(ttfSur, NULL, Blanc, &positionID)) {
		printf("SDL_BlitSurface failed: %s\n", SDL_GetError());
		
	}
	SDL_Texture *ttftext = SDL_CreateTextureFromSurface(ren, Blanc);
	//A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
	for (int i = 0; i < 3; ++i) {
		//First clear the renderer
		SDL_RenderClear(ren);
		//Draw the texture
		SDL_RenderCopy(ren, tex, NULL, NULL);
		// Draw the text
		SDL_RenderCopy(ren, ttftext, NULL, NULL);
		//Update the screen
		SDL_RenderPresent(ren);
		//Take a quick break after all that hard work
		SDL_Delay(1000);
	}

	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}