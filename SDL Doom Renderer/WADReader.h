#ifndef WADREADER_H
#define WADREADER_H

#include<iostream>
#include "DataTypes.h"

// Class with helper functions to read data from the WAD file

class WADReader
{
private:

public:
	uint16_t read2Bytes(const uint8_t* pWADData, int offset);							// Reads 2 bytes of data from the file and return it

	uint32_t read4Bytes(const uint8_t* pWADData, int offset);							// Reads 4 bytes of data from the file and return it

	void readHeaderData(const uint8_t* pWADData, int offset, Header& header);			// Reads data from pWADData into a header
	
	void readDirectoryData(const uint8_t* pWADData, int offset, Directory& directory);	// Reads data from pWADData into a directory

	void readVertexData(const uint8_t* pWADData, int offset, Vertex& vertex);			// Reads data form pWADData into a vertex

	void readLinedefData(const uint8_t* pWADData, int offset, Linedef& linedef);		// Reads data from PWADData into a linedef

	void readThingData(const uint8_t* pWADData, int offset, Thing& thing);				// Reads data from pWADData into a thing

	void readNodeData(const uint8_t* pWADData, int offset, Node& node);					// Reads data from pWADData into a node
};

#endif

