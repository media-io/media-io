
#include "PluginBinary.hpp"

#include <iostream>
#include <iomanip>
#include <cassert>

void PluginBinary::loadPluginInfo(PluginLoader *cache)
{
	_fileModificationTime = _binary.getTime();
	_fileSize = _binary.getSize();
	_binaryChanged = false;
	
	_binary.load();

	int (*getNoRs)() = (int(*)()) _binary.findSymbol("mediaio_get_number_of_plugins");
	MediaioPlugin* (*getPlugRs)(int) = (MediaioPlugin*(*)(int)) _binary.findSymbol("mediaio_get_plugin");

	if(getNoRs != 0 && getPlugRs != 0)
	{
		int pluginCountRs = (*getNoRs)();
		_plugins.reserve(pluginCountRs);

		for( int index = 0; index < pluginCountRs; ++index )
		{
			MediaioPlugin* plugin = (*getPlugRs)(index);
			_plugins.push_back( plugin );
		}
	}
}

PluginBinary::~PluginBinary()
{
	_binary.unload();
}
