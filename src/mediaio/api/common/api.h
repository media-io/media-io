#ifndef _MEDIAIO_API_COMMON_API_H_
#define _MEDIAIO_API_COMMON_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#define kMediaioReaderPluginApi    "MediaioReaderPluginApi"
#define kMediaioWriterPluginApi    "MediaioWriterPluginApi"
#define kMediaioUnwrapperPluginApi "MediaioUnwrapperPluginApi"
#define kMediaioWrapperPluginApi   "MediaioWrapperPluginApi"
#define kMediaioDecoderPluginApi   "MediaioDecoderPluginApi"
#define kMediaioEncoderPluginApi   "MediaioEncoderPluginApi"
#define kMediaioGeneratorPluginApi "MediaioGeneratorPluginApi"
#define kMediaioFilterPluginApi    "MediaioFilterPluginApi"
#define kMediaioAnalyserPluginApi  "MediaioAnalyserPluginApi"

#define kMediaioGetInstancePlugin  "MediaioGetInstancePlugin"
#define kMediaioGetReaderPlugin    "MediaioGetReaderPlugin"
#define kMediaioGetWriterPlugin    "MediaioGetWriterPlugin"
#define kMediaioGetUnwrapperPlugin "MediaioGetUnwrapperPlugin"
#define kMediaioGetWrapperPlugin   "MediaioGetWrapperPlugin"
#define kMediaioGetAnalyserPlugin  "MediaioGetAnalyserPlugin"
#define kMediaioGetDecoderPlugin   "MediaioGetDecoderPlugin"
#define kMediaioGetEncoderPlugin   "MediaioGetEncoderPlugin"
#define kMediaioGetGeneratorPlugin "MediaioGetGeneratorPlugin"
#define kMediaioGetFilterPlugin    "MediaioGetFilterPlugin"

typedef enum MediaioPluginApi
{
	PluginApiReader = 0,
	PluginApiWriter,
	PluginApiUnwrapper,
	PluginApiWrapper,
	PluginApiDecoder,
	PluginApiEncoder,
	PluginApiGenerator,
	PluginApiFilter,
	PluginApiAnalyser,
} MediaioPluginApi;

typedef enum MediaioPluginAction
{
	PluginActionUnknown = 0,
	PluginActionInstance,
	PluginActionReader,
	PluginActionWriter,
	PluginActionUnwrapper,
	PluginActionWrapper,
	PluginActionDecoder,
	PluginActionEncoder,
	PluginActionGenerator,
	PluginActionFilter,
	PluginActionAnalyser,
} MediaioPluginAction;

const char* get_api_str(enum MediaioPluginApi api);
const char* get_action_str(enum MediaioPluginAction api);
enum MediaioPluginAction get_action(const char* api);

#ifdef __cplusplus
}
#endif

#endif
