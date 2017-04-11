#ifndef _MEDIAIO_API_COMMON_PLUGIN_H_
#define _MEDIAIO_API_COMMON_PLUGIN_H_

#include <mediaio/api/common/common.h>
#include <mediaio/api/common/api.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* (PluginActionPoint)(const char* action);

typedef struct MediaioPlugin
{
	const char*  plugin_api;
	int          api_version;
	const char*  plugin_identifier;
	const char*  plugin_label;
	const char*  plugin_description;
	unsigned int plugin_version_major;
	unsigned int plugin_version_minor;

	PluginActionPoint* action_entry;
} MediaioPlugin;

#ifdef __cplusplus
}
#endif

#endif
