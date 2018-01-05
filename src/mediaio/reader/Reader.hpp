#ifndef _MEDIAIO_READER_READER_HPP_
#define _MEDIAIO_READER_READER_HPP_

#include <mediaio/api/instance/instance.h>
#include <mediaio/api/data/audio_frame.h>
#include <mediaio/api/data/image_frame.h>
#include <mediaio/host/Plugins.hpp>
#include <string>
#include <vector>
#include <map>

struct MediaioPluginReader;
struct MediaioPluginUnwrapper;
struct MediaioPluginAudioDecoder;
struct MediaioPluginImageDecoder;
struct MediaioPluginAudioFilter;
struct MediaioPluginImageFilter;

class Reader
{
	typedef const std::map< std::string, std::string>& Parameters;
public:
	Reader();
	~Reader();

	void configure(
		Plugins& plugins,
		const std::string& readerIdentifier,
		const std::string& unwrapperIdentifier,
		const std::string& decoderIdentifier,
		const std::vector<std::string>& filtersIdentifier,
		const std::string& filename
	);

	void setUnwrapperParameters(Parameters parameters);
	void setDecoderParameters(Parameters parameters);
	void setFilterParameters(size_t index, Parameters parameters);

	void disableDecoding(const bool enableDecoding = false);

	void preload();

	void readNextImageFrame(ImageFrame& frame, size_t streamIndex);
	void readNextAudioFrame(AudioFrame& frame, size_t streamIndex);

	void seekAtFrame(long int frameIndex);

private:
	MediaioPluginInstance*                 _readerInstance;
	MediaioPluginInstance*                 _unwrapperInstance;
	MediaioPluginInstance*                 _imageDecoderInstance;
	MediaioPluginInstance*                 _audioDecoderInstance;
	MediaioPluginReader*                   _reader;
	MediaioPluginUnwrapper*                _unwrapper;
	MediaioPluginImageDecoder*             _imageDecoder;
	MediaioPluginAudioDecoder*             _audioDecoder;

	std::vector<MediaioPluginImageFilter*> _videoFilters;
	std::vector<MediaioPluginInstance*>    _videoFiltersInstance;

	std::vector<MediaioPluginAudioFilter*> _audioFilters;
	std::vector<MediaioPluginInstance*>    _audioFiltersInstance;

	void*                                  _readerHandle;
	void*                                  _unwrapperHandle;
	void*                                  _imageDecoderHandle;
	void*                                  _audioDecoderHandle;

	std::vector<void*>                     _videoFiltersHandle;
	std::vector<void*>                     _audioFiltersHandle;

	bool                                   _enableDecoding;
};

#endif