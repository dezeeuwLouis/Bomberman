#include "constantes.h"

//Thread permettant de gérer l'explosion et l'animation de la bombe
DWORD WINAPI ThreadGameEngine(void* data) { 
	
	int l_retour;

	char* P_Message = NULL;
	P_Message = (char*)malloc(1);
	P_Message[0] = ' ';
	P_Message[1] = '\0';
	while (l_COMPTEUR >= 0)
	{
		if (l_COMPTEUR != 0)
		{
			//On attend 5 secondes
			Sleep(3000);
			//On envoie l'explosion
			P_Message[0] = '6';
			//l_retour = sendMessage((SOCKET)data, P_Message);
			l_retour = sendMessage(*((SOCKET*)data), P_Message);
			//l_retour = sendMessage(MySocket, P_Message);
			Sleep(1000);
			P_Message[0] = '7';
			//l_retour = sendMessage(MySocket, P_Message);
			l_retour = sendMessage(*((SOCKET*)data), P_Message);
			l_COMPTEUR--;
		}
	}
	free(P_Message);
  return 0;
}