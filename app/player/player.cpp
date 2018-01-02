
#include <mediaio/api/common/colors.h>
#include <mediaio/host/Plugins.hpp>

#include "CommandLineParser.hpp"

#include "Window.hpp"

#include <iostream>
#include <iomanip>
#include <map>

int main(int argc, char** argv)
{
	std::cout << "Media-IO - Player" << std::endl;

	try
	{
		CommandLineParser parser;
		parser.parse( argc, argv );

		if(
			parser.getInputFilenames().size() == 0
		)
		{
			throw std::runtime_error( "missing some parameters to launch decoding process" );
		}

		Reader reader;
		Plugins plugins;

		std::string reader_plugin = parser.getReaders().size() ? parser.getReaders().at(0) : "";
		std::string unwrapper_plugin = parser.getUnwrappers().size() ? parser.getUnwrappers().at(0) : "";
		std::string decoder_plugin = parser.getDecoders().size() ? parser.getDecoders().at(0) : "";

		reader.configure(
			plugins,
			reader_plugin,
			unwrapper_plugin,
			decoder_plugin,
			parser.getFilters(),
			parser.getInputFilenames().at(0)
		);

		// reader.setReaderParameters(parser.getReaderParameters(0));
		if(unwrapper_plugin != "")
		{
			reader.setUnwrapperParameters(parser.getUnwrapperParameters(0));
		}
		if(decoder_plugin != "")
		{
			reader.setDecoderParameters(parser.getDecoderParameters(0));
		}

		for(size_t index = 0; index < parser.getFilters().size(); ++index)
		{
			reader.setFilterParameters(index, parser.getFilterParameters(index));
		}
		Window window(reader);
		window.launch();
	}
	catch( std::exception& e)
	{
		std::cerr << std::endl << kColorRed << "error: " << e.what() << kColorNone << std::endl;
	}
	catch(...)
	{
		std::cerr << std::endl << kColorRed << "error: unknown error" << kColorNone << std::endl;
	}

	return 0;
}
