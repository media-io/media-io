
#include "PluginLoader.hpp"
#include <mediaio/common/utils.hpp>
#include <mediaio/common/PluginBinary.hpp>

#include <iostream>
#include <cstring>
// #define PLUGIN_LOADER_DEBUG 1

using namespace mediaio::common;

PluginLoader::PluginLoader()
{
	std::string s = MediaioGetEnv("MEDIAIO_PLUGIN_PATH");
	
	while (s.length())
	{
		int spos = int(s.find_first_of(DIRLIST_SEP_CHARS));
		std::string path;
		
		if (spos != -1)
		{
			path = s.substr(0, spos);
			s = s.substr(spos+1);
		} 
		else
		{
			path = s;
			s = "";
		}
		
		_pluginPath.push_back(path);
	}
	
#if defined(WINDOWS)
	_pluginPath.push_back("C:\\Program Files\\Common Files\\Mediaio\\Plugins");
#endif
#if defined(__linux__)
	_pluginPath.push_back("/usr/Mediaio/Plugins");
#endif
#if defined(__APPLE__)
	_pluginPath.push_back("/Library/Mediaio/Plugins");
#endif
}

PluginLoader::~PluginLoader()
{
}

void PluginLoader::scanPluginFiles()
{
	std::set<std::string> foundBinFiles;

	for( auto paths : _pluginPath )
	{
		scanDirectory(foundBinFiles, paths, false);
	}
}

void PluginLoader::scanDirectory(std::set<std::string> &foundBinFiles, const std::string &dir, bool recurse)
{
#ifdef PLUGIN_LOADER_DEBUG
	std::cout << "looking in " << dir << " for plugins" << std::endl;
#endif

#if defined (WINDOWS)
	WIN32_FIND_DATA findData;
	HANDLE findHandle;
#else
	DIR *d = opendir(dir.c_str());
	if(!d)
	{
		return;
	}
#endif

	_pluginDirs.push_back(dir.c_str());

#if defined (UNIX)
	while (dirent *de = readdir(d))
#elif defined (WINDOWS)
	findHandle = FindFirstFile((dir + "\\*").c_str(), &findData);

	if(findHandle == INVALID_HANDLE_VALUE) 
	{
		return;
	}

	while (1)
#endif
	{
#if defined (UNIX)
		std::string name = de->d_name;
		bool isdir = true;
#else
		std::string name = findData.cFileName;
		bool isdir = (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
#endif
		if(name.find(".miop.bundle") != std::string::npos)
		{
			std::string barename = name.substr(0, name.length() - strlen(".bundle"));
			std::string bundlename = dir + DIRSEP + name;
			std::string binpath = dir + DIRSEP + name + DIRSEP "Contents" DIRSEP + ARCHSTR + DIRSEP + barename;

			foundBinFiles.insert(binpath);

			if(_knownBinFiles.find(binpath) == _knownBinFiles.end())
			{
#ifdef PLUGIN_LOADER_DEBUG
				std::cout << "found binary " << binpath << std::endl;
#endif
				
				PluginBinary* pluginBinary = new PluginBinary(binpath, bundlename, this);
				_binaries.push_back(pluginBinary);
				_knownBinFiles.insert(binpath);
				
				for(int pluginIndex = 0 ; pluginIndex < pluginBinary->getNPlugins(); ++pluginIndex)
				{
					MediaioPlugin* plug = &pluginBinary->getPlugin(pluginIndex);
					_plugins.push_back( plug );
				}
			}
			else
			{
#ifdef PLUGIN_LOADER_DEBUG
				std::cout << "found cached binary " << binpath << std::endl;
#endif
			}
		}
		else
		{
			if(isdir && (recurse && name[0] != '@' && name != "." && name != ".."))
			{
				scanDirectory(foundBinFiles, dir + DIRSEP + name, recurse);
			}
		}
#if defined(WINDOWS)
		int rval = FindNextFile(findHandle, &findData);
		
		if(rval == 0)
		{
			break;
		}
#endif
	}

#if defined(UNIX)
	closedir(d);
#else
	FindClose(findHandle);
#endif
}
