#include "constantes.h"


int musique()
{
	static const char *MY_COOL_MP3 = "Medias/backgroundMusic.wav";
	int result = 0;
    int flags = MIX_INIT_MP3;
	Mix_Music *music;

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Failed to init SDL\n");
        exit(1);
    }

    if (flags != (result = Mix_Init(flags))) {
        printf("Could not initialize mixer (result: %d).\n", result);
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(1);
    }

    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    music = Mix_LoadMUS(MY_COOL_MP3);
    Mix_PlayMusic(music, 1);

    while (!SDL_QuitRequested()) {
        SDL_Delay(250);
    }

    Mix_FreeMusic(music);
    SDL_Quit();
	return 0;
}

//Thread de gestion de la musique en arriere plan
DWORD WINAPI ThreadMusic(void* data) { 
	
	while (l_COMPTEUR >= 0)
	{
			musique();
			Sleep(1000);
	}

  return 0;
}