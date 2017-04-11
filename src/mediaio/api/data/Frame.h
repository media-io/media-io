#ifndef _MEDIAIO_API_DATA_FRAME_H_
#define _MEDIAIO_API_DATA_FRAME_H_

#include <stddef.h>
#include <stdlib.h>
#include "component.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Frame
{
	Component*   components;
	unsigned int numberOfComponents;
} Frame;


void init_frame(Frame* frame);
void create_components(Frame* frame, unsigned int required_components);
void delete_frame(Frame* frame);

#ifdef __cplusplus
}
#endif

#endif
