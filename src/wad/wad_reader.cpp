#include "wad_reader.hpp"
#include <iomanip>



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


    std::vector<unsigned char> WADReader::ReadBytes(int offset, int num_bytes) {
        if (offset < 0 || offset + num_bytes > this->buffer.size()) { 
            exit(0);
        }

        std::vector<unsigned char> result(buffer.begin() + offset, buffer.begin() + offset + num_bytes);
        return result;
    }


    WADHeader WADReader::ReadHeader() {
        WADHeader header;
        header.wad_type = BytesToString(this->ReadBytes(0, 4));
        header.lump_count = this->BytesToInt(this->ReadBytes(4, 4));
        header.init_offset = this->BytesToInt(this->ReadBytes(8, 4));
        return header;
    }


    WADDir WADReader::ReadDir() {
        WADDir dir;
        for(int i = 0; i < this->header.lump_count;i++) {
            int offset = this->header.init_offset + i * 16;
            WADLump lump;
            lump.lump_pos = this->BytesToInt(this->ReadBytes(offset, 4));
            lump.lump_size = this->BytesToInt(this->ReadBytes(offset + 4, 4));
            std::string name = BytesToString(this->ReadBytes(offset + 8, 8));
            lump.lump_name = Trim(name);
            dir.lumps.push_back(lump);
        }
        return dir;
    }


    THING WADReader::ReadThing(int offset) {
        THING output;
        output.x_pos = LittleEndianToInt(this->ReadBytes(offset, 2));
        output.y_pos = LittleEndianToInt(this->ReadBytes(offset + 2, 2));
        output.angle = LittleEndianToInt(this->ReadBytes(offset + 4, 2));
        output.thing_type = LittleEndianToInt(this->ReadBytes(offset + 6, 2));
        output.flags = LittleEndianToInt(this->ReadBytes(offset + 8, 2));
        return output;
    }

    LINEDEF WADReader::ReadLinedef(int offset) {
        LINEDEF output;
        output.start_vertex = LittleEndianToInt(this->ReadBytes(offset, 2));
        output.end_vertex = LittleEndianToInt(this->ReadBytes(offset + 2, 2));
        output.flags = LittleEndianToInt(this->ReadBytes(offset + 4, 2));
        output.special_type = LittleEndianToInt(this->ReadBytes(offset + 6, 2));
        output.sector_tag = LittleEndianToInt(this->ReadBytes(offset + 8, 2));
        output.front_sidedef = LittleEndianToInt(this->ReadBytes(offset + 10, 2));
        output.back_sidedef = LittleEndianToInt(this->ReadBytes(offset + 12, 2));
        return output;
    }

    SIDEDEF WADReader::ReadSidedef(int offset) {
        SIDEDEF output;
        output.x_offset = LittleEndianToInt(this->ReadBytes(offset, 2));
        output.y_offset = LittleEndianToInt(this->ReadBytes(offset + 2, 2));
        std::string upper_texture = BytesToString(this->ReadBytes(offset + 4, 8));
        std::string lower_texture = BytesToString(this->ReadBytes(offset + 12, 8));
        std::string middle_texture = BytesToString(this->ReadBytes(offset + 20, 8));
        // Convert the upper_texture, lower_texture, and middle_texture to a usable 8 character array of chars
        for (int i = 0; i < 8; i++) {
            output.upper_texture[i] = upper_texture[i];
            output.lower_texture[i] = lower_texture[i];
            output.middle_texture[i] = middle_texture[i];
        }
        output.sector_id = LittleEndianToInt(this->ReadBytes(offset + 28, 2));
        return output;
    }

    VERTEX WADReader::ReadVertex(int offset) {
        int16_t x = LittleEndianToInt(this->ReadBytes(offset, 2));
        int16_t y = LittleEndianToInt(this->ReadBytes(offset + 2, 2));

        VERTEX output = {x, y}; 
        return output;
    }

    SEG WADReader::ReadSeg(int offset) {
        SEG output;
        output.start_vertex_id = LittleEndianToInt(this->ReadBytes(offset, 2));
        output.end_vertex_id = LittleEndianToInt(this->ReadBytes(offset + 2, 2));
        output.angle = LittleEndianToInt(this->ReadBytes(offset + 4, 2));
        output.linedef_id = LittleEndianToInt(this->ReadBytes(offset + 6, 2));
        output.direction = LittleEndianToInt(this->ReadBytes(offset + 8, 2));
        output.offset = LittleEndianToInt(this->ReadBytes(offset + 10, 2));
        return output;
    }

    SUBSECTOR WADReader::ReadSubsector(int offset) {
        SUBSECTOR output;
        output.seg_count = LittleEndianToInt(this->ReadBytes(offset, 2));
        output.first_seg_id = LittleEndianToInt(this->ReadBytes(offset + 2, 2));
        return output;
    }

    BBox WADReader::ReadBBox(int offset) {
        BBox output;
        output.top = LittleEndianToInt(this->ReadBytes(offset, 2));
        output.bottom = LittleEndianToInt(this->ReadBytes(offset + 2, 2));
        output.left = LittleEndianToInt(this->ReadBytes(offset + 4, 2));
        output.right = LittleEndianToInt(this->ReadBytes(offset + 6, 2));
        return output;
    }

    NODE WADReader::ReadNode(int offset) {
        NODE output;
        output.x_partition = LittleEndianToInt(this->ReadBytes(offset, 2));
        output.y_partition = LittleEndianToInt(this->ReadBytes(offset + 2, 2));
        output.dx_partition = LittleEndianToInt(this->ReadBytes(offset + 4, 2));
        output.dy_partition = LittleEndianToInt(this->ReadBytes(offset + 6, 2));
        output.left_bbox = this->ReadBBox(offset + 8);
        output.right_bbox = this->ReadBBox(offset + 16);
        output.front_child_id = LittleEndianToInt(this->ReadBytes(offset + 24, 2));
        output.back_child_id = LittleEndianToInt(this->ReadBytes(offset + 26, 2));
        return output;
    }

    SECTOR WADReader::ReadSector(int offset) {
        SECTOR output;
        output.floor_height = LittleEndianToInt(this->ReadBytes(offset, 2));
        output.ceiling_height = LittleEndianToInt(this->ReadBytes(offset + 2, 2));
        std::string floor_texture = BytesToString(this->ReadBytes(offset + 4, 8));
        std::string ceiling_texture = BytesToString(this->ReadBytes(offset + 12, 8));
        for (int i = 0; i < 8; i++) {
            output.floor_texture[i] = floor_texture[i];
            output.ceiling_texture[i] = ceiling_texture[i];
        }
        output.light_level = LittleEndianToInt(this->ReadBytes(offset + 20, 2));
        output.special_type = LittleEndianToInt(this->ReadBytes(offset + 22, 2));
        output.sector_tag = LittleEndianToInt(this->ReadBytes(offset + 24, 2));
        return output;
    }

    REJECT WADReader::ReadReject(int offset) {
        REJECT output;
        output.num_reject = LittleEndianToInt(this->ReadBytes(offset, 2));
        output.first_reject = LittleEndianToInt(this->ReadBytes(offset + 2, 2));
        return output;
    }

    BLOCKMAP WADReader::ReadBlockmap(int offset) {
        BLOCKMAP output;
        output.origin_x = LittleEndianToInt(this->ReadBytes(offset, 2));
        output.origin_y = LittleEndianToInt(this->ReadBytes(offset + 2, 2));
        return output;
    }
}