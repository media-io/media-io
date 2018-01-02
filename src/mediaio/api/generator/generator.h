#ifndef _MEDIAIO_API_GENERATOR_GENERATOR_H_
#define _MEDIAIO_API_GENERATOR_GENERATOR_H_

#include <mediaio/api/common/plugin.h>
#include <mediaio/api/data/image_frame.h>
#include <mediaio/api/metadata/metadata.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef MediaioStatus (ConfigureEntryPoint) (void* handle, const Metadata* parameters);
typedef MediaioStatus (GeneratorEntryPoint) (void* handle, ImageFrame* decodedFrame);

typedef struct MediaioPluginGenerator
{
	ConfigureEntryPoint* configure;
	GeneratorEntryPoint* generate;
} MediaioPluginGenerator;

#ifdef __cplusplus
}
#endif

#endif
