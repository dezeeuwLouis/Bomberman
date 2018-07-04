#include "constantes.h"


//Initialisation de la map avec malloc
char** initMap(char** MAP)
{
	int i = 0;
	int j = 0;

	if (( MAP = (char**)malloc( NOMBRE_BLOCS_HAUTEUR*sizeof( char* ))) == NULL )
		perror("error");
	for ( i = 0; i <NOMBRE_BLOCS_HAUTEUR; i++ )
	{	
		if (( MAP[i] = (char*)malloc( NOMBRE_BLOCS_LARGEUR+1 )) == NULL )
		  perror("error");
	}
	return MAP;
}

//Gestion fin de la boucle de jeu
void closeAll(SDL_Renderer* Main_Renderer, SDL_Window* Main_Window, HANDLE* hThreadArray, SOCKET* MySocket)
{
	int i = 0;
	SDL_DestroyRenderer(Main_Renderer);
	SDL_DestroyWindow(Main_Window);
	SDL_Quit();
	for (i = 0; i < 2; i++)
	{
		CloseHandle(hThreadArray[i]);

	}
	closeConnection(MySocket);
	WaitForMultipleObjects(2, hThreadArray, TRUE, INFINITE);
}

//Permet d'ouvrir les sockets et les Threads
int openAll(HANDLE* hThreadArray, SOCKET* MySocket, char* ip)
{
	char* L_serverReply = NULL;
	DWORD* dwThreadIdArray = 0;
	
	hThreadArray[0] = CreateThread( 
    NULL,                   // default security attributes
    0,                      // use default stack size  
    ThreadGameEngine,       // thread function name
	MySocket,          // argument to thread function 
    0,                      // use default creation flags 
    dwThreadIdArray);   // returns the thread identifier  
   if (hThreadArray == NULL) 
        return -3;

   	hThreadArray[1] = CreateThread( 
    NULL,                   // default security attributes
    0,                      // use default stack size  
	ThreadMusic,       // thread function name
	NULL,          // argument to thread function 
    0,                      // use default creation flags 
    dwThreadIdArray);   // returns the thread identifier  
   if (hThreadArray == NULL) 
        return -3;

	L_serverReply = (char*)malloc(2);
	L_serverReply = strcpy(L_serverReply, " \0");

	*MySocket = connectSocket(ip, PORT);
	if(*MySocket == 1)
	{
		free(L_serverReply);
		return -3;
	}
	while (L_serverReply[0] != '0')
		L_serverReply = receiveMessage(*MySocket, L_serverReply, 1);

	free(L_serverReply);
	return *MySocket;
}
