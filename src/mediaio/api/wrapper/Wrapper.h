#ifndef _MEDIAIO_API_WRAPPER_WRAPPER_H_
#define _MEDIAIO_API_WRAPPER_WRAPPER_H_

#include <mediaio/api/common/plugin.h>
#include <mediaio/api/data/coded_data.h>
#include <mediaio/api/metadata/metadata.h>
#include <mediaio/api/writer/writer.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef MediaioStatus (SetWriterEntryPoint) (void* handle, MediaioPluginWriter* writer, void* writerHandle);
typedef MediaioStatus (ConfigureEntryPoint) (void* handle, const Metadata* parameters);
typedef MediaioStatus (WrapEntryPoint)      (void* handle, const int streamIndex, CodedData* wrappedFrame);

typedef struct MediaioPluginWrapper
{
	SetWriterEntryPoint* set_writer;
	ConfigureEntryPoint* configure;
	WrapEntryPoint*      wrap_next_frame;
} MediaioPluginWrapper;

#ifdef __cplusplus
}
#endif

#endif
