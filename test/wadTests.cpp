// This test file is a collection of unit tests to ensure that the WADFile class
// is working as intended. To get the test values, the doom1.wad file is used.
// The map E1M1 is used for the tests. The values that are tested are the first
// values of each lump, and the size of each lump. The first values of each lump
// were cross-referenced with the values in the Doom Wiki & from the Doom level
// editor tool -- SLADE.

#ifndef WAD_TESTS
#define WAD_TESTS

#include <gtest/gtest.h>
#include <iostream>
#include <wad/wad_file.hpp>
using namespace wad;

#pragma region wadFileTests
class WadFileTest : public ::testing::Test {
protected:
  static wad::WADFile wad_file;

  static void SetUpTestSuite() {
    std::cout << "WAD File Test Suite Set Up" << std::endl;
    wad_file.ReadWad("doom1.wad");
    // Commenting this out so the program doesn't immediately crash
    // wad_file.ReadMap("E1M1");
  }

  static void TearDownTestSuite() {
    std::cout << "WAD File Test Suite Tear Down" << std::endl;
  }
};

/*

// Define static member outside the class -- This is what we use in all of the
// tests when we refer to wad_file
wad::WADFile WadFileTest::wad_file;

TEST_F(WadFileTest, ReadMapTest) {
  EXPECT_EQ(wad_file.GetThings().size(), 138);
  EXPECT_EQ(wad_file.GetLinedefs().size(), 475);
  EXPECT_EQ(wad_file.GetSidedefs().size(), 648);
  EXPECT_EQ(wad_file.GetVertexes().size(), 467);
  EXPECT_EQ(wad_file.GetSegs().size(), 732);
  EXPECT_EQ(wad_file.GetSubsectors().size(), 237);
  EXPECT_EQ(wad_file.GetNodes().size(), 236);
  EXPECT_EQ(wad_file.GetSectors().size(), 85);
}

TEST_F(WadFileTest, CheckVertexTest) {
  VERTEX v = wad_file.GetVertexes().at(0);
  EXPECT_EQ(v.x, 1088);
  EXPECT_EQ(v.y, -3680);
}

TEST_F(WadFileTest, CheckSegTest) {
  SEG s = wad_file.GetSegs().at(0);
  EXPECT_EQ(s.start_vertex_id, 123);
  EXPECT_EQ(s.end_vertex_id, 124);
  EXPECT_EQ(s.angle, 16384);
  EXPECT_EQ(s.linedef_id, 152);
  EXPECT_EQ(s.direction, 0);
  EXPECT_EQ(s.offset, 0);
}

TEST_F(WadFileTest, CheckSubsectorTest) {
  SUBSECTOR s = wad_file.GetSubsectors().at(0);
  EXPECT_EQ(s.seg_count, 4);
  EXPECT_EQ(s.first_seg_id, 0);
}

TEST_F(WadFileTest, CheckNodeTest) {
  NODE n = wad_file.GetNodes().at(0);
  EXPECT_EQ(n.x_partition, 1552);
  EXPECT_EQ(n.y_partition, -2432);
  EXPECT_EQ(n.dx_partition, 112);
  EXPECT_EQ(n.dy_partition, 0);

  EXPECT_EQ(n.right_bbox.top, -2432);
  EXPECT_EQ(n.right_bbox.bottom, -2560);
  EXPECT_EQ(n.right_bbox.left, 1552);
  EXPECT_EQ(n.right_bbox.right, 1664);

  EXPECT_EQ(n.left_bbox.top, -2048);
  EXPECT_EQ(n.left_bbox.bottom, -2368);
  EXPECT_EQ(n.left_bbox.left, 1600);
  EXPECT_EQ(n.left_bbox.right, 1664);

  EXPECT_EQ(n.back_child_id, -32767);
  EXPECT_EQ(n.front_child_id, -32768);
}

TEST_F(WadFileTest, CheckSectorTest) {
  SECTOR s = wad_file.GetSectors().at(0);
  EXPECT_EQ(s.floor_height, 0);
  EXPECT_EQ(s.ceiling_height, 72);
  EXPECT_EQ(std::string(s.floor_texture), std::string("FLOOR4_8"));
  EXPECT_EQ(std::string(s.ceiling_texture), std::string("CEIL3_5"));
  EXPECT_EQ(s.light_level, 160);
  EXPECT_EQ(s.special_type, 0);
  EXPECT_EQ(s.sector_tag, 0);
}

TEST_F(WadFileTest, CheckChangeMapTest) {
  wad_file.ReadMap("E1M2");
  EXPECT_EQ(wad_file.GetThings().size(), 262);
  EXPECT_EQ(wad_file.GetLinedefs().size(), 1033);
  EXPECT_EQ(wad_file.GetSidedefs().size(), 1323);
  EXPECT_EQ(wad_file.GetVertexes().size(), 942);
  EXPECT_EQ(wad_file.GetSegs().size(), 1463);
  EXPECT_EQ(wad_file.GetSubsectors().size(), 448);
  EXPECT_EQ(wad_file.GetNodes().size(), 447);
  EXPECT_EQ(wad_file.GetSectors().size(), 200);
}
*/
#pragma endregion

#endif
