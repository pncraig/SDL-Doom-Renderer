#ifndef WADLOADER_H
#define WADLOADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "DataTypes.h"
#include "WADReader.h"

// Class that stores the data extracted from a WAD file

class WADLoader
{
private:
	std::string m_WADFileName{};				// Name of the WAD file
	std::ifstream m_WADFile{};					// File stream that accesses the WAD file
	uint8_t* m_WADData;							// An array of 8-bit integers that stores the data from the WAD file
	std::vector<Directory> m_WADDirectories{};	// Vector that contains a Directory datatype for each directory in the WAD file

	bool openAndLoad();			// Opens the WAD file and reads all the data into m_WADData
	bool readDirectories();		// Adds all the directories into m_WADDirectories

public:
	WADLoader(std::string fileName);

	bool load();

	~WADLoader();
};

#endif

