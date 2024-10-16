#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        printf("Error SDL2 Init : %s\n", SDL_GetError());
        return 1;
    }
    
    SDL_Window* window = SDL_CreateWindow("ex1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 160, 160, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        printf("Error Window Creation\n");
        SDL_Quit();
        return 3;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        printf("Erreur d'initialisation de la SDL_Image\n");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Erreur à la création du renderer\n");
        IMG_Quit();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* surface = IMG_Load("bottle.png");
    if (surface == NULL) {
        printf("Error loading image %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        IMG_Quit();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    // Créer la texture à partir de la surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); // Libérer l'ancienne surface

    if (texture == NULL) {
        printf("Error creating texture\n");
        SDL_DestroyRenderer(renderer);
        IMG_Quit();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    // Créer un rectangle de destination pour centrer l'image
    SDL_Rect destRect;
    destRect.w = 16; // Largeur de l'image
    destRect.h = 16; // Hauteur de l'image
    destRect.x = 160 / 2; // Position X centrée
    destRect.y = 160 / 2; // Position Y centrée

    // Boucle d'événements
    int running = 1;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0; // Sortir de la boucle si l'utilisateur ferme la fenêtre
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &destRect); // Rendu de la texture
        SDL_RenderPresent(renderer);
    }

    // Libération des ressources
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}