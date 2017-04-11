#ifndef _MEDIAIO_HOST_PLUGIN_LOADER_HPP_
#define _MEDIAIO_HOST_PLUGIN_LOADER_HPP_

#include <mediaio/api/common/plugin.h>
#include <string>
#include <vector>
#include <list>
#include <set>

class PluginBinary;

class PluginLoader
{
public:
	PluginLoader();
	~PluginLoader();

	void scanPluginFiles();

	const std::vector<MediaioPlugin*>& getPlugins() const
	{
		return _plugins;
	}

private:
	std::list< std::string >      _pluginPath;
	std::list< std::string >      _pluginDirs;
	std::list< PluginBinary* >    _binaries;       ///< all the binaries we know about, we own these
	std::vector< MediaioPlugin* > _plugins;        ///< all the plugins inside the binaries, we don't own these, populated from _binaries
	std::set< std::string >       _knownBinFiles;

	void scanDirectory(std::set<std::string> &foundBinFiles, const std::string &dir, bool recurse);
};

#endif
