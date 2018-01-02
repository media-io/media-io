#ifndef _MEDIAIO_API_DECODER_DECODER_H_
#define _MEDIAIO_API_DECODER_DECODER_H_

#include <mediaio/api/common/plugin.h>
#include <mediaio/api/data/coded_data.h>
#include <mediaio/api/data/audio_frame.h>
#include <mediaio/api/data/image_frame.h>
#include <mediaio/api/metadata/metadata.h>

typedef MediaioStatus (ConfigureEntryPoint)    (void* handle, const Metadata* parameters);
typedef MediaioStatus (DecodeImageEntryPoint)  (void* handle, CodedData* data, ImageFrame* frame);
typedef MediaioStatus (DecodeAudioEntryPoint)  (void* handle, CodedData* data, AudioFrame* frame);
typedef Metadata*     (GetMetadatasEntryPoint) (void* handle);

typedef struct MediaioPluginImageDecoder
{
	ConfigureEntryPoint*    configure;
	DecodeImageEntryPoint*  decode_image;
	GetMetadatasEntryPoint* get_metadatas;
} MediaioPluginImageDecoder;

typedef struct MediaioPluginAudioDecoder
{
	ConfigureEntryPoint*    configure;
	DecodeAudioEntryPoint*  decode_audio;
	GetMetadatasEntryPoint* get_metadatas;
} MediaioPluginAudioDecoder;

#endif
