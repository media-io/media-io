
#include "api.h"

const char* get_api_str(enum MediaioPluginApi api)
{
	switch(api)
	{
		case PluginApiReader:    return kMediaioReaderPluginApi;
		case PluginApiWriter:    return kMediaioWriterPluginApi;
		case PluginApiUnwrapper: return kMediaioUnwrapperPluginApi;
		case PluginApiWrapper:   return kMediaioWrapperPluginApi;
		case PluginApiDecoder:   return kMediaioDecoderPluginApi;
		case PluginApiEncoder:   return kMediaioEncoderPluginApi;
		case PluginApiGenerator: return kMediaioGeneratorPluginApi;
		case PluginApiFilter:    return kMediaioFilterPluginApi;
		case PluginApiAnalyser:  return kMediaioAnalyserPluginApi;
	}
}
