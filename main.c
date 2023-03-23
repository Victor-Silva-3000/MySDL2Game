#include <stdio.h>
#include <SDL2/SDL.h>


int main(void){

    // Initialize video and timer subsystems
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) // If SDL_Init returns 1 show error message
    {   
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;

    }

    // Create game window.
    SDL_Window* window = SDL_CreateWindow("MySDL2Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

    if(!window){
        printf("Failed to create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    printf("SDL Initialized successfully!\n");

    // Wait for 5000ms (5 seconds)
    SDL_Delay(5000);

    // Remove window
    SDL_DestroyWindow(window);

    // Release SDL resources from memory to safely quit.
    SDL_Quit();
    
    return 1;

}