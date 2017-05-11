#ifndef _MEDIAIO_READER_READER_HPP_
#define _MEDIAIO_READER_READER_HPP_

#include <mediaio/api/instance/instance.h>
#include <mediaio/api/data/frame.h>
#include <mediaio/host/Plugins.hpp>
#include <string>
#include <vector>
#include <map>

struct MediaioPluginReader;
struct MediaioPluginUnwrapper;
struct MediaioPluginDecoder;
struct MediaioPluginFilter;

class Reader
{
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

	void setUnwrapperParameters( const std::map< std::string, std::string>& parameters );
	void setDecoderParameters( const std::map< std::string, std::string>& parameters );
	void setFilterParameters( size_t index, const std::map< std::string, std::string>& parameters );

	void disableDecoding( const bool enableDecoding = false );

	void preload();

	void readNextFrame( Frame& decodedFrame );

	void seekAtFrame( long int frameIndex );

private:
	MediaioPluginInstance*              _readerInstance;
	MediaioPluginInstance*              _unwrapperInstance;
	MediaioPluginInstance*              _decoderInstance;
	MediaioPluginReader*                _reader;
	MediaioPluginUnwrapper*             _unwrapper;
	MediaioPluginDecoder*               _decoder;
	std::vector<MediaioPluginFilter*>   _filters;
	std::vector<MediaioPluginInstance*> _filtersInstance;
	void*                               _readerHandle;
	void*                               _unwrapperHandle;
	void*                               _decoderHandle;
	std::vector<void*>                  _filtersHandle;

	bool                                _enableDecoding;
};

#endif