//Copyright (C) 2014-2015  Corwin Hansen
#include "button.h"//function for each buttons
#include "main.h"//main function and data type header. Just in case.


int main(int argc, char *argv[]){

	if (SDL_Init(SDL_INIT_VIDEO) != 0){//start SDL and get any error if it dosen't.
		printf("Could not load SDL: %s\n", SDL_GetError());//print out error
		exit(EXIT_FAILURE);
	}

	//filter quit event
	SDL_SetEventFilter(EventFilter, NULL);
	//quit SDL at exit
	atexit(SDL_Quit);

	//get desplay mode of the desktop
	if (SDL_GetDesktopDisplayMode(0, &display) != 0) {
		SDL_Log("Could not get display mode: %s\n", SDL_GetError());//take care of errors
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

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE); //create Renderer. Buggy if hardware accelerated.

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);//enable alpha

	

	buttons = malloc(sizeof(buttonfunction));//allocate memory for buttons
	textures = malloc(sizeof(SDL_Texture*));//allocate memory for textures
	
	buttonssize = sizeof(buttonfunction);//set current buttonsize
	texturessize = sizeof(SDL_Texture*);//set current texturesize

	gettexture("button_down.bmp");//second default texture

	inittextures();//initialise textures
	initbuttons();//initialise buttons

	//starting texture
	char file[256] = RESOURCES;//folder path
	strcat(file, "button.bmp");//append path
	SDL_Surface *Surface = SDL_LoadBMP(file);
	if (Surface == NULL){//if surface is empty
		printf("error: %s \n", file, SDL_GetError());//print error message
		return 0;//return 0 for a error
	}
	SDL_SetColorKey(Surface, SDL_TRUE, SDL_MapRGB(Surface->format, 255, 0, 255));//set Magenta as clear
	textures[0] = SDL_CreateTextureFromSurface(renderer, Surface);//make texture
	SDL_FreeSurface(Surface);//free used surface
	if (textures == NULL){//if it becomes null
		printf("could not allocate new memory for textures\n");//print out error if it happens
	}





	
	buttons[0] = &startbutton;//starting button




	button = buttons[0];//set to initial button
	(*button)();//start initial button


	while (SDL_WaitEvent(&e) != 0){//wait for event to happen
		//update desplay mode of the desktop
		if (SDL_GetDesktopDisplayMode(0, &display) != 0) {
			SDL_Log("Could not get display mode: %s\n", SDL_GetError());//take care of errors
			exit(EXIT_FAILURE);
		}
		if (display.h > display.w) buttonsize = display.w / 4;//quorter of shortest screen size
		else buttonsize = display.h / 4;


		switch (e.type) {
		case SDL_QUIT://quit everything
			quit();//quit everything
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
	quit();//quit everything
}






int EventFilter(void* userdata, SDL_Event* e){//event filter
	switch (e->type) {
	case SDL_QUIT://quit everything
		quit();//quit everything
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
		status = DOWN;//button down
		update();
		while (SDL_WaitEventTimeout(&e, 500) != 0){//wait until button goes up or 1/2 second passes without an event
			if (e.type == SDL_MOUSEBUTTONUP){//if button went up
				break;//break out of loop
			}
		}
		status = UP;//button up
		update();
		(*button)();//call button function
	}
	//button was not pressed
}







void setnext(unsigned int i){//set next button
	if (i < MAX_BUTTONS){//if not out of limit
		button = buttons[i];//set next button
	}
	else {
		button = buttons[0];//set to initial button if out of limit
	}
}






unsigned int setbutton(buttonfunction inputbutton){//add button to memory and return that adress
	if (buttonssize / sizeof(buttonfunction) < MAX_BUTTONS){//if not out of limit
		buttonssize += sizeof(buttonfunction);//update buttonsize
		buttons = realloc(buttons, buttonssize);//reallocate memory for longer array
		if (buttons == NULL){//if it becomes null
			printf("could not allocate new memory for buttons\n");//print out error if it happens
			return 0;//return 0 for error
		}
		buttons[buttonssize/sizeof(buttonfunction)-1] = inputbutton;//set value
		return buttonssize/sizeof(buttonfunction)-1;//button adress
	}
	printf("could not allocate new memory for buttons\n");//print out error
	return 0;//return 0 for error
}



unsigned int gettexture(const char *img){//make texture from image source in resources folder, remove magenta memory and return that adress
	if (texturessize / sizeof(SDL_Texture*) < MAX_TEXTURES){//if not out of limit
		texturessize += sizeof(SDL_Texture*);//update texturesize
		char file[256] = RESOURCES;//folder path
		strcat(file, img);//append path
		SDL_Surface *Surface;
		Surface = SDL_LoadBMP(file);
		if (Surface == NULL){//if surface is empty
			printf("error: %s \n", file, SDL_GetError());//print error message
			return 0;//return 0 for a error
		}
		SDL_SetColorKey(Surface, SDL_TRUE, SDL_MapRGB(Surface->format, 255, 0, 255));//set Magenta as clear
		SDL_Texture *Texture = SDL_CreateTextureFromSurface(renderer, Surface);//make texture
		SDL_FreeSurface(Surface);//free used surface
		textures = realloc(textures, texturessize);//reallocate memory for longer array
		if (textures == NULL){//if it becomes null
			printf("could not allocate new memory for textures\n");//print out error if it happens
		}
		textures[texturessize / sizeof(SDL_Texture*)-1] = Texture;//make texture
		return texturessize / sizeof(SDL_Texture*)-1;//button adress
	}
	//do nothing if out of limit
	printf("could not allocate new memory for textures\n");//print out error
	return 0;//return 0 for an error
}




void destroytextures(void){
	int i;//counter
	for (i = sizeof(textures)/sizeof(SDL_Texture*); i > 0; i--){//for each texture in array
		SDL_DestroyTexture(textures[i - 1]);//destroy texture
	}
}




void quit(void){//quit everything
	SDL_DestroyRenderer(renderer);//destroy renderer
	SDL_DestroyWindow(window);//destro window
	SDL_Quit();//end of running SDL
	free(buttons); //free button functions
	destroytextures();//destroy texture array
	free(textures);//free textures
	exit(EXIT_SUCCESS);//end of program
}






void startbutton(void){//Starting button.



	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);//set sendering color to white
	SDL_RenderClear(renderer);//clear renderer

	SDL_Rect dest;//rectangle for button
	dest.w = buttonsize;
	dest.h = buttonsize;
	dest.x = display.w / 2 - buttonsize / 2;//center
	dest.y = display.h / 2 - buttonsize / 2;//center;
	SDL_RenderCopy(renderer, textures[0], NULL, &dest);//draw button
	SDL_RenderPresent(renderer);//render what is drawn

	srand((unsigned int)(clock() + SDL_GetTicks()));//seed random number generator
	setnext(rand()%buttonssize/sizeof(buttonfunction));//set new button function to any of possible buttons


}


void update(void){//update screen
	if (status == NO_BUTTON ||( status != UP && status != DOWN)){//if thereis no button to draw
		SDL_RenderPresent(renderer);//update screen
		return;//end of function
	}
	SDL_Rect dest;//rectangle for button
	dest.w = buttonsize;
	dest.h = buttonsize;
	dest.x = display.w / 2 - buttonsize / 2;//center
	dest.y = display.h / 2 - buttonsize / 2;//center;
	SDL_RenderCopy(renderer, textures[status], NULL, &dest);//draw button
	SDL_RenderPresent(renderer);//update screen
}