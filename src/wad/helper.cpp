#include "helper.hpp"

namespace wad {
// Helper Functions
std::string BytesToString(std::vector<unsigned char> bytes) {
  std::string output(bytes.begin(), bytes.end());
  return output;
}

int16_t LittleEndianToInt(std::vector<unsigned char> bytes) {
  return static_cast<uint16_t>(bytes[1]) << 8 | static_cast<uint16_t>(bytes[0]);
}

int32_t BytesToInt(std::vector<unsigned char> bytes) {
  return (bytes[3]) << 24 | static_cast<uint32_t>(bytes[2]) << 16 |
         static_cast<uint32_t>(bytes[1]) << 8 | static_cast<uint32_t>(bytes[0]);
}

std::string Trim(std::string &str) {
  int end_index = 0;
  for (char c : str) {
    if (static_cast<int>(c) == 0) {
      break;
    }
    end_index++;
  }
  if (end_index == str.size()) {
    return str;
  } else {
    return str.substr(0, end_index);
  }
}

std::vector<unsigned char> ReadBytes(std::vector<char> buffer, int offset,
                                     int num_bytes) {
  if (offset < 0 || offset + num_bytes > buffer.size()) {
    throw std::invalid_argument("Offset is out of bounds");
  }

  std::vector<unsigned char> bytes;
  for (int i = offset; i < offset + num_bytes; i++) {
    bytes.push_back(static_cast<unsigned char>(buffer[i]));
  }
  return bytes;
}

int16_t ReadBytesToInt16(std::vector<char> buffer, int offset, int num_bytes) {
  std::vector<unsigned char> bytes = ReadBytes(buffer, offset, num_bytes);
  return LittleEndianToInt(bytes);
}

int32_t ReadBytesToInt32(std::vector<char> buffer, int offset, int num_bytes) {
  std::vector<unsigned char> bytes = ReadBytes(buffer, offset, num_bytes);
  return BytesToInt(bytes);
}

std::string ReadBytesToString(std::vector<char> buffer, int offset,
                              int num_bytes) {
  std::vector<unsigned char> bytes = ReadBytes(buffer, offset, num_bytes);
  std::string bytes_string = BytesToString(bytes);
  std::string output = Trim(bytes_string);
  return output;
}
} // namespace wad
