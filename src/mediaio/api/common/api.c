
#include "api.h"
#include <string.h>

const char* get_api_str(enum MediaioPluginApi api)
{
	switch(api)
	{
		case PluginApiReader:       return kMediaioReaderPluginApi;
		case PluginApiWriter:       return kMediaioWriterPluginApi;
		case PluginApiUnwrapper:    return kMediaioUnwrapperPluginApi;
		case PluginApiWrapper:      return kMediaioWrapperPluginApi;
		case PluginApiAudioDecoder: return kMediaioAudioDecoderPluginApi;
		case PluginApiImageDecoder: return kMediaioImageDecoderPluginApi;
		case PluginApiAudioEncoder: return kMediaioAudioEncoderPluginApi;
		case PluginApiImageEncoder: return kMediaioImageEncoderPluginApi;
		case PluginApiGenerator:    return kMediaioGeneratorPluginApi;
		case PluginApiAudioFilter:  return kMediaioAudioFilterPluginApi;
		case PluginApiImageFilter:  return kMediaioImageFilterPluginApi;
		case PluginApiAnalyser:     return kMediaioAnalyserPluginApi;
	}
}


const char* get_action_str(enum MediaioPluginAction api)
{
	switch(api)
	{
		case PluginActionInstance:     return kMediaioGetInstancePlugin;
		case PluginActionReader:       return kMediaioGetReaderPlugin;
		case PluginActionWriter:       return kMediaioGetWriterPlugin;
		case PluginActionUnwrapper:    return kMediaioGetUnwrapperPlugin;
		case PluginActionWrapper:      return kMediaioGetWrapperPlugin;
		case PluginActionAudioDecoder: return kMediaioGetAudioDecoderPlugin;
		case PluginActionImageDecoder: return kMediaioGetImageDecoderPlugin;
		case PluginActionAudioEncoder: return kMediaioGetAudioEncoderPlugin;
		case PluginActionImageEncoder: return kMediaioGetImageEncoderPlugin;
		case PluginActionGenerator:    return kMediaioGetGeneratorPlugin;
		case PluginActionAudioFilter:  return kMediaioGetAudioFilterPlugin;
		case PluginActionImageFilter:  return kMediaioGetImageFilterPlugin;
		case PluginActionAnalyser:     return kMediaioGetAnalyserPlugin;
		case PluginActionUnknown:      return NULL;
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
	if(!strcmp(api, kMediaioGetAudioDecoderPlugin))
	{
		return PluginActionAudioDecoder;
	}
	if(!strcmp(api, kMediaioGetImageDecoderPlugin))
	{
		return PluginActionImageDecoder;
	}
	if(!strcmp(api, kMediaioGetAudioEncoderPlugin))
	{
		return PluginActionAudioEncoder;
	}
	if(!strcmp(api, kMediaioGetImageEncoderPlugin))
	{
		return PluginActionImageEncoder;
	}
	if(!strcmp(api, kMediaioGetGeneratorPlugin))
	{
		return PluginActionGenerator;
	}
	if(!strcmp(api, kMediaioGetAudioFilterPlugin))
	{
		return PluginActionAudioFilter;
	}
	if(!strcmp(api, kMediaioGetImageFilterPlugin))
	{
		return PluginActionImageFilter;
	}
	if(!strcmp(api, kMediaioGetAnalyserPlugin))
	{
		return PluginActionAnalyser;
	}
	return PluginActionUnknown;
}
