#ifndef _MEDIAIO_API_DATA_CODED_DATA_H_
#define _MEDIAIO_API_DATA_CODED_DATA_H_

#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CodedData
{
	void*        data;
	unsigned int allocated_size;
	unsigned int size;
} CodedData;

void init_coded_data(CodedData* coded_data);
void resize_coded_data(CodedData* coded_data, unsigned int required_size);
void delete_coded_data(CodedData* coded_data);

#ifdef __cplusplus
}
#endif

#endif
