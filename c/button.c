//Copyright (C) 2015  Corwin Hansen
#include "button.h"//button functions header

void inittextures(void){ //initialise textures
	gettexture("Pointless_Button.bmp");//pointless button
}


void initbuttons(void){//initialise buttons
	setbutton(&button1);
	setbutton(&button2);
	setbutton(&Pointless);
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

	update();//update and render screen


	if (rand() % 5 == 0){
		setnext(3);
	}
	else{
		setnext(2);
	}


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

	update();//update and render screen

	if (rand() % 5 == 0){
		setnext(3);
	}
	else{
		setnext(1);
	}

	//end of test
}


void Pointless(void){//pointless button




		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);//set sendering color to white
		SDL_RenderClear(renderer);//clear renderer
		int tw;//texture width and height
		int th;
		uint32_t format;//texture format
		int access;//access
		SDL_QueryTexture(textures[2], &format, &access, &tw, &th);//get texture attributes
		SDL_Rect dest;//rectangle for texture
		dest.h = display.h / 4;//1/4 of display height
		dest.w = (int)(dest.h * (double)tw / (double)th);//match texture height
		dest.x = display.w/2 - dest.w/2;//1/4 of display
		dest.y = display.h/16;//1/16 of display
		SDL_RenderCopy(renderer, textures[2], NULL, &dest);//draw button
		update();//update and render screen

		srand((unsigned int)(clock() + SDL_GetTicks()));//seed random number generator
		if (rand() % 50 == 0){//one in 50 changce of escaping the loop by breaking the button
			setnext(rand() % buttonssize / sizeof(buttonfunction));//set new button function to any of possible buttons
		}
		else{
			setnext(3);//this button
		}
		


	}