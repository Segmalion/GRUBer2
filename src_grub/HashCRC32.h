//---------------------------------------------------------------------------

#ifndef HashCRC32H
#define HashCRC32H

#include <cstdint> // For uint32_t
#include <vector>  // For std::vector
//---------------------------------------------------------------------------
class Crc32Builder {
private:
	std::vector<uint32_t> crc_table;
	const uint32_t CRC32_POLYNOMIAL = 0x04C11DB7; // Standard CRC-32 polynomial

	void generate_table();

public:
	Crc32Builder();
	uint32_t calculate_crc(const uint8_t* data, size_t length) const;
};

#endif
