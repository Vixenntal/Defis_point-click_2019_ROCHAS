#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

/*Prototype fonctions/procédures*/
int setWindowColor(SDL_Renderer *renderer, SDL_Color color);

int main(int argc, char *argv[])
{
    /*DEFINITION DES VARIABLES*/
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    int statut = EXIT_FAILURE;
    SDL_Rect rect = {160, 90, 320, 180}, dst = {320, 180, 640, 360};
    SDL_Color rouge = {255, 0, 0, 255}, bleu = {0, 0, 255, 255}, orange = {255, 127, 40, 255};
    SDL_Event event;
    int continuer = 1;

    /*DEBUT DU CODE*/
    /*CREATION ET INITIALISATION*/
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }

    if(0 != SDL_CreateWindowAndRenderer(1280, 720, SDL_WINDOW_SHOWN, &window, &renderer))
    {
        fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        goto Quit;
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_TARGET, 640, 360);
    if(NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTexture : %s", SDL_GetError());
        goto Quit;
    }

    /*DEBUT DU PROGRAMME*/

    setWindowColor(renderer, orange);

    while(continuer)
    {
        SDL_PollEvent(&event);

        switch(event.type)
        {
            case SDL_QUIT:
            continuer = 0;
            break;

            case SDL_MOUSEBUTTONDOWN:

            switch(event.button.button)
            {
                case SDL_BUTTON_LEFT:
                continuer = 0;
                break;

                default:
                break;
            }
            break;
        }
    }
    SDL_SetRenderTarget(renderer, texture);
    /* La texture est la cible de rendu, maintenant, on dessine sur la texture. */
    SDL_SetRenderDrawColor(renderer, bleu.r, bleu.g, bleu.b, bleu.a);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, rouge.r, rouge.g, rouge.b, rouge.a);
    SDL_RenderFillRect(renderer, &rect); /* On dessine un rectangle rouge sur la texture. */

    SDL_SetRenderTarget(renderer, NULL); /* Le renderer est la cible de rendu. */

    /* On récupère les dimensions de la texture, on la copie sur le renderer
       et on met à jour l’écran. */
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_RenderPresent(renderer);
    statut = EXIT_SUCCESS;

    /*Evenement qui ferme la fenetre*/
    SDL_bool quit = SDL_FALSE;
    while(!quit)
    {
        while(SDL_PollEvent(&event))
            if(event.type == SDL_QUIT)
                quit = SDL_TRUE;
        SDL_Delay(20);
    }

Quit:
    if(NULL != texture)
    {
        SDL_DestroyTexture(texture);
    }

    if(NULL != renderer)
    {
        SDL_DestroyRenderer(renderer);
    }

    if(NULL != window)
    {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();

    return statut;
}

/*Fonction qui permet de changer la couleur de la fenetre*/
int setWindowColor(SDL_Renderer *renderer, SDL_Color color)
{
    if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0)
        return -1;
    if(SDL_RenderClear(renderer) < 0)
        return -1;
    return 0;
}
