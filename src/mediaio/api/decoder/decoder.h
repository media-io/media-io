#ifndef _MEDIAIO_API_DECODER_DECODER_H_
#define _MEDIAIO_API_DECODER_DECODER_H_

#include <mediaio/api/common/plugin.h>
#include <mediaio/api/data/coded_data.h>
#include <mediaio/api/data/frame.h>
#include <mediaio/api/metadata/metadata.h>

typedef MediaioStatus (ConfigureEntryPoint)    (void* handle, const Metadata* parameters);
typedef MediaioStatus (DecodeEntryPoint)       (void* handle, CodedData* unwrappedFrame, Frame* decodedFrame);
typedef Metadata*     (GetMetadatasEntryPoint) (void* handle);

typedef struct MediaioPluginDecoder
{
	ConfigureEntryPoint*    configure;
	DecodeEntryPoint*       decode;
	GetMetadatasEntryPoint* get_metadatas;
} MediaioPluginDecoder;

#endif
