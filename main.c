#include <stdio.h>
#include <SDL2/SDL.h>


int main(void){

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Error initializing SLD: %s\n", SDL_GetError());
        return 1;

    }

    printf("SDL Initialized successfully!\n");

    SDL_Quit();

}