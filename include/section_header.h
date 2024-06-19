#pragma once
#include <unistd.h>

#define SHT_NULL 0x0
#define SHT_PROGBITS 0x1
#define SHT_SYMTAB 0x2
#define SHT_STRTAB 0x3
#define SHT_RELA 0x4
#define SHT_HASH 0x5
#define SHT_DYNAMIC 0x6
#define SHT_NOTE 0x7
#define SHT_NOBITS 0x8
#define SHT_REL 0x9
#define SHT_SHLIB 0x0A
#define SHT_DYNSYM 0x0B
#define SHT_INIT_ARRAY 0x0E
#define SHT_FINI_ARRAY 0x0F
#define SHT_PREINIT_ARRAY 0x10
#define SHT_GROUP 0x11
#define SHT_SYMTAB_SHNDX 0x12
#define SHT_NUM 0x13
#define SHT_LOOS 0x60000000

#define SHF_WRITE 0x1
#define SHF_ALLOC 0x2
#define SHF_EXECINSTR 0x4
#define SHF_MERGE 0x10
#define SHF_STRINGS 0x20
#define SHF_INFO_LINK 0x40
#define SHF_LINK_ORDER 0x80
#define SHF_OS_NONCONFORMING 0x100
#define SHF_GROU 0x200
#define SHF_TLS	Section 0x400
#define SHF_MASKOS 0x0FF00000	
#define SHF_MASKPROC 0xF0000000	
#define SHF_ORDERED 0x4000000	
#define SHF_EXCLUDE 0x8000000	

struct __attribute__((__packed__)) Section_Header
{ 
    __uint32_t sh_name;
    __uint32_t sh_type;
    __uint64_t sh_flags;
    __uint64_t sh_addr;
    __uint64_t sh_offset;
    __uint64_t sh_size;
    __uint32_t sh_link;
    __uint32_t sh_info;
    __uint64_t sh_addralign;
    __uint64_t sh_entsize;

} typedef Section_Header;

struct __attribute__((__packed__)) Section_Header_Readable
{ 
    __uint32_t name_offset;
    __uint32_t type;
    __uint64_t flags;
    __uint64_t virtual_address;
    __uint64_t offset_in_file;
    __uint64_t size_in_file;
    __uint32_t section_index;
    __uint32_t section_info;
    __uint64_t section_alignment;
    __uint64_t entry_size;

} typedef Section_Header_Readable;