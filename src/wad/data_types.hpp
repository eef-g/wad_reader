#ifndef DATA_TYPES_HPP
#define DATA_TYPES_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

namespace wad {

    enum LUMP_INDICIES {
        THINGS = 1, LINEDEFS = 2, SIDEDEFS = 3, VERTEXES = 4, SEGS = 5,
        SSECTORS = 6, NODES = 7, SECTORS = 8, REJECTS = 9, BLOCKMAPS = 10,
    };

    struct THING {
        // 10 bytes
        int16_t x_pos;
        int16_t y_pos;
        int16_t angle;
        int16_t thing_type;
        int16_t flags;
    };

    enum THING_TYPE {
        ENEMY = 1, WEAPON = 2, AMMO = 3, ARTIFACT = 4,
        POWERUP = 5, KEY = 6, OBSTACLE = 7, DECOR = 8,
        OTHER = 9,  
    };

    struct ThingType {
        THING_TYPE type;
        std::vector<int> thing_numbers;
    };

    extern std::vector<ThingType> thing_types;
    THING_TYPE getThingType(int thing_type);

    struct LINEDEF {
        // 14 bytes total
        int16_t start_vertex;
        int16_t end_vertex;
        int16_t flags;
        int16_t special_type;
        int16_t sector_tag;
        int16_t front_sidedef;
        int16_t back_sidedef;
    };

    struct SIDEDEF {
        // 30 bytes total
        int16_t x_offset;
        int16_t y_offset;
        char upper_texture[8];
        char lower_texture[8];
        char middle_texture[8];
        int16_t sector_id;
    };

    struct VERTEX {
        // 4 bytes total
        int16_t x;
        int16_t y;
    };

    struct SEG {
        // 12 bytes total
        int16_t start_vertex_id;
        int16_t end_vertex_id;
        int16_t angle;
        int16_t linedef_id;
        int16_t direction;
        int16_t offset;
    };

    struct SUBSECTOR {
        // 4 bytes
        int16_t seg_count;
        int16_t first_seg_id;
    };

    struct BBox {
        // 8 bytes total
        int16_t top;
        int16_t bottom;
        int16_t left;
        int16_t right;
    };

    struct NODE {
        // 28 bytes total
        int16_t x_partition;
        int16_t y_partition;
        int16_t dx_partition;
        int16_t dy_partition;
        BBox left_bbox;
        BBox right_bbox;
        int16_t front_child_id;
        int16_t back_child_id;
    };

    struct SECTOR {
        // 26 bytes total
        int16_t floor_height;
        int16_t ceiling_height;
        std::string floor_texture;
        std::string ceiling_texture;
        int16_t light_level;
        int16_t special_type;
        int16_t sector_tag;
    };

    struct REJECT {
        // 4 bytes total
        int16_t num_reject;
        int16_t first_reject;
    };

    struct BLOCKMAP {
        // 4 bytes total
        int16_t origin_x;
        int16_t origin_y;
    };

}

#endif