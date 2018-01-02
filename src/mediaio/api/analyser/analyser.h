#ifndef _MEDIAIO_API_ANALYSER_ANALYSER_H_
#define _MEDIAIO_API_ANALYSER_ANALYSER_H_

#include <mediaio/api/common/plugin.h>
#include <mediaio/api/data/image_frame.h>
#include <mediaio/api/metadata/metadata.h>

typedef Metadata* (AnalyseEntryPoint)(void* handle, const ImageFrame* decodedFrames, const int numberOfFrames);

typedef struct MediaioPluginAnalyser
{
	AnalyseEntryPoint* analyse;
} MediaioPluginAnalyser;

#endif
