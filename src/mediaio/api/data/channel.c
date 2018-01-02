
#include "channel.h"
#include <stdio.h>

void init_channel(Channel* channel)
{
	channel->data = NULL;
	channel->allocatedSize = 0;
	channel->size = 0;
	channel->sample_rate = 0;
	channel->precision = 0;
	channel->sampleSizeInByte = 0;
}

void resize_channel(Channel* channel, unsigned int requiredSize)
{
	if(channel->allocatedSize == 0)
	{
		// printf("allocate memory %s\n", requiredSize);
		channel->data = malloc(requiredSize);
		channel->allocatedSize = requiredSize;
	}
	else if(channel->allocatedSize < requiredSize)
	{
		// printf("re-allocate memory %s\n", requiredSize);
		channel->data = realloc(channel->data, requiredSize);
		channel->allocatedSize = requiredSize;
	}
	channel->size = requiredSize;
}

void delete_channel(Channel* channel)
{
	if(channel->data)
	{
		// printf("free memory\n");
		free(channel->data);
		init_channel(channel);
	}
}
