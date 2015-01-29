//Copyright (C) 2014-2015  Corwin Hansen
#include "button.h"//function for each buttons
#include "main.h"//main function and data type header. Just in case.


int main(int argc, char *argv[]){

	if (SDL_Init(SDL_INIT_VIDEO) != 0){//start SDL and get any error if it dosen't.
		printf("Could not load SDL: %s", SDL_GetError());//print out error
		exit(EXIT_FAILURE);
	}

	//filter quit event
	SDL_SetEventFilter(EventFilter, NULL);
	//quit SDL at exit
	atexit(SDL_Quit);

	//get desplay mode of the desktop
	if (SDL_GetDesktopDisplayMode(0, &display) != 0) {
		SDL_Log("Could not get display mode: %s", SDL_GetError());//take care of errors
		exit(EXIT_FAILURE);
	}
	if (display.h > display.w) buttonsize = display.w / 4;//quorter of shortest screen size
	else buttonsize = display.h / 4;

	window = SDL_CreateWindow(//create window named CFS_Archtecture that is 320 by 240
		"Push-button",                  // window title
		SDL_WINDOWPOS_CENTERED,           // initial x position
		SDL_WINDOWPOS_CENTERED,           // initial y position
		display.w,                               // width, in pixels
		display.h,                               // height, in pixels
		SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE			// fullscreen window
		);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //create Renderer




	//test
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
	//end of test



	while (SDL_WaitEvent(&e) != 0){//wait for event to happen
		//update desplay mode of the desktop
		if (SDL_GetDesktopDisplayMode(0, &display) != 0) {
			SDL_Log("Could not get display mode: %s", SDL_GetError());//take care of errors
			exit(EXIT_FAILURE);
		}
		if (display.h > display.w) buttonsize = display.w / 4;//quorter of shortest screen size
		else buttonsize = display.h / 4;


		switch (e.type) {
		case SDL_QUIT://quit everything
			SDL_DestroyRenderer(renderer);//destroy renderer
			SDL_DestroyWindow(window);//destro window
			SDL_Quit();//end of running SDL
			exit(EXIT_SUCCESS);//end of program
			return 0;//delete that event
			break;
		case SDL_MOUSEBUTTONDOWN: //clicked
			push(e.button.x, e.button.y);//pushed somewhare on screen.
			break;
		default://do nothing for other events
			break;
		}
	}


	//end of softwhere
	SDL_DestroyRenderer(renderer);//destroy renderer
	SDL_DestroyWindow(window);//destro window
	SDL_Quit();//end of running SDL
	exit(EXIT_SUCCESS);//end of program
}


int EventFilter(void* userdata, SDL_Event* e){//event filter
		switch (e->type) {
		case SDL_QUIT://quit everything
			SDL_DestroyRenderer(renderer);//destroy renderer
			SDL_DestroyWindow(window);//destro window
			SDL_Quit();//end of running SDL
			exit(EXIT_SUCCESS);//end of program
			return 0;//delete that event
			break;
		default://for everything else
			return 1;//don't delete event
			break;
			return 1;//just in case something wiard happens
		}
	}


void push(int x, int y){//check if pressed button or not and call button() if pressed.
	if (sqrt((x - display.w / 2)*(x - display.w / 2) + (y - display.h / 2)*(y - display.h / 2)) < buttonsize / 2){//if you pressed on button
		button();//call button function
	}
	//button was not pressed
}

void button(){//button was pressed


	//test
	SDL_SetRenderDrawColor(renderer,
		0,
		0,
		0,
		255);
	SDL_RenderClear(renderer);
	unsigned long int i = 0;//counter
	srand(SDL_GetTicks()%100000);
	for (i = 0; i < 100000; i++){
		SDL_SetRenderDrawColor(renderer,
			rand(),
			rand(),
			rand(),
			rand());
		SDL_RenderDrawPoint(renderer, rand() % display.w , rand() % display.h);
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
	//end of test
}