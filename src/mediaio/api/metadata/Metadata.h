#ifndef _MEDIAIO_API_METADATA_METADATA_H_
#define _MEDIAIO_API_METADATA_METADATA_H_

#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define kMediaioMetadataApi "MediaioMetadataApi"

enum EMetadataType
{
	eMetadataTypeNone = 0,
	eMetadataTypeEnd,
	eMetadataTypeBool,
	eMetadataTypeUint8,
	eMetadataTypeInt8,
	eMetadataTypeUint16,
	eMetadataTypeInt16,
	eMetadataTypeUint32,
	eMetadataTypeInt32,
	eMetadataTypeUint64,
	eMetadataTypeInt64,
	eMetadataTypeHalf,
	eMetadataTypeFloat,
	eMetadataTypeDouble,

	eMetadataTypeString,
	eMetadataTypeRatio,

	eMetadataTypeGroup,
};

typedef struct Metadata
{
	const char*   id;
	const char*   label;
	const char*   unit;
	const char*   mapped;
	enum EMetadataType type;
	void*         data;
} Metadata;

void init_metadata(Metadata* metadata);

#ifdef __cplusplus
}
#endif

#endif
