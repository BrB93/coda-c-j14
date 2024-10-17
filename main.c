#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

char * get_file(FILE * fp)
{
    char * content;
    char buffer[10];

    content = malloc(sizeof(char));
    content[0] = '\0';

    while(fgets(buffer, 10, fp) != NULL)
    {
        content = realloc(content, (strlen(buffer) * sizeof(char)) + strlen(content) * sizeof(char) + 1);
        content = strcat(content, buffer);
    }

    return content;
}

int count_lines(char *str)
{
    int i = 0;
    int lines = 0;

    while(str[i] != '\0')
    {
        if(str[i] == '\n')
        {
            lines++;
        }

        i++;
    }

    return lines;
}

void display_tab(char **tab, int lines)
{
    int i = 0;

    while(i < lines)
    {
        printf("%s\n", tab[i]);
        i++;
    }
}

int main()
{
    FILE *fp = fopen("map.txt", "r");
    char * file_content;
    char **tab;
    int lines;
    char * line;
    int i = 0;
    int j = 0;

    if (fp == NULL)
    {
        printf("Le fichier map.txt n'a pas pu être ouvert\n");
        return EXIT_FAILURE;
    }

    file_content = get_file(fp);

    fclose(fp);
    
    lines = count_lines(file_content);

    tab = malloc(lines * sizeof(*tab));

    line = strtok(file_content, "\n");
    while((line != NULL) && (i < lines))
    {
        tab[i] = malloc(strlen(line) * sizeof(char));
        tab[i] = strcpy(tab[i], line);
        i++;

        line = strtok(NULL, "\n");
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
        printf("Error SDL2 Init : %s\n", SDL_GetError());
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) 
    {
        printf("Erreur d'initialisation de la SDL_Image\n");
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Exercice 4", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 160, SDL_WINDOW_OPENGL);

    if (window == NULL) 
    {
        printf("Error while creating a window : %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) 
    {
        printf("Erreur à la création du renderer\n");
        return 1;
    }

    SDL_Surface* surface = IMG_Load("levels.png");
    if (surface == NULL) 
    {
        printf("Error loading image %s\n", IMG_GetError());
        return 1;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) 
    {
        printf("Error creating texture\n");
        return 1;
    }

    SDL_FreeSurface(surface);   

    while(1)
    {
        SDL_Event e;
        if (SDL_WaitEvent(&e)) 
        {
            if (e.type == SDL_QUIT) 
            {
                break;
            }
        }

        SDL_RenderClear(renderer);
        i = 0;
        while(i < lines)
        {
            j = 0;
            while(j < 20)
            {
                if(tab[i][j] == '0')
                {
                    SDL_Rect rect = {j * 16, i * 16, 16, 16};
                    SDL_Rect rect_img = {0,0, 16, 16};
                    SDL_RenderCopy(renderer, texture, &rect_img, &rect);
                }
                else if(tab[i][j] == '1')
                {
                    SDL_Rect rect = {j * 16, i * 16, 16, 16};
                    SDL_Rect rect_img = {16,0, 16, 16};
                    SDL_RenderCopy(renderer, texture, &rect_img, &rect);
                }
                else if(tab[i][j] == '2')
                {
                    SDL_Rect rect = {j * 16, i * 16, 16, 16};
                    SDL_Rect rect_img = {32,0, 16, 16};
                    SDL_RenderCopy(renderer, texture, &rect_img, &rect);
                }
                else if(tab[i][j] == '3')
                {
                    SDL_Rect rect = {j * 16, i * 16, 16, 16};
                    SDL_Rect rect_img = {48,0, 16, 16};
                    SDL_RenderCopy(renderer, texture, &rect_img, &rect);
                }
                else if(tab[i][j] == '4')
                {
                    SDL_Rect rect = {j * 16, i * 16, 16, 16};
                    SDL_Rect rect_img = {64,0, 16, 16};
                    SDL_RenderCopy(renderer, texture, &rect_img, &rect);
                }

                j++;
            }

            i++;
        }

        SDL_RenderPresent(renderer);
    }


    SDL_Quit();

    for (i = 0; i < lines; i++) {
        free(tab[i]);
    }
    free(tab);
    free(file_content);
    return 0; 
}