#ifndef _MEDIAIO_HOST_C_PLUGINS_HPP_
#define _MEDIAIO_HOST_C_PLUGINS_HPP_

#include <mediaio/api/common/plugin.h>

#ifdef __cplusplus
extern "C" {
#endif

int             get_plugin_count();
MediaioPlugin** get_plugins();

MediaioPlugin*  get_plugin(const char* partialPluginId, const char* context);
MediaioPlugin*  search_plugin(const char* partialPluginId, const char* context);

#ifdef __cplusplus
}
#endif

#endif