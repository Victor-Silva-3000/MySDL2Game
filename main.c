#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)

// Pixels/s

#define SPEED (300)
int main(int argc, char *argv[]){

    // Initialize video and timer subsystems
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) // If SDL_Init returns 1 show error message
    {   
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;

    }

    // Create game window.
    SDL_Window* window = SDL_CreateWindow(
                                        "DK Fucking Zooms",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        WINDOW_WIDTH, WINDOW_HEIGHT, 0
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

    SDL_Surface* surface = IMG_Load("resources/DK.png");

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

    dest.w /= 4;
    dest.h /= 4;

    float x_pos = (WINDOW_WIDTH - dest.w) / 2;
    float y_pos = (WINDOW_HEIGHT - dest.h) / 2;
    float x_vel = SPEED;
    float y_vel = SPEED;

    int close_requested = 0;
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    /* 
    dest.x = (WINDOW_WIDTH - dest.w) / 2;

    float y_pos = WINDOW_HEIGHT; */

    while(!close_requested){
        
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                close_requested = 1;
            }
        }

        if(x_pos <= 0){
            x_pos = 0;
            x_vel = -x_vel;
        }

        if(y_pos <= 0){
            y_pos = 0;
            y_vel = -y_vel;
        }

        if(x_pos >=  WINDOW_WIDTH - dest.w){
            x_pos = WINDOW_WIDTH - dest.w;
            x_vel = -x_vel;
        }

        if(y_pos >= WINDOW_HEIGHT - dest.h){
            y_pos = WINDOW_HEIGHT - dest.h;
            y_vel = -y_vel;
        } 

        x_pos += x_vel / 60;
        y_pos += y_vel / 60;

        SDL_RenderClear(renderer);

        dest.y = (int) y_pos;
        dest.x = (int) x_pos;

        dest.w++;
        dest.h++;


        printf("%d, %d\n", dest.w, dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
        SDL_RenderPresent(renderer);


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