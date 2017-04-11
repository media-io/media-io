#ifndef _MEDIAIO_API_COMMON_UTILS_HPP_
#define _MEDIAIO_API_COMMON_UTILS_HPP_

#include <cstdlib>
#include <string>

#if defined(WIN32) || defined(WIN64)
 #define I386
#elif defined(__linux__)
 #define UNIX
 #ifdef __i386__
  #define I386
 #elif defined(__amd64__)
  #define AMD64
 #else
  #error cannot detect architecture
 #endif
#elif defined(__APPLE__)
 #define UNIX
#else
 #error cannot detect operating system
#endif

#if defined(UNIX)
 #include <dlfcn.h>
#elif defined (WINDOWS)
 #include "windows.h"
 #include <assert.h>
#endif


#if defined (__linux__)

 #define DIRLIST_SEP_CHARS ":;"
 #define DIRSEP "/"
 #include <dirent.h>

 static const char *getArchStr() 
 {
  if(sizeof(void *) == 4)
  {
   return  "Linux-x86";
  }
  else
  {
   return  "Linux-x86-64";
  }
 }

 #define ARCHSTR getArchStr()

#elif defined (__APPLE__)

 #define DIRLIST_SEP_CHARS ";:"
 #define ARCHSTR "MacOS"
 #define DIRSEP "/"
 #include <dirent.h>

#elif defined (WINDOWS)
 #define DIRLIST_SEP_CHARS ";"
 #ifdef _WIN64
  #define ARCHSTR "win64"
 #else
  #define ARCHSTR "win32"
 #endif
 #define DIRSEP "\\"

 #include "shlobj.h"
 #include "tchar.h"
#endif

namespace mediaio
{
namespace common
{

std::string MediaioGetEnv(const char* envVar);

}
}

#endif
