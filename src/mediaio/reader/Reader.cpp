#include "Reader.hpp"
// #include "PrintMetadata.hpp"

#include <mediaio/api/reader/reader.h>
#include <mediaio/api/unwrapper/unwrapper.h>
#include <mediaio/api/decoder/decoder.h>
#include <mediaio/api/filter/filter.h>

#include <mediaio/api/descriptor/file.h>
#include <mediaio/api/descriptor/stream.h>

#include <iostream>
#include <cstring>

Reader::Reader()
	: _readerInstance       (nullptr)
	, _unwrapperInstance    (nullptr)
	, _imageDecoderInstance (nullptr)
	, _audioDecoderInstance (nullptr)
	, _reader               (nullptr)
	, _unwrapper            (nullptr)
	, _imageDecoder         (nullptr)
	, _audioDecoder         (nullptr)
	, _readerHandle         (nullptr)
	, _unwrapperHandle      (nullptr)
	, _imageDecoderHandle   (nullptr)
	, _audioDecoderHandle   (nullptr)
	, _enableDecoding       (true)
{
}

Reader::~Reader()
{
	if( _unwrapperInstance )
		_unwrapperInstance->delete_instance(&_unwrapperHandle);

	if( _imageDecoderInstance )
		_imageDecoderInstance->delete_instance(&_imageDecoderHandle);

	if( _audioDecoderInstance )
		_audioDecoderInstance->delete_instance(&_audioDecoderHandle);

	if( _readerInstance )
		_readerInstance->delete_instance(&_readerHandle);
}


void Reader::configure(
	Plugins& plugins,
	const std::string& readerIdentifier,
	const std::string& unwrapperIdentifier,
	const std::string& imageDecoderIdentifier,
	const std::vector<std::string>& filtersIdentifier,
	const std::string& filename
	)
{
	std::string reader_identifier = readerIdentifier;
	if(readerIdentifier == "")
	{
		if(strncmp(filename.c_str(), "http://" , 7) == 0
			|| strncmp(filename.c_str(), "https://" , 8) == 0)
		{
			reader_identifier = "httpreader";
		}
		else
		{
			reader_identifier = "filesystemreader";
		}
	}
	MediaioPlugin& readerPlugin = plugins.searchPlugin(reader_identifier, kMediaioReaderPluginApi);
	_readerInstance = (MediaioPluginInstance*)readerPlugin.action_entry(kMediaioGetInstancePlugin);
	_reader = (MediaioPluginReader*)readerPlugin.action_entry(kMediaioGetReaderPlugin);
	
	MediaioStatus ret;
	ret = _readerInstance->create_instance(&_readerHandle);
	if(ret == kMediaioStatusFailed)
	{
		throw std::runtime_error("unable to create instance of plugin " + reader_identifier);
	}
	_reader->set_filename(_readerHandle, filename.c_str());

	std::string unwrapper_identifier = unwrapperIdentifier;
	if(unwrapperIdentifier == "")
	{
		std::string sub_name = filename;
		std::cout << sub_name << std::endl;
		if(strcmp(sub_name.substr(sub_name.size() - 4, 4).c_str(), ".mxf") == 0)
		{
			unwrapper_identifier = "mxfunwrapper";
		}
		if(strcmp(sub_name.substr(sub_name.size() - 4, 4).c_str(), ".mov") == 0)
		{
			unwrapper_identifier = "ffmpegunwrapper";
		}
		if(strcmp(sub_name.substr(sub_name.size() -5, 5).c_str(), ".tiff") == 0)
		{
			unwrapper_identifier = "sequenceunwrapper";
		}
	}
	if(unwrapperIdentifier == "")
	{
		unwrapper_identifier = "mxfunwrapper";
	}

	MediaioPlugin& unwrapperPlugin = plugins.searchPlugin(unwrapper_identifier, kMediaioUnwrapperPluginApi);
	_unwrapperInstance = (MediaioPluginInstance*)unwrapperPlugin.action_entry(kMediaioGetInstancePlugin);
	_unwrapper = (MediaioPluginUnwrapper*)unwrapperPlugin.action_entry(kMediaioGetUnwrapperPlugin);

	ret = _unwrapperInstance->create_instance(&_unwrapperHandle);
	if(ret == kMediaioStatusFailed)
	{
		throw std::runtime_error("unable to create instance of plugin " + unwrapper_identifier);
	}

	_unwrapper->set_reader(_unwrapperHandle, _reader, _readerHandle);

	std::string image_decoder_identifier = imageDecoderIdentifier;
	std::string audio_decoder_identifier = "";
	if(imageDecoderIdentifier == "")
	{
		MediaioFileDescriptor descriptor;
		_unwrapper->get_file_description(_unwrapperHandle, &descriptor);
		for (int i = 0; i < descriptor.number_of_streams; ++i)
		{
			MediaioStreamDescriptor stream_descriptor;
			_unwrapper->get_stream_description(_unwrapperHandle, i, &stream_descriptor);
			
			if(stream_descriptor.codec == MediaioStreamCodecMpeg2)
			{
				image_decoder_identifier = "ffmpegdecoder";
			}
			if(stream_descriptor.codec == MediaioStreamCodecJpeg2000)
			{
				image_decoder_identifier = "openjpegdecoder";
			}
			if(stream_descriptor.codec == MediaioStreamCodecPCM)
			{
				audio_decoder_identifier = "pcmdecoder";
			}
			// std::cout << get_stream_kind_letter(stream_descriptor.kind) << " ";
			// std::cout << "codec: " << get_codec_str(stream_descriptor.codec) << std::endl;

			// if(stream_descriptor.image != NULL)
			// {
			// 	std::cout << "width: "  << stream_descriptor.image->width << std::endl;
			// 	std::cout << "height: " << stream_descriptor.image->height << std::endl;
			// }
			// if(stream_descriptor.audio != NULL)
			// {
			// 	std::cout << "channel_count: "      << stream_descriptor.audio->channel_count << std::endl;
			// 	std::cout << "sample_rate: "        << stream_descriptor.audio->sample_rate_num << "/" << stream_descriptor.audio->sample_rate_den << std::endl;
			// 	std::cout << "container_duration: " << stream_descriptor.audio->container_duration << std::endl;
			// 	std::cout << "quantization_bits: "  << stream_descriptor.audio->quantization_bits << std::endl;
			// }
		}
	}

	MediaioPlugin& imageDecoderPlugin = plugins.searchPlugin(image_decoder_identifier, kMediaioImageDecoderPluginApi);
	_imageDecoderInstance = (MediaioPluginInstance*)imageDecoderPlugin.action_entry(kMediaioGetInstancePlugin);
	_imageDecoder = (MediaioPluginImageDecoder*)imageDecoderPlugin.action_entry(kMediaioGetImageDecoderPlugin);
	
	ret = _imageDecoderInstance->create_instance(&_imageDecoderHandle);
	if(ret == kMediaioStatusFailed)
	{
		throw std::runtime_error("unable to create instance of plugin " + image_decoder_identifier);
	}
	
	MediaioPlugin& audioDecoderPlugin = plugins.searchPlugin(audio_decoder_identifier, kMediaioAudioDecoderPluginApi);
	_audioDecoderInstance = (MediaioPluginInstance*)audioDecoderPlugin.action_entry(kMediaioGetInstancePlugin);
	_audioDecoder = (MediaioPluginAudioDecoder*)audioDecoderPlugin.action_entry(kMediaioGetAudioDecoderPlugin);

	ret = _audioDecoderInstance->create_instance(&_audioDecoderHandle);
	if(ret == kMediaioStatusFailed)
	{
		throw std::runtime_error("unable to create instance of plugin " + audio_decoder_identifier);
	}

	for(auto filterIdentifier : filtersIdentifier)
	{
		MediaioPlugin& filterPlugin = plugins.searchPlugin(filterIdentifier, kMediaioImageFilterPluginApi);
		_videoFilters.push_back((MediaioPluginImageFilter*) filterPlugin.action_entry(kMediaioGetImageFilterPlugin));
		_videoFiltersInstance.push_back((MediaioPluginInstance*) filterPlugin.action_entry(kMediaioGetInstancePlugin));
	}

	_videoFiltersHandle.resize(_videoFilters.size());
	size_t index = 0;
	for(auto filter : _videoFiltersInstance)
	{
		ret = filter->create_instance(&_videoFiltersHandle.at(index++));
		if( ret == kMediaioStatusFailed )
		{
			throw std::runtime_error("unable to create instance of filter plugin ");
		}
	}
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

	_imageDecoder->configure(_imageDecoderHandle, &params[0]);
}

void Reader::setFilterParameters(size_t index, const std::map< std::string, std::string>& parameters)
{
	if(index >= _videoFilters.size())
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

	_videoFilters.at(index)->configure(_videoFiltersHandle.at(index), &params[0]);
}

void Reader::disableDecoding(const bool enableDecoding)
{
	_enableDecoding = enableDecoding;
}

void Reader::preload()
{

}

void Reader::readNextImageFrame(ImageFrame& decodedFrame, size_t streamIndex)
{
	while(1)
	{
		CodedData codedFrame;
		init_coded_data(&codedFrame);

		MediaioStatus ret;

		ret = _unwrapper->unwrap_next_frame(_unwrapperHandle, streamIndex, &codedFrame);

		if(ret == kMediaioStatusFailed)
		{
			delete_coded_data(&codedFrame);
			throw std::runtime_error( "unable to unwrap a new packet" );
		}

		init_image_frame(&decodedFrame);
		ImageFrame extractedFrame;
		init_image_frame(&extractedFrame);

		ret = _imageDecoder->decode_image(_imageDecoderHandle, &codedFrame, (_videoFilters.size() == 0) ? &decodedFrame : &extractedFrame);
		if(ret == kMediaioStatusFailed)
		{
			delete_coded_data(&codedFrame);
			continue;
		}

		// Metadata* metadata = _imageDecoder->get_metadatas(_imageDecoderHandle);
		// printMetadata(metadata);

		for(size_t index = 0; index < _videoFilters.size(); ++ index)
		{
			_videoFilters.at(index)->process_image(_videoFiltersHandle.at(index), &extractedFrame, &decodedFrame);
		}

		delete_coded_data(&codedFrame);
		delete_image_frame(&extractedFrame);
		return;
	}
}

void Reader::readNextAudioFrame(AudioFrame& decodedFrame, size_t streamIndex)
{
	while(1)
	{
		CodedData codedFrame;
		init_coded_data(&codedFrame);

		MediaioStatus ret;

		ret = _unwrapper->unwrap_next_frame(_unwrapperHandle, streamIndex, &codedFrame);
		if(ret == kMediaioStatusFailed)
		{
			delete_coded_data(&codedFrame);
			throw std::runtime_error( "unable to unwrap a new packet" );
		}

		init_audio_frame(&decodedFrame);
		AudioFrame extractedFrame;
		init_audio_frame(&extractedFrame);

		ret = _audioDecoder->decode_audio(_audioDecoderHandle, &codedFrame, (_audioFilters.size() == 0) ? &decodedFrame : &extractedFrame);

		if(ret == kMediaioStatusFailed)
		{
			delete_coded_data(&codedFrame);
			continue;
		}

		for(size_t index = 0; index < _audioFilters.size(); ++ index)
		{
			_audioFilters.at(index)->process_audio(_audioFiltersHandle.at(index), &extractedFrame, &decodedFrame);
		}

		delete_audio_frame(&extractedFrame);

		delete_coded_data(&codedFrame);
		return;
	}
}

void Reader::seekAtFrame(long int frameIndex)
{
	_unwrapper->seek_at_frame(_unwrapperHandle, frameIndex);
}
