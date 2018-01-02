#ifndef _MEDIAIO_API_COMMON_API_H_
#define _MEDIAIO_API_COMMON_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#define kMediaioReaderPluginApi       "MediaioReaderPluginApi"
#define kMediaioWriterPluginApi       "MediaioWriterPluginApi"
#define kMediaioUnwrapperPluginApi    "MediaioUnwrapperPluginApi"
#define kMediaioWrapperPluginApi      "MediaioWrapperPluginApi"
#define kMediaioImageDecoderPluginApi "MediaioImageDecoderPluginApi"
#define kMediaioAudioDecoderPluginApi "MediaioAudioDecoderPluginApi"
#define kMediaioImageEncoderPluginApi "MediaioImageEncoderPluginApi"
#define kMediaioAudioEncoderPluginApi "MediaioAudioEncoderPluginApi"
#define kMediaioGeneratorPluginApi    "MediaioGeneratorPluginApi"
#define kMediaioAudioFilterPluginApi  "MediaioAudioFilterPluginApi"
#define kMediaioImageFilterPluginApi  "MediaioImageFilterPluginApi"
#define kMediaioAnalyserPluginApi     "MediaioAnalyserPluginApi"

#define kMediaioGetInstancePlugin     "MediaioGetInstancePlugin"
#define kMediaioGetReaderPlugin       "MediaioGetReaderPlugin"
#define kMediaioGetWriterPlugin       "MediaioGetWriterPlugin"
#define kMediaioGetUnwrapperPlugin    "MediaioGetUnwrapperPlugin"
#define kMediaioGetWrapperPlugin      "MediaioGetWrapperPlugin"
#define kMediaioGetAnalyserPlugin     "MediaioGetAnalyserPlugin"
#define kMediaioGetAudioDecoderPlugin "MediaioGetAudioDecoderPlugin"
#define kMediaioGetImageDecoderPlugin "MediaioGetImageDecoderPlugin"
#define kMediaioGetAudioEncoderPlugin "MediaioGetAudioEncoderPlugin"
#define kMediaioGetImageEncoderPlugin "MediaioGetImageEncoderPlugin"
#define kMediaioGetGeneratorPlugin    "MediaioGetGeneratorPlugin"
#define kMediaioGetAudioFilterPlugin  "MediaioGetAudioFilterPlugin"
#define kMediaioGetImageFilterPlugin  "MediaioGetImageFilterPlugin"

typedef enum MediaioPluginApi
{
	PluginApiReader = 0,
	PluginApiWriter,
	PluginApiUnwrapper,
	PluginApiWrapper,
	PluginApiAudioDecoder,
	PluginApiImageDecoder,
	PluginApiAudioEncoder,
	PluginApiImageEncoder,
	PluginApiGenerator,
	PluginApiAudioFilter,
	PluginApiImageFilter,
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
	PluginActionAudioDecoder,
	PluginActionImageDecoder,
	PluginActionAudioEncoder,
	PluginActionImageEncoder,
	PluginActionGenerator,
	PluginActionAudioFilter,
	PluginActionImageFilter,
	PluginActionAnalyser,
} MediaioPluginAction;

const char* get_api_str(enum MediaioPluginApi api);
const char* get_action_str(enum MediaioPluginAction api);
enum MediaioPluginAction get_action(const char* api);

#ifdef __cplusplus
}
#endif

#endif
