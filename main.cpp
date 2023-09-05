#include <iostream>
#include <stdio.h>
#include <thread>

#define SDL_MAIN_HANDLED
#include "SDL.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        cout << "Unable to initialize SDL: " << SDL_GetError();
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 680, 320, 0);
    if (!window)
    {
        cout << "Failed to create window\n";
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Surface *downloadRAM = SDL_LoadBMP("downloadRAM.bmp");
    SDL_Texture *downloadRAM_tex = SDL_CreateTextureFromSurface(renderer, downloadRAM);

    SDL_Surface *frame0 = SDL_LoadBMP("frame0.bmp");
    SDL_Texture *frame0_tex = SDL_CreateTextureFromSurface(renderer, frame0);
    SDL_Surface *frame1 = SDL_LoadBMP("frame1.bmp");
    SDL_Texture *frame1_tex = SDL_CreateTextureFromSurface(renderer, frame1);
    SDL_Surface *frame2 = SDL_LoadBMP("frame2.bmp");
    SDL_Texture *frame2_tex = SDL_CreateTextureFromSurface(renderer, frame2);
    SDL_Surface *frame3 = SDL_LoadBMP("frame3.bmp");
    SDL_Texture *frame3_tex = SDL_CreateTextureFromSurface(renderer, frame3);

    SDL_Texture *nyan_cat_anim[] = {frame0_tex, frame1_tex, frame2_tex, frame3_tex};
    unsigned char frame = 0;

    bool running = true;
    while (running)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            }
        }
        SDL_RenderCopy(renderer, downloadRAM_tex, NULL, NULL);
        // SDL_RenderCopy(renderer, nyan_cat_anim[(frame++) & 0x03], NULL, NULL);
        SDL_RenderPresent(renderer);

        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyTexture(downloadRAM_tex);
    SDL_DestroyTexture(frame0_tex);
    SDL_DestroyTexture(frame1_tex);
    SDL_DestroyTexture(frame2_tex);
    SDL_DestroyTexture(frame3_tex);
    SDL_FreeSurface(downloadRAM);
    SDL_FreeSurface(frame0);
    SDL_FreeSurface(frame1);
    SDL_FreeSurface(frame2);
    SDL_FreeSurface(frame3);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}