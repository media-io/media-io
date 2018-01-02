#ifndef _MEDIAIO_API_DATA_CHANNEL_H_
#define _MEDIAIO_API_DATA_CHANNEL_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Channel
{
	void*        data;
	unsigned int allocatedSize;
	unsigned int size;
	unsigned int sample_rate;
	unsigned int precision;
	unsigned int sampleSizeInByte;

} Channel;

void init_channel(Channel* channel);
void resize_channel(Channel* channel, unsigned int requiredSize);
void delete_channel(Channel* channel);

#ifdef __cplusplus
}
#endif

#endif
