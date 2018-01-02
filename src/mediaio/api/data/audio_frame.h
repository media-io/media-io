#ifndef _MEDIAIO_API_DATA_AUDIO_FRAME_H_
#define _MEDIAIO_API_DATA_AUDIO_FRAME_H_

#include <stddef.h>
#include <stdlib.h>
#include "channel.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AudioFrame
{
	Channel*     channels;
	unsigned int numberOfChannels;
} AudioFrame;


void init_audio_frame(struct AudioFrame* frame);
void create_channels(struct AudioFrame* frame, unsigned int required_components);
void delete_audio_frame(struct AudioFrame* frame);

#ifdef __cplusplus
}
#endif

#endif
