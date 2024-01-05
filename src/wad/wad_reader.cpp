#include "wad_reader.hpp"
#include <iomanip>
#include <cstring>



namespace wad {

    void PrintCharsToHex(std::vector<unsigned char> bytes) {
        std::cout << "[ ";
        for (unsigned char byte : bytes) {
            std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
        }
        std::cout << "]" << std::endl;
    }


    void PrintHeader(WADHeader header) {
        std::cout << "+---------------------------------+" << std::endl;
        std::cout << "| WAD Filetype: " << header.wad_type << std::endl;
        std::cout << "| Lump Count: " << header.lump_count << std::endl;
        std::cout << "| Initial Offset: " << header.init_offset << std::endl;
        std::cout << "+---------------------------------+" << std::endl;
    }


    void PrintLump(WADLump lump) {
        std::cout << "+---------------------------------+" << std::endl;
        std::cout << "| Lump Position: " << lump.lump_pos << std::endl;
        std::cout << "| Lump Size: " << lump.lump_size << std::endl;
        std::cout << "| Lump Name: " << lump.lump_name << std::endl;
        std::cout << "+---------------------------------+\n" << std::endl;
    }


    // WADReader Functions
    WADReader::WADReader(std::string wad_path) {
        this->wad_path = wad_path;

        std::ifstream file(wad_path, std::ios::binary | std::ios::ate);
        if (file) {
            std::streamsize size = file.tellg();
            file.seekg(0, std::ios::beg);

            buffer.resize(size);
            if(!file.read(buffer.data(), size)) {
                // Handle error
            }
        } else {
            std::cout << "No file found!\n";
            exit(0);   
        }
        
        // Initialize the WAD Info
        this->header = this->ReadHeader();

        this->dir = this->ReadDir();
        int vertex_count = 0;
    }

    WADHeader WADReader::ReadHeader() {
        WADHeader header;
        header.wad_type = ReadBytesToString(this->buffer, 0, 4);
        header.lump_count = ReadBytesToInt32(this->buffer, 4, 4);
        header.init_offset = ReadBytesToInt32(this->buffer, 8, 4);
        return header;
    }


    WADDir WADReader::ReadDir() {
        WADDir dir;
        for(int i = 0; i < this->header.lump_count;i++) {
            int offset = this->header.init_offset + i * 16;
            WADLump lump;
            lump.lump_pos = ReadBytesToInt32(this->buffer, offset, 4);
            lump.lump_size = ReadBytesToInt32(this->buffer, offset + 4, 4);
            std::string name = ReadBytesToString(this->buffer, offset + 8, 8);
            lump.lump_name = Trim(name);
            dir.lumps.push_back(lump);
        }
        return dir;
    }


    THING WADReader::ReadThing(int offset) {
        THING output;
        output.x_pos = ReadBytesToInt16(this->buffer, offset, 2);
        output.y_pos = ReadBytesToInt16(this->buffer, offset + 2, 2);
        output.angle = ReadBytesToInt16(this->buffer, offset + 4, 2);
        output.thing_type = ReadBytesToInt16(this->buffer, offset + 6, 2);
        output.flags = ReadBytesToInt16(this->buffer, offset + 8, 2);
        return output;
    }

    LINEDEF WADReader::ReadLinedef(int offset) {
        LINEDEF output;
        output.start_vertex = ReadBytesToInt16(this->buffer, offset, 2);
        output.end_vertex = ReadBytesToInt16(this->buffer, offset + 2, 2);
        output.flags = ReadBytesToInt16(this->buffer, offset + 4, 2);
        output.special_type = ReadBytesToInt16(this->buffer, offset + 6, 2);
        output.sector_tag = ReadBytesToInt16(this->buffer , offset + 8, 2);
        output.front_sidedef = ReadBytesToInt16(this->buffer, offset + 10, 2);
        output.back_sidedef = ReadBytesToInt16(this->buffer, offset + 12, 2);
        return output;
    }

    SIDEDEF WADReader::ReadSidedef(int offset) {
        SIDEDEF output;
        output.x_offset = ReadBytesToInt16(this->buffer, offset, 2);
        output.y_offset = ReadBytesToInt16(this->buffer, offset + 2, 2);
        std::string upper_texture = ReadBytesToString(this->buffer, offset + 4, 8);
        std::string lower_texture = ReadBytesToString(this->buffer, offset + 12, 8);
        std::string middle_texture = ReadBytesToString(this->buffer, offset + 20, 8);
        // Convert the upper_texture, lower_texture, and middle_texture to a usable 8 character array of chars
        for (int i = 0; i < 8; i++) {
            output.upper_texture[i] = upper_texture[i];
            output.lower_texture[i] = lower_texture[i];
            output.middle_texture[i] = middle_texture[i];
        }
        output.sector_id = ReadBytesToInt16(this->buffer, offset + 28, 2);
        return output;
    }

    VERTEX WADReader::ReadVertex(int offset) {
        int16_t x = ReadBytesToInt16(this->buffer, offset, 2);
        int16_t y = ReadBytesToInt16(this->buffer, offset + 2, 2);

        VERTEX output = {x, y}; 
        return output;
    }

    SEG WADReader::ReadSeg(int offset) {
        SEG output;
        output.start_vertex_id = ReadBytesToInt16(this->buffer, offset, 2);
        output.end_vertex_id = ReadBytesToInt16(this->buffer, offset + 2, 2);
        output.angle = ReadBytesToInt16(this->buffer, offset + 4, 2);
        output.linedef_id = ReadBytesToInt16(this->buffer, offset + 6, 2);
        output.direction = ReadBytesToInt16(this->buffer, offset + 8, 2);
        output.offset = ReadBytesToInt16(this->buffer, offset + 10, 2);
        return output;
    }

    SUBSECTOR WADReader::ReadSubsector(int offset) {
        SUBSECTOR output;
        output.seg_count = ReadBytesToInt16(this->buffer, offset, 2);
        output.first_seg_id = ReadBytesToInt16(this->buffer, offset + 2, 2);
        return output;
    }

    BBox WADReader::ReadBBox(int offset) {
        BBox output;
        output.top = ReadBytesToInt16(this->buffer, offset, 2);
        output.bottom = ReadBytesToInt16(this->buffer, offset + 2, 2);
        output.left = ReadBytesToInt16(this->buffer, offset + 4, 2);
        output.right = ReadBytesToInt16(this->buffer, offset + 6, 2);
        return output;
    }

    NODE WADReader::ReadNode(int offset) {
        NODE output;
        output.x_partition = ReadBytesToInt16(this->buffer, offset, 2);
        output.y_partition = ReadBytesToInt16(this->buffer, offset + 2, 2);
        output.dx_partition = ReadBytesToInt16(this->buffer, offset + 4, 2);
        output.dy_partition = ReadBytesToInt16(this->buffer, offset + 6, 2);
        output.right_bbox = this->ReadBBox(offset + 8);
        output.left_bbox = this->ReadBBox(offset + 16);
        output.front_child_id = ReadBytesToInt16(this->buffer, offset + 24, 2);
        output.back_child_id = ReadBytesToInt16(this->buffer, offset + 26, 2);
        return output;
    }

    SECTOR WADReader::ReadSector(int offset) {
        SECTOR output;
        output.floor_height = ReadBytesToInt16(this->buffer, offset, 2);
        output.ceiling_height = ReadBytesToInt16(this->buffer, offset + 2, 2);
        output.floor_texture = ReadBytesToString(this->buffer, offset + 4, 8);
        output.ceiling_texture = ReadBytesToString(this->buffer, offset + 12, 8);
        output.light_level = ReadBytesToInt16(this->buffer, offset + 20, 2);
        output.special_type = ReadBytesToInt16(this->buffer, offset + 22, 2);
        output.sector_tag = ReadBytesToInt16(this->buffer, offset + 24, 2);
        return output;
    }

    REJECT WADReader::ReadReject(int offset) {
        REJECT output;
        output.num_reject = ReadBytesToInt16(this->buffer, offset, 2);
        output.first_reject = ReadBytesToInt16(this->buffer, offset + 2, 2);
        return output;
    }

    BLOCKMAP WADReader::ReadBlockmap(int offset) {
        BLOCKMAP output;
        output.origin_x = ReadBytesToInt16(this->buffer, offset, 2);
        output.origin_y = ReadBytesToInt16(this->buffer, offset + 2, 2);
        return output;
    }
}