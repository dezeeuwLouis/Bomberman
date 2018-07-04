#include "constantes.h"

//Gestion de l'état actuelle de la partie
int checkGameState(SOCKET MySocket)
{
	int l_retour = 0;
	char* P_Message = NULL;
	P_Message = (char*)malloc(2);
	strcpy(P_Message, " \0");

	l_retour = sendMessage(MySocket, "s");
	if (l_retour == 1)
		return -3;
	P_Message = receiveMessage(MySocket, P_Message, 1);


	if (P_Message[0] == 'd')
	{
		free(P_Message);
		return -1;
	}
	if (P_Message[0] == 'w')
	{	
		P_Message = receiveMessage(MySocket, P_Message, 1);
		printf("Le Joueur %c a gagné la partie\n", P_Message[0]);
		if (P_Message == NULL)
			return -3;
		free(P_Message);
		return -2;
	}
	else
	{
		free(P_Message);
		return 0;
	}
}

//Gestion des evenement Clavier recu
int gestionEvenement(SDL_Event event, SOCKET MySocket)
{
	int l_retour = 0;
	char* P_Message = NULL;
	P_Message = (char*)malloc(2);

	strcpy(P_Message, " \0");
if (event.type == SDL_KEYDOWN)
  {
   if (event.type == SDL_QUIT)
    l_retour = -2;
   else if (event.key.keysym.sym == SDLK_UP)
    P_Message[0] = '1';
   else if (event.key.keysym.sym == SDLK_DOWN)
    P_Message[0] = '2';
   else if (event.key.keysym.sym == SDLK_LEFT)
    P_Message[0] = '3';
   else if (event.key.keysym.sym == SDLK_RIGHT)
    P_Message[0] = '4';
   else if (event.key.keysym.sym == SDLK_SPACE)
		P_Message[0] = '5';
   else
    P_Message[0] = ' ';
   
   if (P_Message[0] != ' ' && l_retour != -2)
   {
    l_retour = sendMessage(MySocket, P_Message);
	if (P_Message[0] == '5')
	{
	P_Message = receiveMessage(MySocket, P_Message, 1);
	if (P_Message[0] == '0')
		l_COMPTEUR++;
	}
   }
  }
free(P_Message);
	return l_retour;
}

//Gestion de la Map et de son affichage
int gestionMap(SDL_Renderer* Main_Renderer, SOCKET MySocket, char** MAP)
{
	int l_retour;
	int ligneTab, colonneTab, ligneSDL, colonneSDL;
	SDL_Surface* Loading_Surf;
	SDL_Rect L_Rect;
	SDL_Texture* L_Shape;
	int l_ligne = 0;
	l_retour = sendMessage(MySocket, "u\0");

	for (l_ligne = 0;l_ligne < 11;l_ligne++)
		MAP[l_ligne] = receiveMessage(MySocket, MAP[l_ligne], 15);

	ligneTab = 0;
	
	for(ligneSDL=SHAPE_SIZE*2;ligneSDL<LARGEUR_FENETRE;ligneSDL+=SHAPE_SIZE)
	{
		colonneTab = 0;
		for(colonneSDL=0;colonneSDL<=LONGUEUR_FENETRE;colonneSDL+=SHAPE_SIZE)
		{
			if(MAP[ligneTab][colonneTab] == 'v')
				Loading_Surf = SDL_LoadBMP("./Medias/weed.bmp");
			else if(MAP[ligneTab][colonneTab] == '1')
				Loading_Surf = SDL_LoadBMP("./Medias/jeffery.bmp");
			else if(MAP[ligneTab][colonneTab] == '2')
				Loading_Surf = SDL_LoadBMP("./Medias/kanye.bmp");
			else if(MAP[ligneTab][colonneTab] == '3')
				Loading_Surf = SDL_LoadBMP("./Medias/travis.bmp");
			else if(MAP[ligneTab][colonneTab] == '4')
				Loading_Surf = SDL_LoadBMP("./Medias/future.bmp");
			else if(MAP[ligneTab][colonneTab] == 'b')
				Loading_Surf = SDL_LoadBMP("./Medias/bombe.bmp");
			else if(MAP[ligneTab][colonneTab] == 'x')
				Loading_Surf = SDL_LoadBMP("./Medias/flamme.bmp");
			else if(MAP[ligneTab][colonneTab] == 'm')
				Loading_Surf = SDL_LoadBMP("./Medias/mur.bmp");
			else if(MAP[ligneTab][colonneTab] == 'w')
				Loading_Surf = SDL_LoadBMP("./Medias/briqueCassable.bmp");
			else if(MAP[ligneTab][colonneTab] == 'p')
				Loading_Surf = SDL_LoadBMP("./Medias/bonusPortee.bmp");
			else if(MAP[ligneTab][colonneTab] == 'q')
				Loading_Surf = SDL_LoadBMP("./Medias/malusPortee.bmp");
			else if(MAP[ligneTab][colonneTab] == 's')
				Loading_Surf = SDL_LoadBMP("./Medias/bonusNbBombe.bmp");
			else if(MAP[ligneTab][colonneTab] == 't')
				Loading_Surf = SDL_LoadBMP("./Medias/malusNbBombe.bmp");
			else
				Loading_Surf = SDL_LoadBMP("./Medias/malusNbBombe.bmp");
			L_Rect.y = ligneSDL;
			L_Rect.x = colonneSDL;
			L_Rect.w = SHAPE_SIZE;
			L_Rect.h = SHAPE_SIZE;

			L_Shape = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
			SDL_FreeSurface(Loading_Surf);
			SDL_RenderCopy(Main_Renderer, L_Shape, NULL, &L_Rect);
			SDL_RenderPresent(Main_Renderer);
			colonneTab++;
		}
		ligneTab++;
	}
	return 0;
}

//Boucle de Jeu
int LaunchGame(char** MAP, SOCKET MySocket, char* name, char* ip)
{
	HANDLE hThreadArray[2];
	SDL_Window* Main_Window = NULL;
	SDL_Renderer* Main_Renderer = NULL;
	SDL_Event event;
	int flag = 0;
	int flag2 = 0;
	MAP = initMap(MAP);

	flag = openAll(hThreadArray, &MySocket, ip);
	Main_Window = SDL_CreateWindow("Bomberman Play",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LONGUEUR_FENETRE, LARGEUR_FENETRE, 0);
	Main_Renderer = SDL_CreateRenderer(Main_Window, -1, SDL_RENDERER_ACCELERATED);

	if (flag < 0)
	{
		free(MAP);
		return flag;
	}
	while (flag >= 0)
	{
        flag = SDL_WaitEventTimeout(&event, 100);
		if (flag == 1)
			flag = gestionEvenement(event, MySocket);
		else
			gestionMap(Main_Renderer, MySocket, MAP);
		flag = checkGameState(MySocket);
	}
	
	closeAll(Main_Renderer, Main_Window, hThreadArray, &MySocket);
  return flag;
}
