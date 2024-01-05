#ifndef HELPER_HPP
#define HELPER_HPP

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>

namespace wad {
    // Helper Functions
    std::string BytesToString(std::vector<unsigned char> bytes);

    int16_t LittleEndianToInt(std::vector<unsigned char> bytes); 

    int32_t BytesToInt(std::vector<unsigned char> bytes);

    std::string Trim(std::string& str); 

    std::vector<unsigned char> ReadBytes(std::vector<char> buffer, int offset, int num_bytes); 
    
    int16_t ReadBytesToInt16(std::vector<char> buffer, int offset, int num_bytes); 
    
    int32_t ReadBytesToInt32(std::vector<char> buffer, int offset, int num_bytes); 
        
    std::string ReadBytesToString(std::vector<char> buffer, int offset, int num_bytes); 
}
#endif