#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h> /*FD_SET, FD_ISSET, FD_ZERO macros*/
#include <pthread.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>

typedef struct sockaddr SOCKADDR;
typedef struct opt
{
  char name;
  char* valeur;
  struct opt* nxt;
} opt_s;

typedef struct list
{
  int x;
  int y;
  char state;
  struct list *nxt;
} list_s;

typedef struct
{
  char** map;
  int x;
  int y;
} T_DATA_MAP;

typedef struct
{
  int x;
  int y;
} T_COORDONNES;

typedef struct
{
  int client_socket;
  int pv;
  char nom;
  int nb_bombe;
  int flagdead;
  list_s *queue_bomb;
  T_COORDONNES coordonnees;
  T_COORDONNES last_coordonnees;
  T_DATA_MAP* l_donnees_map;
} T_CLIENT;

typedef struct
{
  struct sockaddr_in address;
  int addrlen;
  int master_socket;
  fd_set readfds;
  int l_etat_partie;
} T_INFOS_CONNEXION;

#define TRUE   1
#define FALSE  0

#define TIMEOUT_SEC 3
#define TIMEOUT_USEC 0

extern int ETAT_PARTIE;
extern int NOMBRE_JOUEUR;

int my_tablen(char tab[]);
int my_putstr(char *str);
void my_putchar(char c);
void my_put_nbr(int n);
opt_s* ajoutArg(int argc, char** argv);
opt_s* my_getopt(int argc, char** argv, char* format);
int addPort(opt_s* option);
opt_s* delListe(opt_s* liste);
T_DATA_MAP initialisationMap(T_DATA_MAP p_data_map, int x, int y);
T_DATA_MAP initialisationMap2(T_DATA_MAP p_data_map, int x, int y);
T_DATA_MAP initialisationMap3(T_DATA_MAP p_data_map, int x, int y);
void init_orientation(T_CLIENT* l_all_clients, int x, int y, T_DATA_MAP data_map, opt_s* option);
T_COORDONNES initialiseCoordonnes(int i, int x, int y);
void freeMap(T_DATA_MAP p_data_map);
T_INFOS_CONNEXION initConnexionTcp(opt_s* option);
void launchGame(T_INFOS_CONNEXION l_infos_connexion, T_CLIENT* l_all_clients, int i, T_DATA_MAP data_map);
int waitingClientConnexion(/*int activity, */T_INFOS_CONNEXION p_infos_connexion, T_CLIENT* l_all_clients);
void messageReceivedFromClient(T_CLIENT* l_all_clients,T_INFOS_CONNEXION* p_infos_connexion, T_DATA_MAP* data_map);
void gestionCommandeRecu(char* p_buffer, int p_taille_buffer, T_CLIENT* p_socket_client, int index_client_recu, T_DATA_MAP* data_map);
void SendMap(T_CLIENT* p_socket_client, int index_client_recu, T_DATA_MAP* data_map);
void Up(T_CLIENT* p_socket_client, T_DATA_MAP* data_map);
void Down(T_CLIENT* p_socket_client, T_DATA_MAP* data_map);
void Right(T_CLIENT* p_socket_client, T_DATA_MAP* data_map);
void Left(T_CLIENT* p_socket_client, T_DATA_MAP* data_map);
list_s* createList(int coord1, int coord2);
list_s* rmElmt(list_s* listchain, int coord1, int coord2);
list_s* addEnd(list_s* listchain, int coord1, int coord2);
list_s* delList2(list_s* listchain);
list_s* findElmt(list_s* listchain, char etat);
void BombDrop(T_CLIENT* p_socket_client, T_DATA_MAP* data_map);
void FinExplosion(T_CLIENT* p_socket_client, T_DATA_MAP* data_map);
void ExplosionBombe(T_CLIENT* all_socket_client, T_CLIENT* p_socket_client, T_DATA_MAP* data_map);
void IsDie(T_CLIENT* p_socket_client);
