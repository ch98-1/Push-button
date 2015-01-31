//Copyright (C) 2015  Corwin Hansen
#include "button.h"//button functions header

void inittextures(void){ //initialise textures
}


void initbuttons(void){//initialise buttons
	setbutton(&button1);
	setbutton(&button2);
}


void button1(void){//button 1.

	SDL_SetRenderDrawColor(renderer,
		0,
		0,
		0,
		255);
	SDL_RenderClear(renderer);
	unsigned long int i = 0;//counter
	srand((unsigned int)(clock() + SDL_GetTicks()));//seed random number generator
	for (i = 0; i < 100000; i++){
		SDL_SetRenderDrawColor(renderer,
			rand() % 255,
			rand() % 255,
			rand() % 255,
			rand() % 255);
		SDL_RenderDrawPoint(renderer, rand() % display.w, rand() % display.h);
	}
	SDL_SetRenderDrawColor(renderer,
		255,
		0,
		0,
		255);
	SDL_Rect rectangle;
	rectangle.w = buttonsize;
	rectangle.h = buttonsize;
	rectangle.x = display.w / 2 - buttonsize / 2;//center
	rectangle.y = display.h / 2 - buttonsize / 2;//center;

	SDL_RenderFillRect(renderer, &rectangle);

	SDL_RenderPresent(renderer);//render what is drawn


	setnext(2);//set new button function


}


void button2(void){//button2 was pressed

	//test
	SDL_SetRenderDrawColor(renderer,
		255,
		255,
		255,
		255);
	SDL_RenderClear(renderer);
	unsigned long int i = 0;//counter
	srand((unsigned int)(clock() + SDL_GetTicks()));//seed random number generator
	for (i = 0; i < 100000; i++){
		SDL_SetRenderDrawColor(renderer,
			rand() % 100,
			rand() % 255,
			rand() % 100,
			rand() % 255);
		SDL_RenderDrawPoint(renderer, rand() % display.w, rand() % display.h);
	}
	SDL_SetRenderDrawColor(renderer,
		0,
		255,
		0,
		255);
	SDL_Rect rectangle;
	rectangle.w = buttonsize;
	rectangle.h = buttonsize;
	rectangle.x = display.w / 2 - buttonsize / 2;//center
	rectangle.y = display.h / 2 - buttonsize / 2;//center;

	SDL_RenderFillRect(renderer, &rectangle);

	SDL_RenderPresent(renderer);//render what is drawn


	setnext(1);
	//end of test
}
