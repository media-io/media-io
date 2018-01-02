#ifndef _MEDIAIO_API_DESCRIPTOR_STREAM_H_
#define _MEDIAIO_API_DESCRIPTOR_STREAM_H_

#include <mediaio/api/common/common.h>
#include <mediaio/api/common/stream_kind.h>
#include <mediaio/api/common/codecs.h>

typedef struct MediaioImageStreamDescriptor
{
	int width;
	int height;
} MediaioImageStreamDescriptor;

typedef struct MediaioAudioStreamDescriptor
{
	int channel_count;
	int sample_rate_num;
	int sample_rate_den;
	int container_duration;
	int quantization_bits;
} MediaioAudioStreamDescriptor;

typedef struct MediaioStreamDescriptor
{
	MediaioStreamCodec codec;
	MediaioStreamKind kind;
	MediaioImageStreamDescriptor* image;
	MediaioAudioStreamDescriptor* audio;
} MediaioStreamDescriptor;

#endif
