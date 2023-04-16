#include "WADReader.h"

uint16_t WADReader::read2Bytes(const uint8_t* pWADData, int offset)
{
	uint16_t readValue{};
	std::memcpy(&readValue, pWADData + offset, sizeof(uint16_t));
	return readValue;
}

uint32_t WADReader::read4Bytes(const uint8_t* pWADData, int offset)
{
	uint32_t readValue{};
	std::memcpy(&readValue, pWADData + offset, sizeof(uint32_t));
	return readValue;
}

void WADReader::readHeaderData(const uint8_t* pWADData, int offset, Header& header)
{
	// 0x00 to 0x03
	header.WADType[0] = pWADData[offset];
	header.WADType[1] = pWADData[offset + 1];
	header.WADType[2] = pWADData[offset + 2];
	header.WADType[3] = pWADData[offset + 3];
	header.WADType[4] = '\0';

	// 0x04 to 0x07
	header.directoryCount = read4Bytes(pWADData, offset + 4);

	// 0x08 to 0x0b
	header.directoryOffset = read4Bytes(pWADData, offset + 8);
}

void WADReader::readDirectoryData(const uint8_t* pWADData, int offset, Directory& directory)
{
	// 0x00 to 0x03
	directory.lumpOffset = read4Bytes(pWADData, offset);

	// 0x04 to 0x07
	directory.lumpSize = read4Bytes(pWADData, offset + 4);

	// 0x08 to 0x0f
	directory.lumpName[0] = pWADData[offset + 8];
	directory.lumpName[1] = pWADData[offset + 9];
	directory.lumpName[2] = pWADData[offset + 10];
	directory.lumpName[3] = pWADData[offset + 11];
	directory.lumpName[4] = pWADData[offset + 12];
	directory.lumpName[5] = pWADData[offset + 13];
	directory.lumpName[6] = pWADData[offset + 14];
	directory.lumpName[7] = pWADData[offset + 15];
	directory.lumpName[8] = '\0';
}

void WADReader::readVertexData(const uint8_t* pWADData, int offset, Vertex& vertex)
{
	vertex.x = read2Bytes(pWADData, offset);
	vertex.y = read2Bytes(pWADData, offset + 2);
}

void WADReader::readLinedefData(const uint8_t* pWADData, int offset, Linedef& linedef)
{
	linedef.startVertex = read2Bytes(pWADData, offset);
	linedef.endVertex = read2Bytes(pWADData, offset + 2);
	linedef.flags = read2Bytes(pWADData, offset + 4);
	linedef.specialType = read2Bytes(pWADData, offset + 6);
	linedef.sectorTag = read2Bytes(pWADData, offset + 8);
	linedef.frontSidedef = read2Bytes(pWADData, offset + 10);
	linedef.backSidedef = read2Bytes(pWADData, offset + 12);
}

void WADReader::readThingData(const uint8_t* pWADData, int offset, Thing& thing)
{
	thing.x = read2Bytes(pWADData, offset);
	thing.y = read2Bytes(pWADData, offset + 2);
	thing.a = read2Bytes(pWADData, offset + 4);
	thing.type = read2Bytes(pWADData, offset + 6);
	thing.flags = read2Bytes(pWADData, offset + 8);
}

void WADReader::readNodeData(const uint8_t* pWADData, int offset, Node& node)
{
	node.startX = read2Bytes(pWADData, offset);
	node.startY = read2Bytes(pWADData, offset + 2);
	node.changeX = read2Bytes(pWADData, offset + 4);
	node.changeY = read2Bytes(pWADData, offset + 6);
	
	for (int i{ 0 }; i < 4; i ++)
	{
		node.rightBox[i] = read2Bytes(pWADData, offset + 8 + i * 2);
	}

	for (int i{ 0 }; i < 4; i++)
	{
		node.leftBox[i] = read2Bytes(pWADData, offset + 16 + i * 2);
	}

	node.rightChild = read2Bytes(pWADData, offset + 24);
	node.leftChild = read2Bytes(pWADData, offset + 26);
}