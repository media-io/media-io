
#include <mediaio/host/Plugins.hpp>

#include "plugins.h"

static Plugins plugins;

int get_plugin_count()
{
	return plugins.getPlugins().size();
}

MediaioPlugin** get_plugins()
{
	return &plugins.getPlugins()[0];
}

MediaioPlugin* get_plugin(const char* partialPluginId, const char* context)
{
	std::string pattern(partialPluginId);
	std::string c(context);

	try
	{
		MediaioPlugin& plug = plugins.getPlugin(pattern, c);
		return &plug;
	}
	catch(...)
	{
		return NULL;
	}
}

MediaioPlugin* search_plugin(const char* partialPluginId, const char* context)
{
	std::string pattern(partialPluginId);
	std::string c(context);

	try
	{
		MediaioPlugin& p = plugins.searchPlugin(pattern, c);
		return &p;
	}
	catch(...)
	{
		return NULL;
	}
	return nullptr;
}
