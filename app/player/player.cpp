
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

		if( parser.getReaders().size() == 0 ||
			parser.getUnwrappers().size() == 0 ||
			parser.getDecoders().size() == 0 ||
			parser.getInputFilenames().size() == 0
		)
		{
			throw std::runtime_error( "missing some parameters to launch decoding process" );
		}

		Reader reader;
		Plugins plugins;

		reader.configure(
			plugins,
			parser.getReaders().at(0),
			parser.getUnwrappers().at(0),
			parser.getDecoders().at(0),
			parser.getFilters(),
			parser.getInputFilenames().at(0)
		);

		// reader.setReaderParameters(parser.getReaderParameters(0));
		reader.setUnwrapperParameters(parser.getUnwrapperParameters(0));
		reader.setDecoderParameters(parser.getDecoderParameters(0));

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
