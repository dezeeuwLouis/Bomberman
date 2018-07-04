#include "constantes.h"

//Gestion Debut de la SDL
SDL_Window* init_SDL()
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
		fprintf(stderr, "\nUnable to initialize SDL:  %s\n", SDL_GetError());
	if(TTF_Init() != 0)
		fprintf(stderr, "\nUnable to initialize TTF:  %s\n", TTF_GetError());
	point.window = SDL_CreateWindow("Bomberman",
  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LONGUEUR_FENETRE, LARGEUR_FENETRE,
        0);
	if (point.window == NULL)
		fprintf(stderr, "\nCould not create window:  %s\n", SDL_GetError());
	return (point.window);
}

//Gestion Fin de la SDL
int quit_SDL()
{
 SDL_DestroyTexture(point.texture1);
 SDL_DestroyTexture(point.texture2);
 SDL_DestroyTexture(point.texture3);
 SDL_FreeSurface(point.image);
 SDL_FreeSurface(point.image2);
 SDL_DestroyRenderer(point.renderer);
    SDL_DestroyWindow(point.window);
 TTF_CloseFont(point.font);
 TTF_Quit();
 SDL_Quit();
 return (0);
}
