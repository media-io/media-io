#ifndef _MEDIAIO_API_INSTANCE_INSTANCE_H_
#define _MEDIAIO_API_INSTANCE_INSTANCE_H_

#include <mediaio/api/common/plugin.h>

typedef MediaioStatus (CreateInstancePoint) (void** handle);
typedef MediaioStatus (DeleteInstancePoint) (void** handle);

typedef struct MediaioPluginInstance
{
	CreateInstancePoint* create_instance;
	DeleteInstancePoint* delete_instance;
} MediaioPluginInstance;

#endif
