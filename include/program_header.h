#pragma once
#include <unistd.h>

#define PT_NULL 0x00000000
#define PT_LOAD 0x00000001
#define PT_DYNAMIC 0x00000002
#define PT_INTERP 0x00000003
#define PT_NOTE 0x00000004
#define PT_SHLIB 0x00000005
#define PT_PHDR 0x00000006
#define PT_TLS 0x00000007
#define PT_LOOS 0x60000000
#define PT_HIOS 0x6FFFFFFF
#define PT_LOPROC 0x70000000
#define PT_HIPROC 0x7FFFFFFF


#define PF_X 0x1
#define PF_W 0x2
#define PF_R 0x4

struct __attribute__((__packed__)) Program_Header
{ 
    __uint32_t p_type;
    __uint32_t p_flags;
    __uint64_t p_offset;
    __uint64_t p_vaddr;
    __uint64_t p_paddr;
    __uint64_t p_filesz;
    __uint64_t p_memsz;
    __uint64_t p_align;

} typedef Program_Header;

struct __attribute__((__packed__)) Program_Header_Readable
{ 
    __uint32_t type;
    __uint32_t flags;
    __uint64_t offset;
    __uint64_t virtual_address;
    __uint64_t physical_address;
    __uint64_t file_size;
    __uint64_t memory_size;
    __uint64_t alignment;

} typedef Program_Header_Readable;