
#include "codecs.h"
#include <string.h>

const char* get_codec_str(enum MediaioStreamCodec codec)
{
	switch(codec)
	{
		case MediaioStreamCodecUnknown:  return kMediaioStreamCodecUnknown;
		case MediaioStreamCodecMpeg2:    return kMediaioStreamCodecMpeg2;
		case MediaioStreamCodecH264:     return kMediaioStreamCodecH264;
		case MediaioStreamCodecJpeg2000: return kMediaioStreamCodecJpeg2000;
		case MediaioStreamCodecPCM:      return kMediaioStreamCodecPCM;
	}
}
