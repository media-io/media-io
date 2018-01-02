#ifndef _MEDIAIO_PLAYER_PRINT_METADATA_HPP_
#define _MEDIAIO_PLAYER_PRINT_METADATA_HPP_

#include <mediaio/api/metadata/metadata.h>
#include <iostream>
#include <sstream>
#include <iomanip>

void printMetadata( Metadata* metadatas, int level = 0 )
{
	if( metadatas != nullptr )
	{
		size_t index = 0;

		while( metadatas[index].type != eMetadataTypeEnd )
		{
			Metadata& metadata = metadatas[index];
			std::ostringstream label;
			label << "|- " << std::left << std::setw(6) << metadata.id << " - " << metadata.label << " : ";
			std::cout << std::setw(4 * level) << "" << std::left << std::setw(50) << label.str();
			std::cout << std::dec;
			switch(metadata.type)
			{
				case eMetadataTypeNone:
				{
					break;
				}
				case eMetadataTypeEnd:
				{
					break;
				}
				case eMetadataTypeBool:
				{
					std::cout << ( *(bool*)metadata.data ? "True": "False" );
					break;
				}
				case eMetadataTypeUint8:
				{
					std::cout << (int)*(unsigned char*)metadata.data;
					break;
				}
				case eMetadataTypeInt8:
				{
					std::cout << (int)*(char*)metadata.data;
					break;
				}
				case eMetadataTypeUint16:
				{
					std::cout << *(unsigned short*)metadata.data;
					break;
				}
				case eMetadataTypeInt16:
				{
					std::cout << *(short*)metadata.data;
					break;
				}
				case eMetadataTypeUint32:
				{
					std::cout << *(unsigned int*)metadata.data;
					break;
				}
				case eMetadataTypeInt32:
				{
					std::cout << *(int*)metadata.data;
					break;
				}
				case eMetadataTypeUint64:
				{
					break;
				}
				case eMetadataTypeInt64:
				{
					break;
				}
				case eMetadataTypeHalf:
				{
					break;
				}
				case eMetadataTypeFloat:
				{
					std::cout << *(float*)metadata.data;
					break;
				}
				case eMetadataTypeDouble:
				{
					std::cout << *(double*)metadata.data;
					break;
				}
				case eMetadataTypeString:
				{
					std::cout << *(const char*)metadata.data;
					break;
				}
				case eMetadataTypeRatio:
				{
					break;
				}
				case eMetadataTypeGroup:
				{
					std::cout << std::endl;
					Metadata* subMetadata = (Metadata*)metadata.data;
					printMetadata( subMetadata, level + 1 );
					break;
				}
			}
			if( metadata.mapped != nullptr )
			{
				std::cout << " - " << metadata.mapped;
			}
			if( metadata.type != eMetadataTypeGroup )
			{
				std::cout << std::endl;
			}
			++index;
		}
	}
}
#endif
