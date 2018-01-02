#ifndef _MEDIAIO_API_COMMON_COMMON_H_
#define _MEDIAIO_API_COMMON_COMMON_H_

#include <stddef.h>
#include <stdbool.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Platform independent export macro.
 *
 * This macro is to be used before any symbol that is to be
 * exported from a plug-in. This is OS/compiler dependent.
 */
#if ( defined( WIN32 ) || defined( WIN64 ) || defined( _WIN32 ) || defined( _WIN64 ) || defined( __WINDOWS__ ) || defined( __TOS_WIN__ ) || defined( __WIN32__ ) )
 #define MediaioExport extern __declspec( dllexport )
#elif defined( __GNUC__ )     // Add compiler definition here...
 #if __GNUC__ - 0 > 3 || ( __GNUC__ - 0 == 3 && __GNUC_MINOR__ - 0 > 2 )
  #define MediaioExport __attribute__ ( ( visibility( "default" ) ) )
 #else
  #define MediaioExport
  #warning "MediaioExport not set because of a too old gcc version. The plug-in may not compile with the option -fvisible=hidden."
 #endif
#else
 #error "MediaioExport not defined for this compiler..."
#endif

/** @brief Blind data structure to manipulate sets of properties through */
typedef struct MediaioPropertySetStruct* MediaioPropertySetHandle;

/** @brief Mediaio status return type */
typedef int MediaioStatus;

#define kMediaioStatusOK         ((int)0)
#define kMediaioStatusFailed     ((int)1)
#define kMediaioStatusErrorFatal ((int)2)
#define kMediaioStatErrorUnknown ((int)3)

#ifdef __cplusplus
}
#endif

#endif
