#include "WADLoader.h"

WADLoader::WADLoader(std::string fileName)
	: m_WADFileName{ fileName }
{

}

WADLoader::~WADLoader()
{
	delete[] m_WADData;
}

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

	std::cout << header.WADType << '\n';
	std::cout << header.DirectoryCount << '\n';
	std::cout << header.DirectoryOffset << "\n\n";

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

		std::cout << directory.LumpName << '\n';
		std::cout << directory.LumpOffset << '\n';
		std::cout << directory.LumpSize << "\n\n";
	}

	return true;
}

bool WADLoader::load()
{
	if (!openAndLoad())
		return false;

	readDirectories();

	return true;
}