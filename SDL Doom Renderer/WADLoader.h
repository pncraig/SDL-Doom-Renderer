#ifndef WADLOADER_H
#define WADLOADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "DataTypes.h"
#include "WADReader.h"
#include "Map.h"

// Class that stores the data extracted from a WAD file

class WADLoader
{
private:
	std::string m_WADFileName{};				// Name of the WAD file
	std::ifstream m_WADFile{};					// File stream that accesses the WAD file
	uint8_t* m_WADData{};						// An array of 8-bit integers that stores the data from the WAD file
	std::vector<Directory> m_WADDirectories{};	// Vector that contains a Directory datatype for each directory in the WAD file

	// How many indexes each thing is behind the index of the map directory. For example, the Things directory is 1 behind the directory of the map it belongs
	// to, while the Segs directory is 5 behind the map it belongs to 
	enum MapLumpIndex
	{
		MapThings = 1,
		MapLinedefs,
		MapSidedefs,
		MapVertices,
		MapSegs,
		MapSSectors,
		MapNodes,
		MapSectors,
		MapReject,
		MapBlockMap,
	};

	bool openAndLoad();			// Opens the WAD file and reads all the data into m_WADData
	bool readDirectories();		// Adds all the directories into m_WADDirectories

	int findMapIndex(Map& map);			// Returns the index of the directory of the map, or -1 if the map can't be found
	bool readMapVertices(Map& map);		// Reads the map vertices into a vector in the map
	bool readMapLinedefs(Map& map);		// Reads the map linedefs into a vector in the map
	bool readMapThings(Map& map);

public:
	WADLoader(std::string fileName);

	bool load();
	bool loadMapData(Map& map);

	~WADLoader();
};

#endif

