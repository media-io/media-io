
#include "audio_frame.h"

void init_audio_frame(struct AudioFrame* frame)
{
	frame->channels = NULL;
	frame->numberOfChannels = 0;
}

void create_channels(struct AudioFrame* frame, unsigned int required_channels)
{
	if(frame->numberOfChannels == 0)
	{
		frame->channels = (Channel*) malloc(required_channels * sizeof(Channel));
		frame->numberOfChannels = required_channels;
	}
	else
	{
		unsigned int index = 0;
		for(index = 0; index < frame->numberOfChannels; ++index)
		{
			delete_channel(&frame->channels[index]);
		}
		frame->channels = (Channel*)realloc(frame->channels, required_channels * sizeof(Channel));
		frame->numberOfChannels = required_channels;
	}

	unsigned int index = 0;
	for(index = 0; index < required_channels; ++index)
	{
		init_channel(&frame->channels[index]);
	}
}

void delete_audio_frame(struct AudioFrame* frame)
{
	if(frame->channels)
	{
		unsigned int index = 0;
		for(index = 0; index < frame->numberOfChannels; ++index)
		{
			delete_channel(&frame->channels[index]);
		}
		free(frame->channels);
		init_audio_frame(frame);
	}
}
