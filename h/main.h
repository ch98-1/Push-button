//Copyright (C) 2015  Corwin Hansen
#ifndef MAIN_H//include protection
	#define MAIN_H
//main functions and data types
#include "SDL.h"//include sdl
#include <stdio.h>//input and output
#include <stdlib.h>//standard stuff
#include <math.h>//all the math functions

int EventFilter(void* userdata, SDL_Event* e);//event filtering 

void push(int x, int y);//check if pressed button or not and call button() if pressed.

void button();//button was pressed

SDL_Window *window;//window and renderer
SDL_Renderer *renderer;
SDL_Event e;//event
SDL_DisplayMode display;//desplay mode of the desktop
unsigned int buttonsize;//size of the button 1/4 of the shortest side of screen

#endif