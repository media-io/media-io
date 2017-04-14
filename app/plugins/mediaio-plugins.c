
#include <mediaio/host_c/plugins.h>
#include <mediaio/api/common/colors.h>
#include <mediaio/api/reader/reader.h>
#include <mediaio/api/writer/writer.h>
#include <mediaio/api/unwrapper/unwrapper.h>
#include <mediaio/api/generator/generator.h>
#include <mediaio/api/wrapper/wrapper.h>
#include <mediaio/api/decoder/decoder.h>
#include <mediaio/api/encoder/encoder.h>
#include <mediaio/api/filter/filter.h>
#include <mediaio/api/analyser/analyser.h>

#include <stdio.h>
#include <string.h>

void print_plugin(const MediaioPlugin* plugin, const char* api_label, const char* color)
{
	printf("%s", color);
	printf("%-12s%s", api_label, kColorNone);
	printf("%3d.%-4d", plugin->plugin_version_major, plugin->plugin_version_minor);
	printf("%-36.36s", plugin->plugin_identifier);
	printf("%-20.20s", plugin->plugin_label);
	printf("%s\n",plugin->plugin_description);
}

void print_plugins(const char* context, const char* api, const char* color)
{
	int plugin_count = get_plugin_count();
	MediaioPlugin** plugins = get_plugins();

	int index = 0;
	for(index = 0; index < plugin_count; ++index)
	{
		struct MediaioPlugin* plugin = plugins[index];
		if(strcmp(plugin->plugin_api, context))
			continue;

		print_plugin(plugin, api, color);
	}
}

int main(int argc, char** argv)
{
	printf("Media-IO - Plugins detector and information\n");

	int plugin_count = get_plugin_count();

	printf("Plugins: total = %d\n", plugin_count);
	printf("%s%-12s%-8s%-36s%-20s%s\n", kColorGreen, "API", "Version", "Identifier", "Label", "Description");

	print_plugins(kMediaioReaderPluginApi,    "Reader",    kColorPink);
	print_plugins(kMediaioWriterPluginApi,    "Writer",    kColorDark);
	print_plugins(kMediaioGeneratorPluginApi, "Generator", kColorOrange);
	print_plugins(kMediaioUnwrapperPluginApi, "Unwrapper", kColorViolet);
	print_plugins(kMediaioWrapperPluginApi,   "Wrapper",   kColorRed);
	print_plugins(kMediaioDecoderPluginApi,   "Decoder",   kColorYellow);
	print_plugins(kMediaioEncoderPluginApi,   "Encoder",   kColorBlue);
	print_plugins(kMediaioFilterPluginApi,    "Filter",    kColorCyan);
	print_plugins(kMediaioAnalyserPluginApi,  "Analyser",  kColorPurple);

	return 0;
}
