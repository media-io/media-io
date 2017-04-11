#ifndef _MEDIAIO_API_ANALYSER_ANALYSER_H_
#define _MEDIAIO_API_ANALYSER_ANALYSER_H_

#include <mediaio/api/common/plugin.h>
#include <mediaio/api/data/frame.h>
#include <mediaio/api/metadata/metadata.h>

typedef Metadata* (AnalyseEntryPoint)(void* handle, const Frame* decodedFrames, const int numberOfFrames);

typedef struct MediaioPluginAnalyser
{
	AnalyseEntryPoint* analyse;
} MediaioPluginAnalyser;

#endif
