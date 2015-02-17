#include <iostream>
#include <inttypes.h>   // use intXX_t

#define PACK

#ifdef PACK
#pragma pack(push, 1)
#endif // PACK

namespace media_file {
    namespace ogg_file {
        class Header {
            public:
                int32_t capturePattern;         // OggS
                int8_t version;
                int8_t headerType;
                int64_t granulePosition;
                int32_t bitstreamSerialNumber;
                int32_t pageSequenceNumber;
                int32_t checksum;
                int8_t pageSegments;
        };
        class Ogg {
            public:
                Header header;
                int8_t *segmentTable;
        };
    }

    namespace midi_file {
        class MThd {    // Header
            public:
                int32_t chunkHeader;    // MThd
                int32_t headerLength;
                int16_t format;         //type
                int16_t numberOfTracks;
                int16_t division;
        };
        class MTrk {
            public:
                int16_t length;
                int8_t *data;
        };
        class midi {
            public:
                MThd header;
                MTrk data;
        };
    }

}

#ifdef PACK
#pragma pack(pop)
#endif // PACK


int main(void)
{
    std::cout << "PACK " <<
    #ifdef PACK
        "on"
    #else
        "off"
    #endif // PACK
    << std::endl;

    media_file::ogg_file::Ogg   oggFile;
    media_file::midi_file::midi midiFile;

    std::cout << "size of OGG header: " << sizeof(oggFile)  << std::endl;
    std::cout << "size of OGG header: " << sizeof(midiFile) << std::endl;
    return 0;
}
