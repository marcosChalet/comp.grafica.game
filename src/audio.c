#include "audio.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

void init_audio() {
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
  Mix_Music *music = Mix_LoadMUS("ost.mp3");
  if (!music) {
    printf("Erro ao carregar a música: %s\n", Mix_GetError());
  }
  Mix_PlayMusic(music, -1); // -1 = loop infinito
}
