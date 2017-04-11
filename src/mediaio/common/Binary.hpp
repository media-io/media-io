#ifndef _MEDIAIO_API_COMMON_BINARY_HPP_
#define _MEDIAIO_API_COMMON_BINARY_HPP_

#include "utils.hpp"
#include <sys/stat.h>

namespace mediaio
{
namespace common
{

class Binary
{

public:
	/// create object representing the binary. Will stat() it, 
	/// and this fails, will set binary to be invalid.
	Binary(const std::string& binaryPath);

	~Binary()
	{
		unload();
	}

	bool isLoaded() const
	{
		return _dlHandle != 0;
	}

	/// Last modification time of the file.
	time_t getTime() const
	{
		return _time;
	}

	size_t getSize() const
	{
		return _size;
	}

	const std::string& getBinaryPath() const
	{
		return _binaryPath;
	}

	void ref();
	void unref();

	/// open the binary.
	void load();

	/// close the binary
	void unload();

	/// look up a symbol in the binary file and return it as a pointer.
	/// returns null pointer if not found, or if the library is not loaded.
	void* findSymbol(const std::string& symbol);

protected:
	std::string _binaryPath;
#if defined(UNIX)
	void *_dlHandle;
#elif defined (WINDOWS)
	HINSTANCE _dlHandle;
#endif
	time_t _time;
	size_t _size;
	int    _users;
	bool   _invalid;
};

}
}

#endif
