//Copyright (C) 2015  Corwin Hansen
#ifndef MAIN_H//include protection
	#define MAIN_H
//main functions and data types
#include "SDL.h"//include sdl
#include <stdio.h>//input and output
#include <stdlib.h>//standard stuff
#include <math.h>//all the math functions
#include <string.h>//string related things
#include <time.h>//time on system

#define MAX_BUTTONS 1024 //maximum number of buttons
#define MAX_TEXTURES 1024 //maximum number of textures

#define RESOURCES "resources/" //resources folder path

int EventFilter(void* userdata, SDL_Event* e);//event filtering 

void push(int x, int y);//check if pressed button or not and call button() if pressed.

typedef void (*buttonfunction)(void);//button function pointer

buttonfunction button;//function pointer for each different button

SDL_Window *window;//window and renderer
SDL_Renderer *renderer;
SDL_Event e;//event
SDL_DisplayMode display;//desplay mode of the desktop
unsigned int buttonsize;//size of the button 1/4 of the shortest side of screen

buttonfunction *buttons;//array of buttons
unsigned long int buttonssize;//size of buttons

SDL_Texture **textures;//array of texture pointers
unsigned long int texturessize;//size of textures

void startbutton(void);//butrton to start from

unsigned int setbutton(buttonfunction inputbutton);//add button to memory and return that adress

unsigned int gettexture(const char *img);//make texture from image source in resources folder, remove magenta memory and return that adress

void setnext(unsigned int i);//set next button

void inittextures(void);//runs at start. use to get textures

void initbuttons(void);//run at start. use to set buttons

void quit(void);//quit everything

void destroytextures(void);//destroy all textures in list

#endif