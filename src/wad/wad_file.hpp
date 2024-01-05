#ifndef WAD_DATA_HPP
#define WAD_DATA_HPP
#include "wad_reader.hpp"
#include "data_types.hpp"

namespace wad {
    class WADFile {
    private:
        WADReader *reader;
        int map_index;
        // Lump Data
        std::vector<THING> things;
        std::vector<LINEDEF> linedefs;
        std::vector<SIDEDEF> sidedefs;
        std::vector<VERTEX> vertexes;
        std::vector<SEG> segs;
        std::vector<SUBSECTOR> ssectors;
        std::vector<NODE> nodes;
        std::vector<SECTOR> sectors;
        std::vector<REJECT> rejects;
        std::vector<BLOCKMAP> blockmaps;

        // Lump reading
        int GetLumpIndex(std::string lump_name);
        std::vector<THING> ReadThingLump();
        std::vector<LINEDEF> ReadLinedefLump();
        std::vector<SIDEDEF> ReadSidedefLump();
        std::vector<VERTEX> ReadVertexLump();
        std::vector<SEG> ReadSegLump();
        std::vector<SUBSECTOR> ReadSubsectorLump();
        std::vector<NODE> ReadNodeLump();
        std::vector<SECTOR> ReadSectorLump();
        std::vector<REJECT> ReadRejectLump();
        std::vector<BLOCKMAP> ReadBlockmapLump();

    public:
        // Default Constructor
        WADFile();

        // Specific Constructors
        WADFile(std::string path);
        WADFile(std::string path, std::string map);

        // Deconstructor
        ~WADFile() {
            delete this->reader;
        };
        // Public Functions
        void ReadWad(std::string path);
        void ReadMap(std::string map);

        // Getters
        std::vector<VERTEX> GetVertexes() { return this->vertexes; };
        std::vector<LINEDEF> GetLinedefs() { return this->linedefs; };
        std::vector<THING> GetThings() { return this->things; };
        std::vector<SIDEDEF> GetSidedefs() { return this->sidedefs; };
        std::vector<SEG> GetSegs() { return this->segs; };
        std::vector<SUBSECTOR> GetSubsectors() { return this->ssectors; };
        std::vector<NODE> GetNodes() { return this->nodes; };
        std::vector<SECTOR> GetSectors() { return this->sectors; };
        std::vector<REJECT> GetRejects() { return this->rejects; };
        std::vector<BLOCKMAP> GetBlockmaps() { return this->blockmaps; };
    };
}
#endif