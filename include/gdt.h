#ifndef __GDT_H
#define __GDT_H

// doc: https://qbz9bpil4a.feishu.cn/docx/ToykdBwUxoMWEexrMd6c2pdXnGf

#include "types.h"

class GlobalDescriptorTable
{
public:

    class SegmentDescriptor
    {
    private:
        // total 20bit
        // | ptr | limit | access | ptr | ptr | ptr | limit | limit |
        uint16_t limit_lo;  // limit  4bit
        uint16_t base_lo;   // ptr    4bit
        uint8_t  base_hi;   // ptr    3bit
        uint8_t  type;      // access 3bit
        uint8_t  limit_hi;  // limit  3bit
        uint8_t  base_vhi;  // ptr    3bit

    public:
        SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
        uint32_t Base();
        uint32_t Limit();
    } __attribute__((packed));

private:
    SegmentDescriptor nullSegmentSelector;
    SegmentDescriptor unusedSegmentSelector;
    SegmentDescriptor codeSegmentSelector;
    SegmentDescriptor dataSegmentSelector;

public:

    GlobalDescriptorTable();
    ~GlobalDescriptorTable();

    uint16_t CodeSegmentSelector();
    uint16_t DataSegmentSelector();
};

#endif