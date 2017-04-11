#ifndef _MEDIAIO_API_FILTER_FILTER_H_
#define _MEDIAIO_API_FILTER_FILTER_H_

#include <mediaio/api/common/plugin.h>
#include <mediaio/api/data/frame.h>
#include <mediaio/api/metadata/metadata.h>

typedef MediaioStatus (ConfigureEntryPoint) (void* handle, const Metadata* parameters);
typedef MediaioStatus (FilterEntryPoint)    (void* handle, const Frame* inputFrame, Frame* outputFrame);

typedef struct MediaioPluginFilter
{
	ConfigureEntryPoint* configure;
	FilterEntryPoint*    process;
} MediaioPluginFilter;

#endif
