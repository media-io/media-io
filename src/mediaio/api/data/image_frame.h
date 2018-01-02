#ifndef _MEDIAIO_API_DATA_IMAGE_FRAME_H_
#define _MEDIAIO_API_DATA_IMAGE_FRAME_H_

#include <stddef.h>
#include <stdlib.h>
#include "component.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImageFrame
{
	Component*   components;
	unsigned int numberOfComponents;
} ImageFrame;


void init_image_frame(ImageFrame* frame);
void create_components(ImageFrame* frame, unsigned int required_components);
void delete_image_frame(ImageFrame* frame);

#ifdef __cplusplus
}
#endif

#endif
