//Copyright (C) 2015  Corwin Hansen
#include "button.h"//button functions header

void inittextures(void){ //initialise textures
	gettexture("Pointless_Button.bmp");//pointless button
}


void initbuttons(void){//initialise buttons
	b1 = setbutton(&button1);//button1 and 2
	b2 = setbutton(&button2);
	pl = setbutton(&Pointless);//pointless button that says pointless button
	bh = setbutton(&black_hole);//black hole
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


	if (rand() % 5 == 0){//set to pointless button at 1/5 chance
		setnext(pl);
	}
	else{
		setnext(b2);
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

	if (rand() % 5 == 0){//set to pointless button at 1/5 chances
		setnext(pl);
	}
	else{
		setnext(b1);
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
		if (rand() % POINTLESS_ESCAPE_CHANCE == 0){//one in 50 changce of escaping the loop by breaking the button
			setnext(bh);//set new button function to black hole button
		}
		else{
			setnext(pl);//this button
		}
		


}

	



void black_hole(void){//black hole button
	status = NO_BUTTON;//don't draw button as is
	int i;//counter
	SDL_Rect rect;//rect the size of screen
	rect.h = display.h;
	rect.w = display.w;
	rect.x = 0;
	rect.y = 0;
	for (i = 0; i < 64; i++){//spin 360 degrees. Darken screen each frame
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 16);//set sendering color to white
		SDL_RenderFillRect(renderer, &rect);//draw rectangle
		update();//update screen
		SDL_Delay(3);//wait 3 milliseconds
	}
	for (i = 0; i < 32; i++){//spin 360 degrees. Darken screen each frame
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 32);//set sendering color to white
		SDL_RenderFillRect(renderer, &rect);//draw rectangle
		update();//update screen
		SDL_Delay(1);//wait 1 milliseconds
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);//set rendering color to white
	SDL_RenderClear(renderer);//clear screen
	status = UP;//start drawing button
	update();//update screen
	(*buttons[0])(0);//run starting button
}