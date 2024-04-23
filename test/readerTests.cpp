/* This is a test file to help debug the WADReader class.
 * At the moment, when the program is run on a UNIX system
 * it will crash when reading the Linedefs of a map in a WAD file.
 * For the doom1.wad file, it crashes at offset=75532
 */

#ifndef READ_TESTS
#define READ_TESTS

#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <iostream>
#include <ostream>
#include <wad/wad_reader.hpp>
using namespace wad;

#pragma region readerTests

class ReaderTests : public ::testing::Test {
protected:
  static wad::WADReader wad_reader;

  static void SetUpTestSuite() {
    std::cout << "ReaderTests Suite Set Up" << std::endl;
    wad_reader = WADReader("doom1.wad");
    std::cout << "ReaderTests Suite has been set up :)" << std::endl;
  }

  static void TearDownTestSuite() {
    std::cout << "ReaderTests Suite Tear Down" << std::endl;
  }
};

// Define static member outside the class -- This is what we use in all of the
// tests when we refer to wad_file

wad::WADReader ReaderTests::wad_reader;
TEST_F(ReaderTests, ReadLineDefSuccess) {
  LINEDEF def = wad_reader.ReadLinedef(0);
  EXPECT_EQ(def.start_vertex, 22345);
}

TEST_F(ReaderTests, ReadLinedefFail) {
  std::cout << "Expecting to fail here" << std::endl;
  LINEDEF def = wad_reader.ReadLinedef(75532);
  std::cout << "Test Concluded" << std::endl;
}

#pragma endregion

#endif
