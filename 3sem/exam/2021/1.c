#include <unistd.h>

typedef struct segment
{
    unsigned int base;
    unsigned int size;
} segment;

// 8-ми сегментная
unsigned int
VirtIntoPhys(segment *segTable, unsigned int VirtAdr)
{
    unsigned int SegNum = VirtAdr >> 29;
    unsigned int offset = (VirtAdr << 3) >> 3;

    if (offset > segTable[SegNum].size) {
        _exit(25);
    }

    return segTable[SegNum].base + offset;
}
