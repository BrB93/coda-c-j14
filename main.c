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
        printf("Error Window Creation: %s\n", SDL_GetError());
        SDL_Quit();
        return 3;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Erreur d'initialisation de la SDL_Image: %s\n", IMG_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Erreur à la création du renderer: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* surface = IMG_Load("bottle.png");
    if (surface == NULL) {
        printf("Error loading image: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        IMG_Quit();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (texture == NULL) {
        printf("Error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        IMG_Quit();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Rect destRect;
    destRect.w = surface->w;
    destRect.h = surface->h;
    destRect.x = (160 - destRect.w) / 2; // Position X centrée
    destRect.y = (160 - destRect.h) / 2; // Position Y centrée

    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                // Déplacer l'image en fonction de la touche pressée
                if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                    destRect.x -= 5; // Déplace vers la gauche
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                    destRect.x += 5; // Déplace vers la droite
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                    destRect.y -= 5; // Déplace vers haut
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                    destRect.y += 5; // Déplace vers bas
                }
            }
        }

        // Vérification des limites pour ne pas sortir de la fenêtre
        if (destRect.x < 0) {
            destRect.x = 0; // Limite gauche
        } else if (destRect.x > 160 - destRect.w) {
            destRect.x = 160 - destRect.w; // Limite droite
        }
        if (destRect.y < 0)
        {
            destRect.y = 0;                            //limite hauteur
        } else if (destRect.y > 160 - destRect.h)
        {
            destRect.y = 160 - destRect.h;
        }

        SDL_SetRenderDrawColor(renderer, 156, 150, 150, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &destRect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
