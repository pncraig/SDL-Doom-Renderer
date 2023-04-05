#ifndef DATATYPES_H
#define DATATYPES_H

#include <iostream>

// Header file that contains all the data types necessary to run Doom

// A WAD file always starts with a 12 byte header
struct Header
{
	char WADType[5];				// Whether the WAD file is an IWAD or a PWAD (IWAD = created by id, PWAD = created by modders)
	uint32_t DirectoryCount{};		// Number of directories contained in the WAD file
	uint32_t DirectoryOffset{};		// Number of bytes from the start of the file to the first directory
};

// Associates names of lumps with the data that belongs to them
struct Directory
{
	uint32_t LumpOffset{};		// Number of bytes from the beginning of the file to the lump
	uint32_t LumpSize{};		// Size in bytes of the lump
	char LumpName[9];			// Name of the lump (limited to 8 characters)
};

struct Vertex
{
	int16_t x{};
	int16_t y{};
};

struct Linedef
{
	int16_t StartVertex{};
	int16_t EndVertex{};

};

#endif
