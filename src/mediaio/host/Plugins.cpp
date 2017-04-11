#include "Plugins.hpp"

#include <iostream>
#include <cstring>
#include <stdexcept>

Plugins::Plugins()
{
	_pluginLoader.scanPluginFiles();
}

Plugins::~Plugins()
{}

std::vector<MediaioPlugin*> Plugins::getPlugins() const
{
	return _pluginLoader.getPlugins();
}

MediaioPlugin& Plugins::getPlugin( const std::string& pluginId, const std::string& context ) const
{
	const std::vector< MediaioPlugin* >& plugins = _pluginLoader.getPlugins();
	for(auto plugin: plugins)
	{
		if(!strcmp(plugin->plugin_api, context.c_str()) &&
			pluginId == plugin->plugin_identifier)
		{
			return *plugin;
		}
	}
	throw std::runtime_error("unable to found plugin named " + pluginId);
}

MediaioPlugin& Plugins::searchPlugin(const std::string& partialPluginId, const std::string& context) const
{
	const std::vector< MediaioPlugin* >& plugins = _pluginLoader.getPlugins();
	for(auto plugin : plugins)
	{
		std::string pluginId = plugin->plugin_identifier;
		if(!strcmp(plugin->plugin_api, context.c_str()) &&
			(pluginId.find(partialPluginId) != std::string::npos))
		{
			return *plugin;
		}
	}
	throw std::runtime_error("unable to found plugin with pattern " + partialPluginId);
}
