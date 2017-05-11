#ifndef _MEDIAIO_APP_COMMON_COMMANDLINEPARSER_HPP_
#define _MEDIAIO_APP_COMMON_COMMANDLINEPARSER_HPP_

#include <mediaio/api/metadata/metadata.h>

#include <string>
#include <vector>
#include <iostream>
#include <map>

class CommandLineParser
{
public:
	CommandLineParser();

	void parse(size_t argc, char** argv);

	const size_t                    getDuration()        const { return duration;            }

	const std::vector<std::string>& getReaders()         const { return readerIdentifier; }
	const std::vector<std::string>& getWriters()         const { return writerIdentifier; }
	const std::vector<std::string>& getGenerators()      const { return generatorIdentifier; }
	const std::vector<std::string>& getUnwrappers()      const { return unwrapperIdentifier; }
	const std::vector<std::string>& getWrappers()        const { return wrapperIdentifier;   }
	const std::vector<std::string>& getDecoders()        const { return decoderIdentifier;   }
	const std::vector<std::string>& getEncoders()        const { return encoderIdentifier;   }
	const std::vector<std::string>& getFilters()         const { return filterIdentifier;    }
	const std::vector<std::string>& getAnalysers()       const { return analyserIdentifier;  }
	const std::vector<std::string>& getInputFilenames()  const { return inputFilenames;      }
	const std::vector<std::string>& getOutputFilenames() const { return outputFilenames;     }

	const std::map<std::string, std::string>& getReaderParameters    ( size_t index ) const { return readerParameters.at( index ); }
	const std::map<std::string, std::string>& getWriterParameters    ( size_t index ) const { return writerParameters.at( index ); }
	const std::map<std::string, std::string>& getGeneratorParameters ( size_t index ) const { return generatorParameters.at( index ); }
	const std::map<std::string, std::string>& getUnwrapperParameters ( size_t index ) const { return unwrapperParameters.at( index ); }
	const std::map<std::string, std::string>& getWrapperParameters   ( size_t index ) const { return wrapperParameters.at( index );   }
	const std::map<std::string, std::string>& getDecoderParameters   ( size_t index ) const { return decoderParameters.at( index );   }
	const std::map<std::string, std::string>& getEncoderParameters   ( size_t index ) const { return encoderParameters.at( index );   }
	const std::map<std::string, std::string>& getFilterParameters    ( size_t index ) const { return filterParameters.at( index );    }

protected:
	void parseParameters( std::map< std::string, std::string >& parameters, size_t& index, int argc, char** argv );

private:
	size_t duration;

	std::vector<std::string> readerIdentifier;
	std::vector<std::string> writerIdentifier;
	std::vector<std::string> generatorIdentifier;
	std::vector<std::string> unwrapperIdentifier;
	std::vector<std::string> wrapperIdentifier;
	std::vector<std::string> decoderIdentifier;
	std::vector<std::string> encoderIdentifier;
	std::vector<std::string> filterIdentifier;
	std::vector<std::string> analyserIdentifier;
	std::vector<std::string> inputFilenames;
	std::vector<std::string> outputFilenames;

	std::vector< std::map< std::string, std::string > > readerParameters;
	std::vector< std::map< std::string, std::string > > writerParameters;
	std::vector< std::map< std::string, std::string > > generatorParameters;
	std::vector< std::map< std::string, std::string > > unwrapperParameters;
	std::vector< std::map< std::string, std::string > > wrapperParameters;
	std::vector< std::map< std::string, std::string > > decoderParameters;
	std::vector< std::map< std::string, std::string > > encoderParameters;
	std::vector< std::map< std::string, std::string > > filterParameters;
	std::vector< std::map< std::string, std::string > > analyserParameters;
};

CommandLineParser::CommandLineParser()
	: duration(1)
{

}

void CommandLineParser::parse(size_t argc, char** argv)
{
	for(size_t index = 1; index < argc; ++index)
	{
		if( argv[index][0] == '-' )
		{
			if( ! strcmp( argv[index], "-i" ) ||
				! strcmp( argv[index], "-input" ) )
			{
				++index;
				if( index == argc )
				{
					std::cerr << "missing input filename" << std::endl;
					exit( -1 );
				}
				inputFilenames.push_back( std::string( argv[index] ) );
			}
			if( ! strcmp( argv[index], "-o" ) ||
				! strcmp( argv[index], "-output" ) )
			{
				++index;
				if( index == argc )
				{
					std::cerr << "missing output filename" << std::endl;
					exit( -1 );
				}
				outputFilenames.push_back( std::string( argv[index] ) );
			}
			if( ! strcmp( argv[index], "-r" ) ||
				! strcmp( argv[index], "--reader" ) )
			{
				++index;
				if( index == argc )
				{
					std::cerr << "missing reader plugin name" << std::endl;
					exit( -1 );
				}

				readerIdentifier.push_back( std::string( argv[index] ) );
				std::map< std::string, std::string > parameters;
				parseParameters( parameters, index, argc, argv );
				readerParameters.push_back( parameters );
			}
			if( ! strcmp( argv[index], "-b" ) ||
				! strcmp( argv[index], "--writer" ) )
			{
				++index;
				if( index == argc )
				{
					std::cerr << "missing writer plugin name" << std::endl;
					exit( -1 );
				}

				writerIdentifier.push_back( std::string( argv[index] ) );
				std::map< std::string, std::string > parameters;
				parseParameters( parameters, index, argc, argv );
				writerParameters.push_back( parameters );
			}
			if( ! strcmp( argv[index], "-g" ) ||
				! strcmp( argv[index], "--generator" ) )
			{
				++index;
				if( index == argc )
				{
					std::cerr << "missing generator plugin name" << std::endl;
					exit( -1 );
				}

				generatorIdentifier.push_back( std::string( argv[index] ) );
				std::map< std::string, std::string > parameters;
				parseParameters( parameters, index, argc, argv );
				generatorParameters.push_back( parameters );
			}
			if( ! strcmp( argv[index], "-u" ) ||
				! strcmp( argv[index], "--unwrapper" ) )
			{
				++index;
				if( index == argc )
				{
					std::cerr << "missing unwrapper plugin name" << std::endl;
					exit( -1 );
				}

				unwrapperIdentifier.push_back( std::string( argv[index] ) );
				std::map< std::string, std::string > parameters;
				parseParameters( parameters, index, argc, argv );
				unwrapperParameters.push_back( parameters );
			}
			if( ! strcmp( argv[index], "-w" ) ||
				! strcmp( argv[index], "--wrapper" ) )
			{
				++index;
				if( index == argc )
				{
					std::cerr << "missing wrapper plugin name" << std::endl;
					exit( -1 );
				}

				wrapperIdentifier.push_back( std::string( argv[index] ) );
				std::map< std::string, std::string > parameters;
				parseParameters( parameters, index, argc, argv );
				wrapperParameters.push_back( parameters );
			}
			if( ! strcmp( argv[index], "-d" ) ||
				! strcmp( argv[index], "--decoder" ) )
			{
				++index;
				if( index == argc )
				{
					std::cerr << "missing decoder plugin name" << std::endl;
					exit( -1 );
				}

				decoderIdentifier.push_back( std::string( argv[index] ) );
				std::map< std::string, std::string > parameters;
				parseParameters( parameters, index, argc, argv );
				decoderParameters.push_back( parameters );
			}
			if( ! strcmp( argv[index], "-e" ) ||
				! strcmp( argv[index], "--encoder" ) )
			{
				++index;
				if( index == argc )
				{
					std::cerr << "missing encoder plugin name" << std::endl;
					exit( -1 );
				}

				encoderIdentifier.push_back( std::string( argv[index] ) );
				std::map< std::string, std::string > parameters;
				parseParameters( parameters, index, argc, argv );
				encoderParameters.push_back( parameters );
			}
			if( ! strcmp( argv[index], "-f" ) ||
				! strcmp( argv[index], "--filter" ) )
			{
				++index;
				if( index == argc )
				{
					std::cerr << "missing filter plugin name" << std::endl;
					exit( -1 );
				}

				filterIdentifier.push_back( std::string( argv[index] ) );
				std::map< std::string, std::string > parameters;
				parseParameters( parameters, index, argc, argv );
				filterParameters.push_back( parameters );
			}
			if( ! strcmp( argv[index], "-a" ) ||
				! strcmp( argv[index], "--analyser" ) )
			{
				++index;
				if( index == argc )
				{
					std::cerr << "missing analyser plugin name" << std::endl;
					exit( -1 );
				}

				analyserIdentifier.push_back( std::string( argv[index] ) );
				std::map< std::string, std::string > parameters;
				parseParameters( parameters, index, argc, argv );
				analyserParameters.push_back( parameters );
			}
			if( ! strcmp( argv[index], "--duration" ) )
			{
				++index;
				if( index == argc )
				{
					std::cerr << "missing duration value" << std::endl;
					exit( -1 );
				}

				duration = atoi( argv[index] );
			}
		}
	}
}

void CommandLineParser::parseParameters( std::map< std::string, std::string >& parameters, size_t& index, int argc, char** argv )
{
	while( 1 )
	{
		if( index + 1 >= argc ||
			argv[index + 1][0] == '-' )
		{
			return;
		}
		++index;
		std::string key = argv[index];
		++index;

		if( index == argc )
		{
			std::cerr << "missing value for parameter " << argv[index - 1] << std::endl;
			exit(-1);
		}

		std::string value = argv[index];
		parameters[ key ] = value;
	}
}

#endif
