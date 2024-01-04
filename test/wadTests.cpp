#include <gtest/gtest.h>
#include <wad/helper.hpp>

using namespace wad;

TEST(helperTests, BytesToString)
{
    std::vector<unsigned char> bytes = {0x48, 0x65, 0x6c, 0x6c, 0x6f};
    std::string expected = "Hello";
    std::string actual = BytesToString(bytes);
    EXPECT_EQ(expected, actual);
}

TEST(helperTests, LittleEndianToInt)
{
    std::vector<unsigned char> bytes = {0x01, 0x00};
    int16_t expected = 1;
    int16_t actual = LittleEndianToInt(bytes);
    EXPECT_EQ(expected, actual);
}

TEST(helperTests, BytesToInt)
{
    std::vector<unsigned char> bytes = {0x01, 0x00, 0x00, 0x00};
    int32_t expected = 1;
    int32_t actual = BytesToInt(bytes);
    EXPECT_EQ(expected, actual);
}

TEST(helperTests, Trim)
{
    std::string str = "Hello\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
    std::string expected = "Hello";
    std::string actual = Trim(str);
    EXPECT_EQ(expected, actual);
}

TEST(helperTests, ReadBytes)
{
    std::vector<char> buffer = {'H', 'e', 'l', 'l', 'o'};
    std::vector<unsigned char> expected = {'e', 'l', 'l'};
    std::vector<unsigned char> actual = ReadBytes(buffer, 1, 3);
    EXPECT_EQ(expected, actual);
}

TEST(helperTests, LittleEndianIntFromBytes)
{
    std::vector<char> buffer = { 0x00, 0x65, 0x00, 0x00};
    int16_t expected = 101;
    int16_t actual = ReadBytesToInt16(buffer, 1, 2);
    EXPECT_EQ(expected, actual);
}