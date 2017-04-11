
#include "utils.hpp"
namespace mediaio
{
namespace common
{

std::string MediaioGetEnv(const char* envVar)
{
#ifdef WINDOWS
	size_t requiredSize;
	getenv_s( &requiredSize, 0, 0, envVar );
	std::vector<char> buffer( requiredSize );
	if( requiredSize > 0 )
	{
		getenv_s( &requiredSize, &buffer.front(), requiredSize, envVar );
		return &buffer.front();
	}
	return "";
#else
	if( getenv( envVar ) )
		return getenv( envVar );
#endif
	return "";
}

}
}
