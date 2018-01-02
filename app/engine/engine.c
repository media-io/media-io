
#include <mediaio/host_c/plugins.h>
#include <mediaio/api/common/api.h>
#include <mediaio/api/instance/instance.h>
#include <mediaio/api/reader/reader.h>
#include <mediaio/api/writer/writer.h>
#include <mediaio/api/unwrapper/unwrapper.h>
#include <mediaio/api/wrapper/wrapper.h>
#include <mediaio/api/generator/generator.h>
#include <mediaio/api/decoder/decoder.h>
#include <mediaio/api/encoder/encoder.h>

#include <pthread.h>
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

int connect_plugins(struct PluginInstance* pi_src, struct PluginInstance* pi_dst)
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

int generate_frame(struct PluginInstance* pi, ImageFrame* frame)
{
	MediaioPluginGenerator* generator_api = (MediaioPluginGenerator*)pi->plugin->action_entry(kMediaioGetGeneratorPlugin);
	return generator_api->generate(pi->handle, frame);
}

int decode_frame(struct PluginInstance* pi, CodedData* packet, ImageFrame* frame)
{
	MediaioPluginImageDecoder* decoder_api = (MediaioPluginImageDecoder*)pi->plugin->action_entry(kMediaioGetImageDecoderPlugin);
	return decoder_api->decode_image(pi->handle, packet, frame);
}

int encode_frame(struct PluginInstance* pi, ImageFrame* frame, CodedData* packet)
{
	MediaioPluginImageEncoder* encoder_api = (MediaioPluginImageEncoder*)pi->plugin->action_entry(kMediaioGetImageEncoderPlugin);
	return encoder_api->encode_image(pi->handle, frame, packet);
}

static void *task(void *p_data)
{
	// puts ("create unused thread for link main exec with pthread, required for turingcodec");

	(void) p_data;
	return NULL;
}

int main(int argc, char** argv)
{
	printf("Media-IO - Engine\n");

	pthread_t ta;
	pthread_create(&ta, NULL, task, NULL);

	// struct PluginInstance pi_reader;
	struct PluginInstance pi_writer;
	struct PluginInstance pi_unwrapper;
	struct PluginInstance pi_wrapper;
	struct PluginInstance pi_decoder;
	// struct PluginInstance pi_generator;
	struct PluginInstance pi_encoder;

	// if(get_plugin_instance("filesystem", PluginApiReader, &pi_reader) != kMediaioStatusOK)
	// 	exit(-1);
	if(get_plugin_instance("filesystem", PluginApiWriter, &pi_writer) != kMediaioStatusOK)
		exit(-1);

	if(get_plugin_instance("mxfunwrapper", PluginApiUnwrapper, &pi_unwrapper) != kMediaioStatusOK)
		exit(-1);
	// if(get_plugin_instance("bento_ts", PluginApiWrapper, &pi_wrapper) != kMediaioStatusOK)
	// 	exit(-1);
	// if(get_plugin_instance("tiff", PluginApiDecoder, &pi_decoder) != kMediaioStatusOK)
	// 	exit(-1);
	if(get_plugin_instance("turing", PluginApiImageEncoder, &pi_encoder) != kMediaioStatusOK)
		exit(-1);
	if(get_plugin_instance("ffmpeg", PluginApiImageDecoder, &pi_decoder) != kMediaioStatusOK)
		exit(-1);
	if(get_plugin_instance("tiff", PluginApiImageEncoder, &pi_encoder) != kMediaioStatusOK)
		exit(-1);
	// if(get_plugin_instance("nvidiaencoder", PluginApiImageEncoder, &pi_encoder) != kMediaioStatusOK)
	// 	exit(-1);

	// const char* in_filename = "/Users/marco/Movies/seq1/imf_app4_seq1.####.tiff";
	const char* in_filename = "/Users/marco/Movies/michael_buble.mov_M6.mxf";
	const char* out_filename = "stream.ts";

	// if(set_filename(&pi_reader, in_filename) != kMediaioStatusOK)
	// 	exit(-1);
	if(set_filename(&pi_writer, out_filename) != kMediaioStatusOK)
		exit(-1);

	// if(connect_plugins(&pi_reader, &pi_unwrapper) != kMediaioStatusOK)
	// 	exit(-1);
	if(connect_plugins(&pi_wrapper, &pi_writer) != kMediaioStatusOK)
		exit(-1);

	int count = 0;
	while(1)
	{
		CodedData src_packet;
		init_coded_data(&src_packet);

		// printf("process frame %d\r", count);
		printf("process frame %d\n", count);
		fflush(stdout);

		if(unwrap_next_frame(&pi_unwrapper, &src_packet) != kMediaioStatusOK)
		{
			delete_coded_data(&src_packet);
			break;
		}

		ImageFrame frame;
		init_image_frame(&frame);
		if(decode_frame(&pi_decoder, &src_packet, &frame) != kMediaioStatusOK)
		{
			delete_coded_data(&src_packet);
			delete_image_frame(&frame);
			continue;
		}
		CodedData dst_packet;
		init_coded_data(&dst_packet);
		if(encode_frame(&pi_encoder, &frame, &dst_packet) != kMediaioStatusOK)
		{
			printf("Failed to encode frame\n");
			break;
		}
		if(wrap_next_frame(&pi_wrapper, &dst_packet) != kMediaioStatusOK)
		{
			printf("Failed to wrap frame\n");
			break;
		}
		delete_image_frame(&frame);
		delete_coded_data(&src_packet);
		delete_coded_data(&dst_packet);
		++count;

		if(count >= 100)
		{
			while(true)
			{
				ImageFrame* frame = NULL;
				CodedData dst_packet;
				init_coded_data(&dst_packet);
				if(encode_frame(&pi_encoder, frame, &dst_packet) != kMediaioStatusOK)
				{
					break;
				}

				if(dst_packet.size == 0)
				{
					break;
				}

				if(wrap_next_frame(&pi_wrapper, &dst_packet) != kMediaioStatusOK)
				{
					break;
				}
				delete_coded_data(&dst_packet);
			}
			break;
		}
	}

	// delete_plugin_instance(&pi_reader);
	delete_plugin_instance(&pi_writer);
	delete_plugin_instance(&pi_unwrapper);
	delete_plugin_instance(&pi_decoder);
	// delete_plugin_instance(&pi_generator);
	delete_plugin_instance(&pi_encoder);
	delete_plugin_instance(&pi_wrapper);

	printf("Total processed frames: %d\n", count);

	return 0;
}
