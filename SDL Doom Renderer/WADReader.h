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

	void readHeaderData(const uint8_t* pWADData, int offset, Header& header);			// Read data from pWADData into a header
	
	void readDirectoryData(const uint8_t* pWADData, int offset, Directory& directory);	// Read data from pWADData into a directory
};

#endif

