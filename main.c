#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>


int main(void){

    // Initialize video and timer subsystems
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) // If SDL_Init returns 1 show error message
    {   
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;

    }

    // Create game window.
    SDL_Window* window = SDL_CreateWindow(
                                        "MySDL2Game",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        640, 480, 0
                                        );

    if(!window){
        printf("Failed to create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }


    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, render_flags);

    if(!renderer){
        printf("Failed to create renderer: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* surface = IMG_Load("resources/hello.png");

    if(!surface){
        printf("Failed to create surface: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if(!texture){
        printf("Failed to create texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    printf("SDL Initialized successfully!\n");

    // Wait for 5000ms (5 seconds)
    SDL_Delay(5000);

    // Remove window
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Release SDL resources from memory to safely quit.
    SDL_Quit();

    return 1;

}