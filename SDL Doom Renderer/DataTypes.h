#ifndef DATATYPES_H
#define DATATYPES_H

#include <iostream>

// Header file that contains all the data types necessary to run Doom

// A WAD file always starts with a 12 byte header
struct Header
{
	char WADType[5]{};				// Whether the WAD file is an IWAD or a PWAD (IWAD = created by id, PWAD = created by modders)
	uint32_t directoryCount{};		// Number of directories contained in the WAD file
	uint32_t directoryOffset{};		// Number of bytes from the start of the file to the first directory
};

// Associates names of lumps with the data that belongs to them (16 bytes)
struct Directory
{
	uint32_t lumpOffset{};		// Number of bytes from the beginning of the file to the lump
	uint32_t lumpSize{};		// Size in bytes of the lump
	char lumpName[9]{};			// Name of the lump (limited to 8 characters)
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
	int16_t startVertex{};		// Index of the start vertex in the vertices array
	int16_t endVertex{};		// Index of the end vertex
	int16_t flags{};
	int16_t specialType{};
	int16_t sectorTag{};
	int16_t frontSidedef{};
	int16_t backSidedef{};
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
	int16_t a{};		// Angle
	int16_t type{};		// What kind of thing it is
	int16_t flags{};
};

// A 28 byte structure that represents a node in the binary search tree
// The distinction between left and right is based on the direction of the partition vector
//					^												O
//					|												|
//		Left		|		Right		or			Right			|		Left
//					|												|
//					O												V
struct Node
{
	int16_t startX{};		// X-coordinate of partition line start
	int16_t startY{};		// Y-coordinate of partition line start
	int16_t changeX{};		// Change in x from the start of the partition line to the end
	int16_t changeY{};		// Change in y from the start of the partition line to the end
	int16_t rightBox[4]{};	// Bounding box for the parts of the map on the right side of the partition line. Format is { upperY, lowerY, leftmostX, rightmostX }
	int16_t leftBox[4]{};	// Bounding box for the parts of the map on the left side of the partition line
	int16_t rightChild{};	// Index value of the right child node. If the value is negative, that means it represents the index of a subsector and is the last node in that part of the tree
	int16_t leftChild{};	// Index value of the left child node
};

struct Subsector
{
	int16_t segCount{};
	int16_t firstSeg{};
};

struct Seg
{
	int16_t startVertex{};
	int16_t endVertex{};
	int16_t angle{};
	int16_t linedef{};
	int16_t direction{};
	int16_t offset{};
};

#endif
