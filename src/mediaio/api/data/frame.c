
#include "frame.h"

void init_frame(Frame* frame)
{
	frame->components = NULL;
	frame->numberOfComponents = 0;
}

void create_components(Frame* frame, unsigned int required_components)
{
	if(frame->numberOfComponents == 0)
	{
		frame->components = (Component*) malloc(required_components * sizeof(Component));
		frame->numberOfComponents = required_components;
	}
	else
	{
		for(unsigned int index = 0; index < frame->numberOfComponents; ++index)
		{
			delete_component(&frame->components[index]);
		}
		frame->components = (Component*)realloc(frame->components, required_components * sizeof(Component));
		frame->numberOfComponents = required_components;
	}
	for(unsigned int index = 0; index < required_components; ++index)
	{
		init_component(&frame->components[index]);
	}
}

void delete_frame(Frame* frame)
{
	if(frame->components)
	{
		for(unsigned int index = 0; index < frame->numberOfComponents; ++index)
		{
			delete_component(&frame->components[index]);
		}
		free(frame->components);
		init_frame(frame);
	}
}
