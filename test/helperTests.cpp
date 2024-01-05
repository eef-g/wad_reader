#ifndef HELPER_TESTS
#define HELPER_TESTS

#include <gtest/gtest.h>
#include <wad/wad_file.hpp>



#pragma region helperTests
    TEST(helperTests, BytesToStringTest)
    {
        std::vector<unsigned char> bytes = {0x48, 0x65, 0x6c, 0x6c, 0x6f};
        std::string expected = "Hello";
        std::string actual = wad::BytesToString(bytes);
        EXPECT_EQ(expected, actual);
    }

    TEST(helperTests, LittleEndianToIntTest)
    {
        std::vector<unsigned char> bytes = {0x01, 0x00};
        int16_t expected = 1;
        int16_t actual = wad::LittleEndianToInt(bytes);
        EXPECT_EQ(expected, actual);
    }

    TEST(helperTests, BytesToIntTest)
    {
        std::vector<unsigned char> bytes = {0x01, 0x00, 0x00, 0x00};
        int32_t expected = 1;
        int32_t actual = wad::BytesToInt(bytes);
        EXPECT_EQ(expected, actual);
    }

    TEST(helperTests, TrimTest)
    {
        std::string str = "Hello\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
        std::string expected = "Hello";
        std::string actual = wad::Trim(str);
        EXPECT_EQ(expected, actual);
    }

    TEST(helperTests, ReadBytesTest)
    {
        std::vector<char> buffer = {'H', 'e', 'l', 'l', 'o'};
        std::vector<unsigned char> expected = {'e', 'l', 'l'};
        std::vector<unsigned char> actual = wad::ReadBytes(buffer, 1, 3);
        EXPECT_EQ(expected, actual);
    }

    TEST(helperTests, ReadBytesToInt16Test)
    {
        std::vector<char> buffer = { 0x00, 0x65, 0x00, 0x00};
        int16_t expected = 101;
        int16_t actual = wad::ReadBytesToInt16(buffer, 1, 2);
        EXPECT_EQ(expected, actual);
    }
#pragma endregion


#endif