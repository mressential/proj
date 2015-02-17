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
}

#ifdef PACK
#pragma pack(pop)
#endif // PACK


int main()
{
    media_file::ogg_file::Ogg oggFile;

    std::cout << sizeof(oggFile);
    return 0;
}
