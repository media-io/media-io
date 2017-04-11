#ifndef _MEDIAIO_API_WRITER_WRITER_H_
#define _MEDIAIO_API_WRITER_WRITER_H_

#include <mediaio/api/common/plugin.h>

typedef MediaioStatus (SetFilenameEntryPoint)  (void* handle, const char* filename);
typedef const char*   (GetFilenameEntryPoint)  (void* handle);
typedef MediaioStatus (OpenEntryPoint)         (void* handle);
typedef MediaioStatus (CloseEntryPoint)        (void* handle);
typedef uint64_t      (GetPositionEntryPoint)  (void* handle);
typedef uint64_t      (WriteEntryPoint)        (void* handle, const char* data, const uint64_t size);
typedef MediaioStatus (SeekEntryPoint)         (void* handle, const int64_t size);

typedef struct MediaioPluginWriter
{
	SetFilenameEntryPoint*  set_filename;
	GetFilenameEntryPoint*  get_filename;
	OpenEntryPoint*         open;
	CloseEntryPoint*        close;
	GetPositionEntryPoint*  getPosition;
	WriteEntryPoint*        write;
	SeekEntryPoint*         seek;
} MediaioPluginWriter;

#endif
