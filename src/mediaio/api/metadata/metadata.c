
#include "metadata.h"

void init_metadata(Metadata* metadata)
{
	metadata->id     = NULL;
	metadata->label  = NULL;
	metadata->unit   = NULL;
	metadata->mapped = NULL;
	metadata->type   = eMetadataTypeNone;
	metadata->data   = NULL;
}
