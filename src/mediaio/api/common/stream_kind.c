
#include "stream_kind.h"
#include <string.h>

const char* get_stream_kind_str(enum MediaioStreamKind kind)
{
	switch(kind)
	{
		case MediaioStreamKindUnknown:  return kMediaioStreamKindUnknown;
		case MediaioStreamKindImage:    return kMediaioStreamKindImage;
		case MediaioStreamKindAudio:    return kMediaioStreamKindAudio;
		case MediaioStreamKindSubtitle: return kMediaioStreamKindSubtitle;
		case MediaioStreamKindData:     return kMediaioStreamKindData;
	}
}

const char get_stream_kind_letter(enum MediaioStreamKind kind)
{
	switch(kind)
	{
		case MediaioStreamKindUnknown:  return 'U';
		case MediaioStreamKindImage:    return 'I';
		case MediaioStreamKindAudio:    return 'A';
		case MediaioStreamKindSubtitle: return 'S';
		case MediaioStreamKindData:     return 'D';
	}
}
