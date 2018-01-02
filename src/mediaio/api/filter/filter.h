#ifndef _MEDIAIO_API_FILTER_FILTER_H_
#define _MEDIAIO_API_FILTER_FILTER_H_

#include <mediaio/api/common/plugin.h>
#include <mediaio/api/data/audio_frame.h>
#include <mediaio/api/data/image_frame.h>
#include <mediaio/api/metadata/metadata.h>

typedef MediaioStatus (ConfigureEntryPoint) (void* handle, const Metadata* parameters);
typedef MediaioStatus (FilterAudioEntryPoint)    (void* handle, const AudioFrame* inputFrame, AudioFrame* outputFrame);
typedef MediaioStatus (FilterImageEntryPoint)    (void* handle, const ImageFrame* inputFrame, ImageFrame* outputFrame);

typedef struct MediaioPluginAudioFilter
{
	ConfigureEntryPoint*   configure;
	FilterAudioEntryPoint* process_audio;
} MediaioPluginAudioFilter;

typedef struct MediaioPluginImageFilter
{
	ConfigureEntryPoint*   configure;
	FilterImageEntryPoint* process_image;
} MediaioPluginImageFilter;

#endif
