#ifndef _MEDIAIO_API_COMMON_CODECS_H_
#define _MEDIAIO_API_COMMON_CODECS_H_

#ifdef __cplusplus
extern "C" {
#endif

#define kMediaioStreamCodecUnknown  "unknown";
#define kMediaioStreamCodecMpeg2    "MPEG 2";
#define kMediaioStreamCodecH264     "H.264";
#define kMediaioStreamCodecJpeg2000 "Jpeg2000";
#define kMediaioStreamCodecPCM      "PCM";

typedef enum MediaioStreamCodec
{
	MediaioStreamCodecUnknown = 0,
	MediaioStreamCodecMpeg2,
	MediaioStreamCodecH264,
	MediaioStreamCodecJpeg2000,
	MediaioStreamCodecPCM,
} MediaioStreamCodec;

const char* get_codec_str(enum MediaioStreamCodec codec);

#ifdef __cplusplus
}
#endif

#endif
