#ifndef __SDL_DIBAUDIOIN_H__
#define __SDL_DIBAUDIOIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <SDL/SDL.h>

int SDL_OpenAudioIn(SDL_AudioSpec *requested, SDL_AudioSpec *result);
void SDL_CloseAudioIn();
void SDL_PauseAudioIn(int pause);

#ifdef __cplusplus
}
#endif


#endif