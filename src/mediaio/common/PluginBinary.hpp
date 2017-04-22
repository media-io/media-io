#ifndef _MEDIAIOP_API_COMMON_PLUGINBINARY_HPP_
#define _MEDIAIOP_API_COMMON_PLUGINBINARY_HPP_

#include <string>
#include <vector>

#include "Binary.hpp"
#include <mediaio/api/common/plugin.h>

using namespace mediaio::common;

class PluginLoader;

class PluginBinary
{
public:

	/// create one from the cache.  this will invoke the Binary() constructor which
	/// will stat() the file.
	explicit PluginBinary(const std::string& file, const std::string& bundlePath, time_t mtime, size_t size)
		: _binary(file)
		, _filePath(file)
		, _bundlePath(bundlePath)
		, _fileModificationTime(mtime)
		, _fileSize(size)
		, _binaryChanged(false)
	{
		if (_fileModificationTime != _binary.getTime() ||
			_fileSize != _binary.getSize())
		{
			_binaryChanged = true;
		}
	}


	/// constructor which will open a library file, call things inside it, and then 
	/// create Plugin objects as appropriate for the plugins exported therefrom
	explicit PluginBinary(const std::string& file, const std::string& bundlePath, PluginLoader* cache)
		: _binary(file)
		, _filePath(file)
		, _bundlePath(bundlePath)
		, _binaryChanged(false)
	{
		loadPluginInfo(cache);
	}

	virtual ~PluginBinary();


	time_t getFileModificationTime() const
	{
		return _fileModificationTime;
	}

	size_t getFileSize()
	{
		return _fileSize;
	}

	const std::string &getFilePath() const
	{
		return _filePath;
	}

	const std::string &getBundlePath() const
	{
		return _bundlePath;
	}

	bool hasBinaryChanged() const
	{
		return _binaryChanged;
	}

	bool isLoaded() const
	{
		return _binary.isLoaded();
	}

	void loadPluginInfo(PluginLoader *);

	int getNPlugins() const
	{
		return (int)_plugins.size();
	}

	MediaioPlugin& getPlugin(int index)
	{
		return *_plugins.at(index);
	}

	const MediaioPlugin& getPlugin(int index) const
	{
		return *_plugins.at(index);
	}

protected:
	Binary _binary;                 ///< our binary object, abstracted layer ontop of OS calls, defined in ofxhBinary.h
	std::string _filePath;          ///< full path to the file
	std::string _bundlePath;        ///< path to the .bundle directory
	std::vector< MediaioPlugin* > _plugins; ///< my plugins
	time_t _fileModificationTime;   ///< used as a time stamp to check modification times, used for caching
	size_t _fileSize;               ///< file size last time we check, used for caching
	bool _binaryChanged;            ///< whether the timestamp/filesize in this cache is different from that in the actual binary
};

#endif
