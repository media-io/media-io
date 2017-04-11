#ifndef _MEDIAIO_API_DATA_COMPONENT_H_
#define _MEDIAIO_API_DATA_COMPONENT_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Component
{
	void*        data;
	unsigned int allocatedSize;
	unsigned int size;
	unsigned int width;
	unsigned int height;
	unsigned int precision;
	unsigned int sampleSizeInByte;
	unsigned int horizontalSubsampling;
	unsigned int verticalSubsampling;
	bool         signedData;

} Component;

void init_component(Component* component);
void resize_component(Component* component, unsigned int requiredSize);
void delete_component(Component* component);

#ifdef __cplusplus
}
#endif

#endif
