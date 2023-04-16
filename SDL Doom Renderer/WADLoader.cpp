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

	if (!readMapNodes(map))
	{
		std::cerr << "Unable to load nodes for map " << map.getMapName() << '\n';
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
	std::cout << header.directoryOffset << "\n\n";*/

	// Create a directory instance
	Directory directory;

	// Loop through every directory in the WAD file
	for (int i{ 0 }; i < header.directoryCount; i++)
	{
		// Read the data from the file into the directory. The offset is header.directoryOffset + i * 16 because the directories start at 
		// header.directoryOffset, i is the number of the directory the loop is on, and 16 is the size of a directory in bytes
		reader.readDirectoryData(m_WADData, header.directoryOffset + i * 16, directory);

		// Add the directory to the list of directories
		m_WADDirectories.push_back(directory);

		/*std::cout << directory.lumpName << '\n';
		std::cout << directory.lumpOffset << '\n';
		std::cout << directory.lumpSize << "\n\n";*/
	}

	return true;
}

int WADLoader::findMapIndex(Map& map)
{
	std::string name{ map.getMapName() };
	for (int i{ 0 }; i < m_WADDirectories.size(); i++)
	{
		if (m_WADDirectories[i].lumpName == name)
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
	if (strcmp(vertexDirectory.lumpName, "VERTEXES") != 0)
		return false;

	Vertex vertex{};

	int sizeOfVertex{ sizeof(Vertex) };

	// Loop through all the data in the vertexes lump and add it to the map vector
	for (int i{ 0 }; i < vertexDirectory.lumpSize; i += sizeOfVertex)		// Add 4 because the vertex datatype is 4 bytes
	{
		reader.readVertexData(m_WADData, vertexDirectory.lumpOffset + i, vertex);

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
	if (strcmp(linedefDirectory.lumpName, "LINEDEFS") != 0)
		return false;

	Linedef linedef{};

	int sizeOfLinedef{ sizeof(Linedef) };

	// Loop through all the data in the vertexes lump and add it to the map vector
	for (int i{ 0 }; i < linedefDirectory.lumpSize; i += sizeOfLinedef)	// Add 14 because a linedef is 14 bytes
	{
		reader.readLinedefData(m_WADData, linedefDirectory.lumpOffset + i, linedef);

		/*std::cout << linedef.startVertex << '\n';
		std::cout << linedef.endVertex << '\n';
		std::cout << linedef.flags << '\n';
		std::cout << linedef.specialType << '\n';
		std::cout << linedef.sectorTag << '\n';
		std::cout << linedef.frontSidedef << '\n';
		std::cout << linedef.backSidedef << "\n\n";*/

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

	if (strcmp(directory.lumpName, "THINGS") != 0)
		return false;

	Thing thing;

	int sizeOfThing{ sizeof(Thing) };

	for (int i{ 0 }; i < directory.lumpSize; i += sizeOfThing)
	{
		reader.readThingData(m_WADData, directory.lumpOffset + i, thing);

		/*std::cout << thing.x << '\n';
		std::cout << thing.y << '\n';
		std::cout << thing.a << '\n';
		std::cout << thing.type << '\n';
		std::cout << thing.flags << "\n\n";*/

		map.addThing(thing);
	}

	map.initPlayer();

	return true;
}

bool WADLoader::readMapNodes(Map& map)
{
	WADReader reader;

	int mapIndex{ findMapIndex(map) };

	if (mapIndex == -1)
		return false;

	Directory directory{ m_WADDirectories[mapIndex + MapNodes] };

	if (strcmp(directory.lumpName, "NODES") != 0)
		return false;

	Node node{};

	int sizeOfNode{ sizeof(Node) };

	for (int i{ 0 }; i < directory.lumpSize; i += sizeOfNode)
	{
		reader.readNodeData(m_WADData, directory.lumpOffset + i, node);

		/*std::cout << node.startX << '\n';
		std::cout << node.startY << '\n';
		std::cout << node.changeX << '\n';
		std::cout << node.changeY << '\n';
		std::cout << "{ " << node.rightBox[0] << ", " << node.rightBox[1] << ", " << node.rightBox[2] << ", " << node.rightBox[3] << " }\n";
		std::cout << "{ " << node.leftBox[0] << ", " << node.leftBox[1] << ", " << node.leftBox[2] << ", " << node.leftBox[3] << " }\n";
		std::cout << node.rightChild << '\n';
		std::cout << node.leftChild << "\n\n";*/

		map.addNode(node);
	}

	return true;
}