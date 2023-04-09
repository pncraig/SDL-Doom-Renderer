#include "WADLoader.h"

// Public
WADLoader::WADLoader(std::string fileName)
	: m_WADFileName{ fileName }
{

}

WADLoader::~WADLoader()
{
	delete[] m_WADData;
}

bool WADLoader::load()
{
	if (!openAndLoad())
		return false;

	readDirectories();

	return true;
}

bool WADLoader::loadMapData(Map& map)
{
	if (!readMapVertices(map))
	{
		std::cerr << "Unable to load vertices for map " << map.getMapName() << '\n';
		return false;
	}

	if (!readMapLinedefs(map))
	{
		std::cerr << "Unable to load linedefs for map " << map.getMapName() << '\n';
		return false;
	}

	if (!readMapThings(map))
	{
		std::cerr << "Unable to load things for map " << map.getMapName() << '\n';
		return false;
	}

	return true;
}

// Private
bool WADLoader::openAndLoad()
{
	std::cout << "Loading " << m_WADFileName << '\n';

	// Open the WAD file, and return an error if the file doesn't open
	m_WADFile.open(m_WADFileName.c_str(), std::ifstream::binary);
	if (!m_WADFile.is_open())
	{
		std::cerr << "WAD file cannot be opened at " << m_WADFileName << '\n';
		return false;
	}

	// Move the position of the file pointer to the end to determine the length of the file
	m_WADFile.seekg(0, m_WADFile.end);
	std::size_t length{ static_cast<std::size_t>(m_WADFile.tellg()) };

	// Create an array to store the data from the file
	m_WADData = new uint8_t[length];

	if (m_WADData == nullptr)
	{
		std::cerr << "Error allocating data for WAD file of length " << length << '\n';
		return false;
	}

	// Move the pointer to the beginning of the file and read the data into m_WADFile
	m_WADFile.seekg(std::istream::beg);
	m_WADFile.read((char*)m_WADData, length);

	m_WADFile.close();

	std::cout << "Finished loading " << m_WADFileName << '\n';
	return true;
}

bool WADLoader::readDirectories()
{
	// Create an instance of the WADReader class
	WADReader reader;

	// Create a header instance and fill it with data
	Header header;
	reader.readHeaderData(m_WADData, 0, header);

	/*std::cout << header.WADType << '\n';
	std::cout << header.DirectoryCount << '\n';
	std::cout << header.DirectoryOffset << "\n\n";*/

	// Create a directory instance
	Directory directory;

	// Loop through every directory in the WAD file
	for (int i{ 0 }; i < header.DirectoryCount; i++)
	{
		// Read the data from the file into the directory. The offset is header.DirectoryOffset + i * 16 because the directories start at 
		// header.DirectoryOffset, i is the number of the directory the loop is on, and 16 is the size of a directory in bytes
		reader.readDirectoryData(m_WADData, header.DirectoryOffset + i * 16, directory);

		// Add the directory to the list of directories
		m_WADDirectories.push_back(directory);

		/*std::cout << directory.LumpName << '\n';
		std::cout << directory.LumpOffset << '\n';
		std::cout << directory.LumpSize << "\n\n";*/
	}

	return true;
}

int WADLoader::findMapIndex(Map& map)
{
	std::string name{ map.getMapName() };
	for (int i{ 0 }; i < m_WADDirectories.size(); i++)
	{
		if (m_WADDirectories[i].LumpName == name)
			return i;
	}
	return -1;
}

bool WADLoader::readMapVertices(Map& map)
{
	WADReader reader;
	
	// Get the map index
	int mapIndex{ findMapIndex(map) };

	if (mapIndex == -1)
		return false;

	// Locate the vertex directory that belongs to the map
	Directory vertexDirectory{ m_WADDirectories[mapIndex + MapVertices] };

	// Make sure the directory is the vertex directory
	if (strcmp(vertexDirectory.LumpName, "VERTEXES") != 0)
		return false;

	Vertex vertex{};

	int sizeOfVertex{ sizeof(Vertex) };

	// Loop through all the data in the vertexes lump and add it to the map vector
	for (int i{ 0 }; i < vertexDirectory.LumpSize; i += sizeOfVertex)		// Add 4 because the vertex datatype is 4 bytes
	{
		reader.readVertexData(m_WADData, vertexDirectory.LumpOffset + i, vertex);

		// std::cout << "(" << vertex.x << ", " << vertex.y << ")\n";

		map.addVertex(vertex);
	}

	return true;
};

bool WADLoader::readMapLinedefs(Map& map)
{
	WADReader reader;

	int mapIndex{ findMapIndex(map) };

	if (mapIndex == -1)
		return false;

	// Locate linedef directory that belongs to the map
	Directory linedefDirectory{ m_WADDirectories[mapIndex + MapLinedefs] };

	// Make sure the directory is actually the linedef directory
	if (strcmp(linedefDirectory.LumpName, "LINEDEFS") != 0)
		return false;

	Linedef linedef{};

	int sizeOfLinedef{ sizeof(Linedef) };

	// Loop through all the data in the vertexes lump and add it to the map vector
	for (int i{ 0 }; i < linedefDirectory.LumpSize; i += sizeOfLinedef)	// Add 14 because a linedef is 14 bytes
	{
		reader.readLinedefData(m_WADData, linedefDirectory.LumpOffset + i, linedef);

		/*std::cout << linedef.StartVertex << '\n';
		std::cout << linedef.EndVertex << '\n';
		std::cout << linedef.Flags << '\n';
		std::cout << linedef.SpecialType << '\n';
		std::cout << linedef.SectorTag << '\n';
		std::cout << linedef.FrontSidedef << '\n';
		std::cout << linedef.BackSidedef << "\n\n";*/

		map.addLinedef(linedef);
	}

	return true;
}

bool WADLoader::readMapThings(Map& map)
{
	WADReader reader;

	int mapIndex{ findMapIndex(map) };

	if (mapIndex == -1)
		return false;

	Directory directory{ m_WADDirectories[mapIndex + MapThings] };

	if (strcmp(directory.LumpName, "THINGS") != 0)
		return false;

	Thing thing;

	int sizeOfThing{ sizeof(Thing) };

	for (int i{ 0 }; i < directory.LumpSize; i += sizeOfThing)
	{
		reader.readThingData(m_WADData, directory.LumpOffset + i, thing);

		std::cout << thing.x << '\n';
		std::cout << thing.y << '\n';
		std::cout << thing.a << '\n';
		std::cout << thing.Type << '\n';
		std::cout << thing.Flags << "\n\n";

		map.addThing(thing);
	}

	return true;
}