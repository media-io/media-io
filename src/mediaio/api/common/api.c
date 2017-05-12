
#include "api.h"
#include <string.h>

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


const char* get_action_str(enum MediaioPluginAction api)
{
	switch(api)
	{
		case PluginActionInstance:  return kMediaioGetInstancePlugin;
		case PluginActionReader:    return kMediaioGetReaderPlugin;
		case PluginActionWriter:    return kMediaioGetWriterPlugin;
		case PluginActionUnwrapper: return kMediaioGetUnwrapperPlugin;
		case PluginActionWrapper:   return kMediaioGetWrapperPlugin;
		case PluginActionDecoder:   return kMediaioGetDecoderPlugin;
		case PluginActionEncoder:   return kMediaioGetEncoderPlugin;
		case PluginActionGenerator: return kMediaioGetGeneratorPlugin;
		case PluginActionFilter:    return kMediaioGetFilterPlugin;
		case PluginActionAnalyser:  return kMediaioGetAnalyserPlugin;
		case PluginActionUnknown:   return NULL;
	}
	return NULL;
}

enum MediaioPluginAction get_action(const char* api)
{
	if(!strcmp(api, kMediaioGetInstancePlugin))
	{
		return PluginActionInstance;
	}
	if(!strcmp(api, kMediaioGetReaderPlugin))
	{
		return PluginActionReader;
	}
	if(!strcmp(api, kMediaioGetWriterPlugin))
	{
		return PluginActionWriter;
	}
	if(!strcmp(api, kMediaioGetUnwrapperPlugin))
	{
		return PluginActionUnwrapper;
	}
	if(!strcmp(api, kMediaioGetWrapperPlugin))
	{
		return PluginActionWrapper;
	}
	if(!strcmp(api, kMediaioGetDecoderPlugin))
	{
		return PluginActionDecoder;
	}
	if(!strcmp(api, kMediaioGetEncoderPlugin))
	{
		return PluginActionEncoder;
	}
	if(!strcmp(api, kMediaioGetGeneratorPlugin))
	{
		return PluginActionGenerator;
	}
	if(!strcmp(api, kMediaioGetFilterPlugin))
	{
		return PluginActionFilter;
	}
	if(!strcmp(api, kMediaioGetAnalyserPlugin))
	{
		return PluginActionAnalyser;
	}
	return PluginActionUnknown;
}
