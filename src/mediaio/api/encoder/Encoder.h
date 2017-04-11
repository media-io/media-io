#ifndef _MEDIAIO_API_ENCODER_ENCODER_H_
#define _MEDIAIO_API_ENCODER_ENCODER_H_

#include <mediaio/api/common/plugin.h>
#include <mediaio/api/data/coded_data.h>
#include <mediaio/api/data/frame.h>
#include <mediaio/api/metadata/metadata.h>

typedef MediaioStatus (ConfigureEntryPoint)    (void* handle, const Metadata* parameters);
typedef MediaioStatus (EncodeEntryPoint)       (void* handle, Frame* decodedFrame, CodedData* unwrappedFrame);
typedef Metadata*     (GetMetadatasEntryPoint) (void* handle);

typedef struct MediaioPluginEncoder
{
	ConfigureEntryPoint*    configure;
	EncodeEntryPoint*       encode;
	GetMetadatasEntryPoint* get_metadatas;
} MediaioPluginEncoder;

#endif
