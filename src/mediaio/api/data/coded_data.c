
#include "coded_data.h"

void init_coded_data(CodedData* coded_data) {
	coded_data->data = NULL;
	coded_data->allocated_size = 0;
	coded_data->size = 0;
}

void resize_coded_data(CodedData* coded_data, unsigned int required_size)
{
	if(coded_data->allocated_size == 0)
	{
		coded_data->data = malloc(required_size);
		coded_data->allocated_size = required_size;
	}
	else if(coded_data->allocated_size < required_size)
	{
		coded_data->data = realloc(coded_data->data, required_size);
		coded_data->allocated_size = required_size;
	}
	coded_data->size = required_size;
}

void delete_coded_data(CodedData* coded_data)
{
	if(coded_data->data)
	{
		free(coded_data->data);
		init_coded_data(coded_data);
	}
}
