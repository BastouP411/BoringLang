#include "boringlang/memory/ObjectHeader.hpp"

#include "catch2/catch_all.hpp"

TEST_CASE("testDecodeHeader1", "[objectHeader]") {
    BoringLang::Memory::SlotOrHeader mem[] {
            0x1234ABCD00280000,
            0x0000000000000000
    };
    BoringLang::Memory::ObjectHeader header(mem);

    REQUIRE(!header.arrayed());
    REQUIRE(header.arraySlotSize() == BoringLang::Memory::BITS_64);
    REQUIRE(header.specialSection() == BoringLang::Memory::NONE);
    REQUIRE(!header.null());
    REQUIRE(header.length() == 40);
    REQUIRE(header.lengthWithHeader() == 48);
    REQUIRE(header.slotLength() == 5);
    REQUIRE(header.slotLengthWithHeader() == 6);
    REQUIRE(header.classPointer() == 0x1234ABCD);
}

TEST_CASE("testEncodeHeader1", "[objectHeader]") {
    BoringLang::Memory::SlotOrHeader mem[] {
            0x0000000000000000,
            0x123456789ABCDEF0
    };
    BoringLang::Memory::ObjectHeader header(mem);

    header.setArrayed(false);
    header.setArraySlotSize(BoringLang::Memory::BITS_64);
    header.setSpecialSection(BoringLang::Memory::NONE);
    header.setNull(false);
    header.setLength(40);
    header.setClassPointer(0x1234ABCD);

    REQUIRE(mem[0].slot == 0x1234ABCD00280000);
    REQUIRE(mem[1].slot == 0x123456789ABCDEF0);
}

TEST_CASE("testDecodeHeader2", "[objectHeader]") {
    BoringLang::Memory::SlotOrHeader mem[] {
            0xBE11EC1E007E002B,
            0x0000000000000000
    };
    BoringLang::Memory::ObjectHeader header(mem);

    REQUIRE(header.arrayed());
    REQUIRE(header.arraySlotSize() == BoringLang::Memory::BITS_32);
    REQUIRE(header.specialSection() == BoringLang::Memory::FREE);
    REQUIRE(header.null());
    REQUIRE(header.length() == 126);
    REQUIRE(header.lengthWithHeader() == 134);
    REQUIRE(header.slotLength() == 16);
    REQUIRE(header.slotLengthWithHeader() == 17);
    REQUIRE(header.classPointer() == 0xBE11EC1E);
}

TEST_CASE("testEncodeHeader2", "[objectHeader]") {
    BoringLang::Memory::SlotOrHeader mem[] {
            0x0000000000000000,
            0x123456789ABCDEF0
    };
    BoringLang::Memory::ObjectHeader header(mem);

    header.setArrayed(true);
    header.setArraySlotSize(BoringLang::Memory::BITS_32);
    header.setSpecialSection(BoringLang::Memory::FREE);
    header.setNull(true);
    header.setLength(126);
    header.setClassPointer(0xBE11EC1E);

    REQUIRE(mem[0].slot == 0xBE11EC1E007E002B);
    REQUIRE(mem[1].slot == 0x123456789ABCDEF0);
}

TEST_CASE("testDecodeHeader3", "[objectHeader]") {
    BoringLang::Memory::SlotOrHeader mem[] {
            0xA110A110FFFF0036,
            0x0000000000100000
    };
    BoringLang::Memory::ObjectHeader header(mem);

    REQUIRE(!header.arrayed());
    REQUIRE(header.arraySlotSize() == BoringLang::Memory::BITS_8);
    REQUIRE(header.specialSection() == BoringLang::Memory::BLOCKED);
    REQUIRE(header.null());
    REQUIRE(header.length() == 1048576);
    REQUIRE(header.lengthWithHeader() == 1048592);
    REQUIRE(header.slotLength() == 131072);
    REQUIRE(header.slotLengthWithHeader() == 131074);
    REQUIRE(header.classPointer() == 0xA110A110);
}

TEST_CASE("testEncodeHeader3", "[objectHeader]") {
    BoringLang::Memory::SlotOrHeader mem[] {
            0x0000000000000000,
            0x123456789ABCDEF0
    };
    BoringLang::Memory::ObjectHeader header(mem);

    header.setArrayed(false);
    header.setArraySlotSize(BoringLang::Memory::BITS_8);
    header.setSpecialSection(BoringLang::Memory::BLOCKED);
    header.setNull(true);
    header.setLength(1048576);
    header.setClassPointer(0xA110A110);

    REQUIRE(mem[0].slot == 0xA110A110FFFF0036);
    REQUIRE(mem[1].slot == 1048576);
}
