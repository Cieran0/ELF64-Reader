#pragma once
#include <unistd.h>

struct __attribute__((__packed__)) ELF64_Header
{
    __uint32_t ei_mag0;
    __uint8_t ei_class;
    __uint8_t ei_data;
    __uint8_t ei_version;
    __uint8_t ei_osabi;
    __uint8_t ei_abiversion;
    __uint32_t ei_pad_0;
    __uint16_t ei_pad_1;
    __uint8_t ei_pad_2;
    __uint16_t e_type;
    __uint16_t e_machine;
    __uint32_t e_version;
    __uint64_t e_entry;
    __uint64_t e_phoff;
    __uint64_t e_shoff;
    __uint32_t e_flags;
    __uint16_t e_ehsize;
    __uint16_t e_phentsize;
    __uint16_t e_phnum;
    __uint16_t e_shentsize;
    __uint16_t e_shnum;
    __uint16_t e_shstrndx;
} typedef ELF64_Header;

struct __attribute__((__packed__)) ELF64_Header_Readable
{
    __uint8_t magic_number[4];
    __uint8_t format;
    __uint8_t endianness;
    __uint8_t version;
    __uint8_t target_abi;
    __uint8_t abi_version;
    __uint8_t ei_pad[7];
    __uint16_t file_type;
    __uint16_t target_instruction_set;
    __uint32_t elf_version;
    __uint64_t entry_point;
    __uint64_t program_header_offset;
    __uint64_t section_header_offset;
    __uint32_t flags;
    __uint16_t header_size;
    __uint16_t program_header_size;
    __uint16_t program_header_num;
    __uint16_t section_header_size;
    __uint16_t section_header_num;
    __uint16_t section_header_string_index;
} typedef ELF64_Header_Readable;