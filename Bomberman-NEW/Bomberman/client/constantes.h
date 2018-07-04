#include <stdlib.h>
#include "include/SDL_image.h"
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>*/
#include <tchar.h>
#include <strsafe.h>
#include "include/SDL.h"
#include "include/SDL_image.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "socketTools.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Windows.h>
#include <SDL_mixer.h>
#include "socketTools.h"
#pragma comment(lib,"ws2_32.lib") //Winsock Library


#define TAILLE_REC_TCP 2000 //Taille d'une reception

#define LONGUEUR_FENETRE 480
#define LARGEUR_MAP_FENETRE 416
#define LARGEUR_FENETRE 416
#define SHAPE_SIZE 32
#define PORT 4242

#define NOMBRE_BLOCS_LARGEUR 15  // nombre a afficher en x et y
#define NOMBRE_BLOCS_HAUTEUR 11

int l_COMPTEUR;
enum {HAUT, BAS, GAUCHE, DROITE};
enum {VIDE, MUR, CAISSE, OBJECTIF, J1, CAISSE_OK};

typedef struct argument_struct
{
 char ip[17];
 char login[20];
}T_ARGUMENT;

struct my_struc

{
	SDL_Texture* texture1;
	SDL_Texture* texture2;
	SDL_Texture* texture3;
	SDL_Texture* texture4;
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Surface* surface1;
	SDL_Surface* surface2;
	SDL_Surface* surface3;
	SDL_Surface* surface4;
	SDL_Surface* image;
	SDL_Surface* image2;
	int tW;
	int tH;
	SDL_Rect pos1;
	SDL_Rect pos2;
	SDL_Rect pos3;
	SDL_Event event;
	int nb;
};

struct my_struc point;


//Déclaration de nos 2 threads
DWORD WINAPI ThreadGameEngine(LPVOID lpParam);
DWORD WINAPI ThreadMusic(LPVOID lpParam);
char** initMap(char** MAP);
void closeAll(SDL_Renderer* Main_Renderer, SDL_Window* Main_Window, HANDLE* hThreadArray, SOCKET* MySocket);
int openAll(HANDLE* hThreadArray, SOCKET* MySocket, char* ip);
int checkGameState(SOCKET MySocket);
int gestionEvenement(SDL_Event event, SOCKET MySocket);
int gestionMap(SDL_Renderer* Main_Renderer, SOCKET MySocket, char** MAP);
int LaunchGame(char** MAP, SOCKET MySocket, char* name, char* ip);
int quit_SDL();
SDL_Window* init_SDL();
int menu();
int menu2(int nb);
int first_menu();
int finJeu(char* Message, int etat);
int attenteFinJeu(char* Message, int etat);
