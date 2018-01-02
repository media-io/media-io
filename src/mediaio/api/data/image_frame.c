
#include "image_frame.h"

void init_image_frame(ImageFrame* frame)
{
	frame->components = NULL;
	frame->numberOfComponents = 0;
}

void create_components(ImageFrame* frame, unsigned int required_components)
{
	if(frame->numberOfComponents == 0)
	{
		frame->components = (Component*) malloc(required_components * sizeof(Component));
		frame->numberOfComponents = required_components;
	}
	else
	{
		unsigned int index = 0;
		for(index = 0; index < frame->numberOfComponents; ++index)
		{
			delete_component(&frame->components[index]);
		}
		frame->components = (Component*)realloc(frame->components, required_components * sizeof(Component));
		frame->numberOfComponents = required_components;
	}

	unsigned int index = 0;
	for(index = 0; index < required_components; ++index)
	{
		init_component(&frame->components[index]);
	}
}

void delete_image_frame(ImageFrame* frame)
{
	if(frame->components)
	{
		unsigned int index = 0;
		for(index = 0; index < frame->numberOfComponents; ++index)
		{
			delete_component(&frame->components[index]);
		}
		free(frame->components);
		init_image_frame(frame);
	}
}
