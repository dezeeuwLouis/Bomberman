#include "constantes.h"

//Menu 1
int menu()
{
 SDL_Color color = { 255, 51, 255 };
 
 point.tW = 300;
 point.tH = 100;
 point.pos1.x = 80;
 point.pos1.y = 0;
 point.pos1.w = point.tW;
 point.pos1.h = point.tH;
 point.pos2.x = 80;
 point.pos2.y = 300;
 point.pos2.w = point.tW;
 point.pos2.h = point.tH;
 point.renderer = SDL_CreateRenderer(point.window, -1, SDL_RENDERER_ACCELERATED);
	if(point.renderer == NULL)
	{
		fprintf(stderr, "\nCould not create a renderer :  %s\n", SDL_GetError());
		return (-1);
	}
	point.image = SDL_LoadBMP("Medias/menu1.bmp");
	if (point.image == NULL)
	{
		fprintf(stderr, "\nCould not load a image :  %s\n", SDL_GetError());
		return (-1);
	}
	point.font = TTF_OpenFont("Medias/game_over.ttf", 800);
	if (point.font == NULL)
	{
		fprintf(stderr, "\nCould not load a font :  %s\n", TTF_GetError());
		return (-1);
	}
	point.texture2 = SDL_CreateTextureFromSurface(point.renderer, point.image);
	if (point.texture2 == NULL)
	{
		fprintf(stderr, "\nCreateTextureFromSurface failed : %s\n", SDL_GetError());
		return (-1);
	}
	point.surface2 = TTF_RenderText_Solid(point.font, "Press Enter !", color);
	if (point.surface2 == NULL) 
	{
		fprintf(stderr, "\nCreateTextureFromSurface failed : %s\n", TTF_GetError());
		return (-1);
	}
	point.texture3 = SDL_CreateTextureFromSurface(point.renderer, point.surface2);
	if (point.texture3 == NULL)
	{
		fprintf(stderr, "\nCreateTextureFromSurface failed : %s\n", SDL_GetError());
		return (-1);
	}
	point.surface1 = TTF_RenderText_Solid(point.font, "My_Bomberman !", color);
	if (point.surface1 == NULL) 
	{
		fprintf(stderr, "\nCreateTextureFromSurface failed : %s\n", TTF_GetError());
		return (-1);
	}
	point.texture1 = SDL_CreateTextureFromSurface(point.renderer, point.surface1);
	if (point.texture1 == NULL)
	{
		fprintf(stderr, "\nCreateTextureFromSurface failed : %s\n", SDL_GetError());
		return (-1);
	}
	SDL_QueryTexture(point.texture1, NULL, NULL, &point.tW, &point.tH);
	SDL_QueryTexture(point.texture3, NULL, NULL, &point.tW, &point.tH);
	SDL_RenderCopy(point.renderer, point.texture2, NULL, NULL);
	SDL_RenderCopy(point.renderer, point.texture1, NULL, &point.pos1);
	SDL_RenderCopy(point.renderer, point.texture3, NULL, &point.pos2);
	SDL_RenderPresent(point.renderer);
	return 0;
}

//Menu 2
int menu2(int nb)
{
 SDL_Color color = { 0, 0, 0 };

 point.tW = 300;
 point.tH = 100;
 point.pos1.x = 80;
 point.pos1.y = 0;
 point.pos1.w = point.tW;
 point.pos1.h = point.tH;
 point.pos3.x = 80;
 point.pos3.y = 300;
 point.pos3.w = point.tW;
 point.pos3.h = point.tH;
 	
	point.window = init_SDL();
	point.renderer = SDL_CreateRenderer(point.window, -1, SDL_RENDERER_ACCELERATED);
	if(point.renderer == NULL)
	{
		fprintf(stderr, "\nCould not create a renderer :  %s\n", SDL_GetError());
		return (-1);
	}
	point.image = SDL_LoadBMP("Medias/menu2.bmp");
	if (point.image == NULL)
	{
		fprintf(stderr, "\nCould not load a image :  %s\n", SDL_GetError());
		return (-1);
	}
	point.font = TTF_OpenFont("Medias/game_over.ttf", 800);
	if (point.font == NULL)
	{
		fprintf(stderr, "\nCould not load a font :  %s\n", TTF_GetError());
		return (-1);
	}
	point.texture2 = SDL_CreateTextureFromSurface(point.renderer, point.image);
	if (point.texture2 == NULL)
	{
		fprintf(stderr, "\nCreateTextureFromSurface failed : %s\n", SDL_GetError());
		return (-1);
	}
	point.surface3 = TTF_RenderText_Solid(point.font, "My_Bomberman !", color);
	if (point.surface3 == NULL) 
	{
		fprintf(stderr, "\nCreateTextureFromSurface failed : %s\n", TTF_GetError());
		return (-1);
	}
	point.texture3 = SDL_CreateTextureFromSurface(point.renderer, point.surface3);
	if (point.texture3 == NULL)
	{
		fprintf(stderr, "\nCreateTextureFromSurface failed : %s\n", SDL_GetError());
		return (-1);
	}
	point.surface1 = TTF_RenderText_Solid(point.font, "Press enter to play !", color);
	if (point.surface1 == NULL) 
	{
		fprintf(stderr, "\nCreateTextureFromSurface failed : %s\n", TTF_GetError());
		return (-1);
	}
	point.texture1 = SDL_CreateTextureFromSurface(point.renderer, point.surface1);
	if (point.texture1 == NULL)
	{
		fprintf(stderr, "\nCreateTextureFromSurface failed : %s\n", SDL_GetError());
		return (-1);
	}
	SDL_QueryTexture(point.texture1, NULL, NULL, &point.tW, &point.tH);
	SDL_QueryTexture(point.texture3, NULL, NULL, &point.tW, &point.tH);
	SDL_RenderCopy(point.renderer, point.texture2, NULL, NULL);
	SDL_RenderCopy(point.renderer, point.texture3, NULL, &point.pos1);
	SDL_RenderCopy(point.renderer, point.texture1, NULL, &point.pos3);
	
	SDL_RenderPresent(point.renderer);
	while (point.nb == 0)
    {
        SDL_WaitEvent(&point.event);
 
        switch (point.event.type)
        {
            case SDL_QUIT:
                point.nb = 1;
                break;
			case SDL_KEYDOWN:
				switch (point.event.key.keysym.sym)
				{
				case SDLK_RETURN:
					point.nb = 1;
					break;
				}
			break;
		}
    }
	return point.nb;

}

//Gestion des 2 menus
int first_menu()
{
 point.nb = 0;
 
 point.window = init_SDL();
 menu();
 while (point.nb == 0)
    {
        SDL_WaitEvent(&point.event); 
        switch (point.event.type)
        {
            case SDL_QUIT:
                point.nb = 1;
                break;
   case SDL_KEYDOWN:
    switch (point.event.key.keysym.sym)
    {
    case SDLK_RETURN:
     point.nb = menu2(point.nb);
     break;
    }
   break;
  }
    }
    quit_SDL();
 return 0;
}

//Fin du jeu
int finJeu(char* Message, int etat)
{
 SDL_Color color = { 255, 51, 255 };
 
 point.tW = 300;
 point.tH = 100;
 point.pos1.x = 80;
 point.pos1.y = 0;
 point.pos1.w = point.tW;
 point.pos1.h = point.tH;
 point.pos2.x = 80;
 point.pos2.y = 300;
 point.pos2.w = point.tW;
 point.pos2.h = point.tH;
 point.renderer = SDL_CreateRenderer(point.window, -1, SDL_RENDERER_ACCELERATED);
	if(point.renderer == NULL)
	{
		fprintf(stderr, "\nCould not create a renderer :  %s\n", SDL_GetError());
		return (-1);
	}
	if (etat == 1)
		point.image = SDL_LoadBMP("Medias/menu3.bmp");
	else 
		point.image = SDL_LoadBMP("Medias/menu4.bmp");

	if (point.image == NULL)
	{
		fprintf(stderr, "\nCould not load a image :  %s\n", SDL_GetError());
		return (-1);
	}
	point.font = TTF_OpenFont("Medias/game_over.ttf", 800);
	if (point.font == NULL)
	{
		fprintf(stderr, "\nCould not load a font :  %s\n", TTF_GetError());
		return (-1);
	}
	point.texture2 = SDL_CreateTextureFromSurface(point.renderer, point.image);
	if (point.texture2 == NULL)
	{
		fprintf(stderr, "\nCreateTextureFromSurface failed : %s\n", SDL_GetError());
		return (-1);
	}
	point.surface2 = TTF_RenderText_Solid(point.font, Message, color);
	if (point.surface2 == NULL) 
	{
		fprintf(stderr, "\nCreateTextureFromSurface failed : %s\n", TTF_GetError());
		return (-1);
	}
	point.texture3 = SDL_CreateTextureFromSurface(point.renderer, point.surface2);
	if (point.texture3 == NULL)
	{
		fprintf(stderr, "\nCreateTextureFromSurface failed : %s\n", SDL_GetError());
		return (-1);
	}
	point.surface1 = TTF_RenderText_Solid(point.font, Message, color);
	if (point.surface1 == NULL) 
	{
		fprintf(stderr, "\nCreateTextureFromSurface failed : %s\n", TTF_GetError());
		return (-1);
	}
	point.texture1 = SDL_CreateTextureFromSurface(point.renderer, point.surface1);
	if (point.texture1 == NULL)
	{
		fprintf(stderr, "\nCreateTextureFromSurface failed : %s\n", SDL_GetError());
		return (-1);
	}
	SDL_QueryTexture(point.texture1, NULL, NULL, &point.tW, &point.tH);
	SDL_QueryTexture(point.texture3, NULL, NULL, &point.tW, &point.tH);
	SDL_RenderCopy(point.renderer, point.texture2, NULL, NULL);
	SDL_RenderCopy(point.renderer, point.texture1, NULL, &point.pos1);
	SDL_RenderCopy(point.renderer, point.texture3, NULL, &point.pos2);
	SDL_RenderPresent(point.renderer);
	return 0;
}

//Gestion fin de jeu en attendant l'appui sur une touche
int attenteFinJeu(char* Message, int etat)
{
	 int i = 0;
 
 point.window = init_SDL();
 finJeu(Message, etat);
 while (i != 1)
    {
        SDL_WaitEvent(&point.event);
 
        switch (point.event.type)
        {
            case SDL_QUIT:
                i = 1;
                break;
			case SDL_KEYDOWN:
				switch (point.event.key.keysym.sym)
				{
				case SDLK_RETURN:
					i = 1;
					break;
				}
			break;
		}
    }
    quit_SDL();
 return 0;
}
