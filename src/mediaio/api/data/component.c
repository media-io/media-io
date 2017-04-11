
#include "component.h"

void init_component(Component* component)
{
	component->data = NULL;
	component->allocatedSize = 0;
	component->size = 0;
	component->width = 0;
	component->height = 0;
	component->precision = 0;
	component->sampleSizeInByte = 0;
	component->horizontalSubsampling = 0;
	component->verticalSubsampling = 0;
	component->signedData = false;
}

void resize_component(Component* component, unsigned int requiredSize)
{
	if(component->allocatedSize == 0)
	{
		component->data = malloc(requiredSize);
		component->allocatedSize = requiredSize;
	}
	else if(component->allocatedSize < requiredSize)
	{
		component->data = realloc(component->data, requiredSize);
		component->allocatedSize = requiredSize;
	}
	component->size = requiredSize;
}

void delete_component(Component* component)
{
	if(component->data)
	{
		free(component->data);
		init_component(component);
	}
}
