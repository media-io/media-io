#ifndef _MEDIAIO_HOST_PLUGINS_HPP_
#define _MEDIAIO_HOST_PLUGINS_HPP_

#include "PluginLoader.hpp"
#include <vector>

class Plugins
{
public:
	Plugins();
	~Plugins();

	std::vector<MediaioPlugin*> getPlugins() const;

	MediaioPlugin& getPlugin(const std::string& pluginId, const std::string& context) const;

	MediaioPlugin& searchPlugin(const std::string& partialPluginId, const std::string& context) const;

private:
	PluginLoader _pluginLoader;
};

#endif