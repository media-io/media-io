#ifndef _MEDIAIO_API_READER_READER_H_
#define _MEDIAIO_API_READER_READER_H_

#include <mediaio/api/common/plugin.h>

typedef MediaioStatus (SetFilenameEntryPoint)  (void* handle, const char* filename);
typedef const char*   (GetFilenameEntryPoint)  (void* handle);
typedef MediaioStatus (OpenEntryPoint)         (void* handle);
typedef MediaioStatus (CloseEntryPoint)        (void* handle);
typedef int64_t       (GetSizeEntryPoint)      (void* handle);
typedef MediaioStatus (SetCacheEntryPoint)     (void* handle, const uint64_t size);
typedef uint64_t      (GetCacheEntryPoint)     (void* handle);
typedef uint64_t      (GetPositionEntryPoint)  (void* handle);
typedef uint64_t      (ReadEntryPoint)         (void* handle, char* data, const uint64_t size);
typedef MediaioStatus (SeekEntryPoint)         (void* handle, const int64_t size);

typedef struct MediaioPluginReader
{
	SetFilenameEntryPoint*  set_filename;
	GetFilenameEntryPoint*  get_filename;
	OpenEntryPoint*         open;
	CloseEntryPoint*        close;
	GetSizeEntryPoint*      get_size;
	SetCacheEntryPoint*     set_cache_size;
	GetCacheEntryPoint*     get_cache_size;
	GetPositionEntryPoint*  get_position;
	ReadEntryPoint*         read;
	SeekEntryPoint*         seek;
} MediaioPluginReader;

#endif
