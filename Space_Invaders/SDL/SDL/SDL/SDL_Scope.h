#ifndef __SDL_SCOPE_H__
#define __SDL_SCOPE_H__

#include "SDL_dibaudioIn.h"

#ifdef __cplusplus
extern "C" {
#endif

//Duh, but for the sake of clarity
#define TICKS_PER_SECOND 1000

/*
 *	Dirt-simple fixed point # macros
 *	TO_FXP(x) converts an integer to a fixed-point integer, FROM_FXP(x) does
 *	the reverse.  FXP_MUL and FXP_DIV are only used when multiplying/dividing
 *	two fixed point #s.
 *
 */

#define MAX_FXP 65535
#define TO_FXP(x)		( ((Uint32)(x)) <<16)
#define FROM_FXP(x)		( ((Uint32)(x)) >>16)
#define FXP_MUL(x,y)	((Uint32)(( ((Uint64)(x)) * ((Uint64)(y)) ) >> 16))
#define FXP_DIV(x,y)	(( ((Uint32)(x)) / ((Uint32)(y)) ) << 16)
typedef Uint32 FXP;


#define AUDIO_SAMPLERATE		11025
#define AUDIO_SAMPLES			64
#define AUDIO_FORMAT			AUDIO_S16
#define SAMPLES_PER_TICK		(AUDIO_SAMPLERATE/TICKS_PER_SECOND)
#define FXP_TICKS_PER_SAMPLE	(TO_FXP(TICKS_PER_SECOND)/AUDIO_SAMPLERATE)

int UpdateScreen();
void SoundInCallback(void *udata, Uint8 *stream, int len);

typedef struct
{
	Uint8 *buf;
	Uint8 bytesPerSample;
	Uint32 len;
	Uint32 prevTick;

} SoundInfo;


#ifdef __cplusplus
}
#endif


#endif//__SDL_SCOPE_H__