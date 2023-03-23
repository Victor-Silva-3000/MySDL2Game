#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)

// Pixels/s
#define SCROLL_SPEED (300)
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
    

    SDL_Rect dest;

    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    dest.x = (WINDOW_WIDTH - dest.w) / 2;

    float y_pos = WINDOW_HEIGHT;

    while(dest.y >= -dest.h){
        SDL_RenderClear(renderer);

        dest.y = (int) y_pos;

        SDL_RenderCopy(renderer, texture, NULL, &dest);
        SDL_RenderPresent(renderer);

        y_pos -= (float) SCROLL_SPEED / 60;

        SDL_Delay(1000/60);

    }



    // Remove window
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Release SDL resources from memory to safely quit.
    SDL_Quit();

    return 1;

}