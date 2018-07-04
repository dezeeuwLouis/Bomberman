#include "constantes.h"

int main(int argc , char *argv[])
{
	int l_result = 0;
	int a, b, c, d;
	int t = 0;
	int success = 0;
	char name[50];
	char ip[50];
	int len;

	//Gestion du nom et des IPs
	while (success < 4)
	{
		printf("Enter name:\n");
		fgets(name,11,stdin);
		len = strlen(name);
		printf("Enter Ip:\n");
		fgets(ip,15,stdin);
		len = strlen(ip);
		success = sscanf(ip, "%i.%i.%i.%i", &a, &b, &c, &d);
	}

	//Lancement des menus
	l_result = first_menu();
	if (l_result == -1)
		return 0;
	l_result = 0;
	l_COMPTEUR = 0;

	//Lancement de la boucle de jeu
	l_result = LaunchGame(NULL, 0, name, ip);		

	//Si -3 On a perdu
	if (l_result == -1)
		attenteFinJeu("Perdu", 0);
	//Si -2 on a gagné
	if (l_result == -2)
		attenteFinJeu("Gagne", 1);

  return 0;
}