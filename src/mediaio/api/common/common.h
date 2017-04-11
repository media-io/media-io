#ifndef _MEDIAIO_API_COMMON_COMMON_H_
#define _MEDIAIO_API_COMMON_COMMON_H_

#include <stddef.h>
#include <stdbool.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(WIN32) || defined(WIN64)
	#define MediaioExport extern __declspec(dllexport)
#else
	#define MediaioExport extern
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
