#ifndef __AUDIOFILTER_H__
#define __AUDIOFILTER_H__

#include <SDL/SDL.h>

#ifdef __cplusplus
extern "C" {
#endif

void AudioFilter(Sint16 *data, int samples);
void AudioFilterInit();

#ifdef __cplusplus
}
#endif


#endif//__AUDIOFILTER_H__