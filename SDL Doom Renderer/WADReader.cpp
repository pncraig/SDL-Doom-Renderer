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
	header.DirectoryCount = read4Bytes(pWADData, offset + 4);

	// 0x08 to 0x0b
	header.DirectoryOffset = read4Bytes(pWADData, offset + 8);
}

void WADReader::readDirectoryData(const uint8_t* pWADData, int offset, Directory& directory)
{
	// 0x00 to 0x03
	directory.LumpOffset = read4Bytes(pWADData, offset);

	// 0x04 to 0x07
	directory.LumpSize = read4Bytes(pWADData, offset + 4);

	// 0x08 to 0x0f
	directory.LumpName[0] = pWADData[offset + 8];
	directory.LumpName[1] = pWADData[offset + 9];
	directory.LumpName[2] = pWADData[offset + 10];
	directory.LumpName[3] = pWADData[offset + 11];
	directory.LumpName[4] = pWADData[offset + 12];
	directory.LumpName[5] = pWADData[offset + 13];
	directory.LumpName[6] = pWADData[offset + 14];
	directory.LumpName[7] = pWADData[offset + 15];
	directory.LumpName[8] = '\0';
}