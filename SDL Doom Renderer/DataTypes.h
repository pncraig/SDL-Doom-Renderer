#ifndef DATATYPES_H
#define DATATYPES_H

#include <iostream>

// Header file that contains all the data types necessary to run Doom

// A WAD file always starts with a 12 byte header
struct Header
{
	char WADType[5]{};				// Whether the WAD file is an IWAD or a PWAD (IWAD = created by id, PWAD = created by modders)
	uint32_t DirectoryCount{};		// Number of directories contained in the WAD file
	uint32_t DirectoryOffset{};		// Number of bytes from the start of the file to the first directory
};

// Associates names of lumps with the data that belongs to them (16 bytes)
struct Directory
{
	uint32_t LumpOffset{};		// Number of bytes from the beginning of the file to the lump
	uint32_t LumpSize{};		// Size in bytes of the lump
	char LumpName[9]{};			// Name of the lump (limited to 8 characters)
};

// 4 byte structure that holds a point on the map
struct Vertex
{
	int16_t x{};
	int16_t y{};
};

// 14 byte structure that defines a wall
struct Linedef
{
	int16_t StartVertex{};		// Index of the start vertex in the vertices array
	int16_t EndVertex{};		// Index of the end vertex
	int16_t Flags{};
	int16_t SpecialType{};
	int16_t SectorTag{};
	int16_t FrontSidedef{};
	int16_t BackSidedef{};
};

// Linedef flags
#define BLOCKING		0b0000'0001		// (1) Blocks player and monsters
#define BLOCK_MONSTERS	0b0000'0010		// (2) Blocks only monsters
#define TWO_SIDED		0b0000'0100		// (4) Does the linedef have two sides
#define UPPER_UNPEGGED	0b0000'1000		// (8)
#define LOWER_UNPEGGED	0b0001'0000		// (16)
#define SECRET			0b0010'0000		// (32) Don't map as two sided in automap
#define BLOCK_SOUND		0b0100'0000		// (64) Blocks sound
#define DONT_DRAW		0b1000'0000		// (128) Don't draw on the automap
#define MAPPED		0b001'0000'0000		// (256) Set if already seen, thus drawn on automap

// 10 byte structure that represents players, monsters, projectiles, and pickups
struct Thing
{
	int16_t x{};
	int16_t y{};
	int16_t a{};
	int16_t Type{};
	int16_t Flags{};
};

#endif
