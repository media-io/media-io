#include "Reader.hpp"
#include "PrintMetadata.hpp"

#include <mediaio/api/reader/reader.h>
#include <mediaio/api/unwrapper/unwrapper.h>
#include <mediaio/api/decoder/decoder.h>
#include <mediaio/api/filter/filter.h>

#include <iostream>

Reader::Reader()
	: _readerInstance    (nullptr)
	, _unwrapperInstance (nullptr)
	, _decoderInstance   (nullptr)
	, _reader            (nullptr)
	, _unwrapper         (nullptr)
	, _decoder           (nullptr)
	, _readerHandle      (nullptr)
	, _unwrapperHandle   (nullptr)
	, _decoderHandle     (nullptr)
	, _enableDecoding    (true)
{
}

Reader::~Reader()
{
	if( _unwrapperInstance )
		_unwrapperInstance->delete_instance(&_unwrapperHandle);

	if( _decoderInstance )
		_decoderInstance->delete_instance(&_decoderHandle);

	if( _readerInstance )
		_readerInstance->delete_instance(&_readerHandle);
}


void Reader::configure(
	Plugins& plugins,
	const std::string& readerIdentifier,
	const std::string& unwrapperIdentifier,
	const std::string& decoderIdentifier,
	const std::vector<std::string>& filtersIdentifier,
	const std::string& filename )
{
	MediaioPlugin& readerPlugin = plugins.searchPlugin(readerIdentifier, kMediaioReaderPluginApi);
	_readerInstance = (MediaioPluginInstance*)readerPlugin.action_entry(kMediaioGetInstancePlugin);
	_reader = (MediaioPluginReader*)readerPlugin.action_entry(kMediaioGetReaderPlugin);
	
	MediaioPlugin& unwrapperPlugin = plugins.searchPlugin(unwrapperIdentifier, kMediaioUnwrapperPluginApi);
	_unwrapperInstance = (MediaioPluginInstance*)unwrapperPlugin.action_entry(kMediaioGetInstancePlugin);
	_unwrapper = (MediaioPluginUnwrapper*)unwrapperPlugin.action_entry(kMediaioGetUnwrapperPlugin);
	
	MediaioPlugin& decoderPlugin = plugins.searchPlugin(decoderIdentifier, kMediaioDecoderPluginApi);
	_decoderInstance = (MediaioPluginInstance*)decoderPlugin.action_entry(kMediaioGetInstancePlugin);
	_decoder = (MediaioPluginDecoder*)decoderPlugin.action_entry(kMediaioGetDecoderPlugin);

	// std::cout << "Unwrapper : " << unwrapperPlugin.plugin_identifier << " v" << unwrapperPlugin.plugin_version_major << "." << unwrapperPlugin.plugin_version_minor << std::endl;
	// std::cout << "Decoder   : " << decoderPlugin.plugin_identifier << " v" << decoderPlugin.plugin_version_major << "." << decoderPlugin.plugin_version_minor << std::endl;

	for(auto filterIdentifier : filtersIdentifier)
	{
		MediaioPlugin& filterPlugin = plugins.searchPlugin(filterIdentifier, kMediaioFilterPluginApi);
		_filters.push_back((MediaioPluginFilter*) filterPlugin.action_entry(kMediaioGetFilterPlugin));
		_filtersInstance.push_back((MediaioPluginInstance*) filterPlugin.action_entry(kMediaioGetInstancePlugin));
		// std::cout << "Filter    : " << filterPlugin.plugin_identifier << " v" << filterPlugin.plugin_version_major << "." << filterPlugin.plugin_version_minor << std::endl;
	}

	MediaioStatus ret;
	ret = _readerInstance->create_instance(&_readerHandle);
	if(ret == kMediaioStatusFailed)
	{
		throw std::runtime_error("unable to create instance of plugin " + readerIdentifier);
	}
	ret = _unwrapperInstance->create_instance(&_unwrapperHandle);
	if(ret == kMediaioStatusFailed)
	{
		throw std::runtime_error("unable to create instance of plugin " + unwrapperIdentifier);
	}
	ret = _decoderInstance->create_instance(&_decoderHandle);
	if(ret == kMediaioStatusFailed)
	{
		throw std::runtime_error("unable to create instance of plugin " + decoderIdentifier);
	}

	_filtersHandle.resize(_filters.size());
	size_t index = 0;
	for(auto filter : _filtersInstance)
	{
		ret = filter->create_instance(&_filtersHandle.at(index++));
		if( ret == kMediaioStatusFailed )
		{
			throw std::runtime_error("unable to create instance of filter plugin ");
		}
	}

	_reader->set_filename(_readerHandle, filename.c_str());

	_unwrapper->set_reader(_unwrapperHandle, _reader, _readerHandle);

	// ret = _unwrapper->open( _unwrapperHandle, filename.c_str() );
	// if( ret != kMediaioStatusOK || ! _unwrapperHandle )
	// {
	// 	throw std::runtime_error( "unable to open file: " + filename );
	// }
}

void Reader::setUnwrapperParameters(const std::map< std::string, std::string>& parameters)
{
	std::vector<Metadata> params;

	for(auto& p : parameters)
	{
		Metadata m;
		m.id = p.first.c_str();
		m.type = eMetadataTypeString;
		m.data = (void*)p.second.c_str();
		params.push_back(m);
	}

	Metadata m;
	m.type = eMetadataTypeEnd;
	params.push_back(m);

	_unwrapper->configure(_unwrapperHandle, &params[0]);
}

void Reader::setDecoderParameters(const std::map< std::string, std::string>& parameters)
{
	std::vector<Metadata> params;

	for(auto& p : parameters)
	{
		Metadata m;
		m.id = p.first.c_str();
		m.type = eMetadataTypeString;
		m.data = (void*)p.second.c_str();
		params.push_back( m );
	}

	Metadata m;
	m.type = eMetadataTypeEnd;
	params.push_back(m);

	_decoder->configure(_decoderHandle, &params[0]);
}

void Reader::setFilterParameters(size_t index, const std::map< std::string, std::string>& parameters)
{
	if(index >= _filters.size())
	{
		return;
	}

	std::vector<Metadata> params;

	for(auto& p : parameters)
	{
		Metadata m;
		m.id = p.first.c_str();
		m.type = eMetadataTypeString;
		m.data = (void*)p.second.c_str();
		params.push_back(m);
	}

	Metadata m;
	m.type = eMetadataTypeEnd;
	params.push_back(m);

	_filters.at(index)->configure(_filtersHandle.at(index), &params[0]);
}

void Reader::disableDecoding(const bool enableDecoding)
{
	_enableDecoding = enableDecoding;
}

void Reader::preload()
{

}

void Reader::readNextFrame(Frame& decodedFrame)
{
	size_t streamIndex = 0;

	while(1)
	{
		CodedData codedFrame;
		init_coded_data(&codedFrame);
		MediaioStatus ret;

		// clock_t startTime = clock();

		ret = _unwrapper->unwrap_next_frame(_unwrapperHandle, streamIndex, &codedFrame);

		if(ret == kMediaioStatusFailed)
		{
			delete_coded_data(&codedFrame);
			throw std::runtime_error( "unable to unwrap a new packet" );
		}

		// clock_t unwrapTime = clock();
		// std::cout << "codeddata size = " << codedFrame.size << std::endl;

		init_frame(&decodedFrame);
		Frame extractedFrame;
		init_frame(&extractedFrame);
		
		ret = _decoder->decode(_decoderHandle, &codedFrame, (_filters.size() == 0) ? &decodedFrame : &extractedFrame);
		if(ret == kMediaioStatusFailed)
		{
			delete_coded_data(&codedFrame);
			continue;
			// throw std::runtime_error("unable to decode frame");
		}

		Metadata* metadata = _decoder->get_metadatas(_decoderHandle);

		for(size_t index = 0; index < _filters.size(); ++ index)
		{
			_filters.at(index)->process(_filtersHandle.at(index), &extractedFrame, &decodedFrame);
		}

		printMetadata(metadata);

		// clock_t decodedTime = clock();

		// std::cout << "unwrapping = " << ( ((float)unwrapTime - startTime ) / CLOCKS_PER_SEC );
		// std::cout << " decoding = " << ( ((float) decodedTime - unwrapTime ) / CLOCKS_PER_SEC );
		// std::cout << " total = " << ( ((float) decodedTime - startTime ) / CLOCKS_PER_SEC ) << std::endl;

		delete_coded_data(&codedFrame);
		return;
	}
}


void Reader::seekAtFrame( long int frameIndex )
{
	_unwrapper->seek_at_frame( _unwrapperHandle, frameIndex );
}
