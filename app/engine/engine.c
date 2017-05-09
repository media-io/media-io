
#include <mediaio/host_c/plugins.h>
#include <mediaio/api/common/api.h>
#include <mediaio/api/instance/instance.h>
#include <mediaio/api/reader/reader.h>
#include <mediaio/api/writer/writer.h>
#include <mediaio/api/unwrapper/unwrapper.h>
#include <mediaio/api/wrapper/wrapper.h>
#include <mediaio/api/decoder/decoder.h>
#include <mediaio/api/encoder/encoder.h>

#include <stdio.h>
#include <string.h>

struct PluginInstance
{
	enum MediaioPluginApi api;
	MediaioPlugin* plugin;
	void* handle;
};

int get_plugin_instance(const char* searched_name, enum MediaioPluginApi api, struct PluginInstance* pi)
{
	MediaioPlugin* plugin = search_plugin(searched_name, get_api_str(api));
	if(plugin == NULL){
		printf("Error: unable to found %s plugin\n", searched_name);
		return kMediaioStatusFailed;
	}

	MediaioPluginInstance* instance_api = (MediaioPluginInstance*)plugin->action_entry(kMediaioGetInstancePlugin);

	int ret = instance_api->create_instance(&pi->handle);
	if(ret == kMediaioStatusFailed)
	{
		printf("unable to create instance of plugin");
		return kMediaioStatusFailed;
	}
	pi->api = api;
	pi->plugin = plugin;
	return kMediaioStatusOK;
}

int delete_plugin_instance(struct PluginInstance* pi)
{
	MediaioPluginInstance* instance_api = (MediaioPluginInstance*)pi->plugin->action_entry(kMediaioGetInstancePlugin);
	return instance_api->delete_instance(&pi->handle);
}

int set_filename(struct PluginInstance* pi, const char* filename)
{
	if(pi->api == PluginApiReader)
	{
		MediaioPluginReader* reader_api = (MediaioPluginReader*)pi->plugin->action_entry(kMediaioGetReaderPlugin);
		return reader_api->set_filename(pi->handle, filename);
	}
	if(pi->api == PluginApiWriter)
	{
		MediaioPluginWriter* writer_api = (MediaioPluginWriter*)pi->plugin->action_entry(kMediaioGetWriterPlugin);
		return writer_api->set_filename(pi->handle, filename);
	}
	printf("API don't support set filename\n");
	return kMediaioStatusFailed;
}

int connect(struct PluginInstance* pi_src, struct PluginInstance* pi_dst)
{
	if(pi_src->api == PluginApiReader &&
		pi_dst->api == PluginApiUnwrapper)
	{
		MediaioPluginReader* reader_api = (MediaioPluginReader*)pi_src->plugin->action_entry(kMediaioGetReaderPlugin);
		MediaioPluginUnwrapper* unwrapper_api = (MediaioPluginUnwrapper*)pi_dst->plugin->action_entry(kMediaioGetUnwrapperPlugin);

		return unwrapper_api->set_reader(pi_dst->handle, reader_api, pi_src->handle);
	}

	if(pi_src->api == PluginApiWrapper &&
		pi_dst->api == PluginApiWriter
		)
	{
		MediaioPluginWrapper* wrapper_api = (MediaioPluginWrapper*)pi_src->plugin->action_entry(kMediaioGetWrapperPlugin);
		MediaioPluginWriter* writer_api = (MediaioPluginWriter*)pi_dst->plugin->action_entry(kMediaioGetWriterPlugin);

		return wrapper_api->set_writer(pi_src->handle, writer_api, pi_dst->handle);
	}

	printf("APIs don't support connection\n");
	return kMediaioStatusFailed;
}

int unwrap_next_frame(struct PluginInstance* pi, CodedData* packet)
{
	MediaioPluginUnwrapper* unwrapper_api = (MediaioPluginUnwrapper*)pi->plugin->action_entry(kMediaioGetUnwrapperPlugin);
	return unwrapper_api->unwrap_next_frame(pi->handle, 0, packet);
}

int wrap_next_frame(struct PluginInstance* pi, CodedData* packet)
{
	MediaioPluginWrapper* wrapper_api = (MediaioPluginWrapper*)pi->plugin->action_entry(kMediaioGetWrapperPlugin);
	return wrapper_api->wrap_next_frame(pi->handle, 0, packet);
}

int decode_frame(struct PluginInstance* pi, CodedData* packet, Frame* frame)
{
	MediaioPluginDecoder* decoder_api = (MediaioPluginDecoder*)pi->plugin->action_entry(kMediaioGetDecoderPlugin);
	return decoder_api->decode(pi->handle, packet, frame);
}

int encode_frame(struct PluginInstance* pi, Frame* frame, CodedData* packet)
{
	MediaioPluginEncoder* encoder_api = (MediaioPluginEncoder*)pi->plugin->action_entry(kMediaioGetEncoderPlugin);
	return encoder_api->encode(pi->handle, frame, packet);
}

int main(int argc, char** argv)
{
	printf("Media-IO - Engine\n");

	struct PluginInstance pi_reader;
	struct PluginInstance pi_writer;
	struct PluginInstance pi_unwrapper;
	struct PluginInstance pi_wrapper;
	struct PluginInstance pi_decoder;
	struct PluginInstance pi_encoder;

	if(get_plugin_instance("filesystem", PluginApiReader, &pi_reader) != kMediaioStatusOK)
		exit(-1);
	if(get_plugin_instance("filesystem", PluginApiWriter, &pi_writer) != kMediaioStatusOK)
		exit(-1);
	if(get_plugin_instance("mxfunwrapper", PluginApiUnwrapper, &pi_unwrapper) != kMediaioStatusOK)
		exit(-1);
	if(get_plugin_instance("sequence", PluginApiWrapper, &pi_wrapper) != kMediaioStatusOK)
		exit(-1);
	if(get_plugin_instance("ffmpeg", PluginApiDecoder, &pi_decoder) != kMediaioStatusOK)
		exit(-1);
	if(get_plugin_instance("tiff", PluginApiEncoder, &pi_encoder) != kMediaioStatusOK)
		exit(-1);

	// const char* in_filename = "/Users/marco/Movies/seq1/imf_app4_seq1.####.tiff";
	const char* in_filename = "/Users/marco/Movies/michael_buble.mov_M6.mxf";
	const char* out_filename = "out.####.tiff";

	if(set_filename(&pi_reader, in_filename) != kMediaioStatusOK)
		exit(-1);
	if(set_filename(&pi_writer, out_filename) != kMediaioStatusOK)
		exit(-1);

	if(connect(&pi_reader, &pi_unwrapper) != kMediaioStatusOK)
		exit(-1);
	if(connect(&pi_wrapper, &pi_writer) != kMediaioStatusOK)
		exit(-1);

	int count = 0;
	while(1)
	{
		CodedData src_packet;
		init_coded_data(&src_packet);

		if(unwrap_next_frame(&pi_unwrapper, &src_packet) != kMediaioStatusOK)
		{
			delete_coded_data(&src_packet);
			break;
		}

		Frame frame;
		init_frame(&frame);
		if(decode_frame(&pi_decoder, &src_packet, &frame) != kMediaioStatusOK)
		{
			delete_coded_data(&src_packet);
			delete_frame(&frame);
			continue;
		}
		CodedData dst_packet;
		init_coded_data(&dst_packet);
		if(encode_frame(&pi_encoder, &frame, &dst_packet) != kMediaioStatusOK)
		{
			break;
		}
		if(wrap_next_frame(&pi_wrapper, &dst_packet) != kMediaioStatusOK)
		{
			break;
		}
		delete_frame(&frame);
		delete_coded_data(&src_packet);
		delete_coded_data(&dst_packet);
		++count;
	}

	delete_plugin_instance(&pi_reader);
	delete_plugin_instance(&pi_writer);
	delete_plugin_instance(&pi_unwrapper);
	delete_plugin_instance(&pi_wrapper);

	printf("Total processed frames: %d\n", count);
	return 0;
}
