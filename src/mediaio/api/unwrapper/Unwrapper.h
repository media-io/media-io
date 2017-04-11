#ifndef _MEDIAIO_API_UNWRAPPER_UNWRAPPER_H_
#define _MEDIAIO_API_UNWRAPPER_UNWRAPPER_H_

#include <mediaio/api/common/plugin.h>
#include <mediaio/api/data/coded_data.h>
#include <mediaio/api/metadata/metadata.h>
#include <mediaio/api/reader/reader.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef MediaioStatus (SetReaderEntryPoint) (void* handle, MediaioPluginReader* reader, void* readerHandle);
typedef MediaioStatus (ConfigureEntryPoint) (void* handle, const Metadata* parameters);
typedef MediaioStatus (UnwrapEntryPoint)    (void* handle, const int streamIndex, CodedData* unwrappedFrame);
typedef MediaioStatus (SeekFrameEntryPoint) (void* handle, const int frame);
typedef MediaioStatus (SeekTimeEntryPoint)  (void* handle, const double time);

typedef struct MediaioPluginUnwrapper
{
	SetReaderEntryPoint* set_reader;
	ConfigureEntryPoint* configure;
	UnwrapEntryPoint*    unwrap_next_frame;
	SeekFrameEntryPoint* seek_at_frame;
	SeekTimeEntryPoint*  seek_at_time;
} MediaioPluginUnwrapper;

#ifdef __cplusplus
}
#endif

#endif
