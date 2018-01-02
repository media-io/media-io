#ifndef _MEDIAIO_API_ENCODER_ENCODER_H_
#define _MEDIAIO_API_ENCODER_ENCODER_H_

#include <mediaio/api/common/plugin.h>
#include <mediaio/api/data/coded_data.h>
#include <mediaio/api/data/audio_frame.h>
#include <mediaio/api/data/image_frame.h>
#include <mediaio/api/metadata/metadata.h>

typedef MediaioStatus (ConfigureEntryPoint)    (void* handle, const Metadata* parameters);
typedef MediaioStatus (EncodeImageEntryPoint)  (void* handle, ImageFrame* frame, CodedData* data);
typedef MediaioStatus (EncodeAudioEntryPoint)  (void* handle, AudioFrame* frame, CodedData* data);
typedef Metadata*     (GetMetadatasEntryPoint) (void* handle);

typedef struct MediaioPluginImageEncoder
{
	ConfigureEntryPoint*    configure;
	EncodeImageEntryPoint*  encode_image;
	GetMetadatasEntryPoint* get_metadatas;
} MediaioPluginImageEncoder;

typedef struct MediaioPluginAudioEncoder
{
	ConfigureEntryPoint*    configure;
	EncodeAudioEntryPoint*  encode_audio;
	GetMetadatasEntryPoint* get_metadatas;
} MediaioPluginAudioEncoder;

#endif
