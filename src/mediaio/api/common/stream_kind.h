#ifndef _MEDIAIO_API_COMMON_STREAM_KIND_H_
#define _MEDIAIO_API_COMMON_STREAM_KIND_H_

#ifdef __cplusplus
extern "C" {
#endif

#define kMediaioStreamKindUnknown  "unknown";
#define kMediaioStreamKindImage    "image";
#define kMediaioStreamKindAudio    "audio";
#define kMediaioStreamKindSubtitle "subtitle";
#define kMediaioStreamKindData     "data";

typedef enum MediaioStreamKind
{
	MediaioStreamKindUnknown = 0,
	MediaioStreamKindImage,
	MediaioStreamKindAudio,
	MediaioStreamKindSubtitle,
	MediaioStreamKindData,
} MediaioStreamKind;

const char* get_stream_kind_str(enum MediaioStreamKind kind);
const char get_stream_kind_letter(enum MediaioStreamKind kind);

#ifdef __cplusplus
}
#endif

#endif
