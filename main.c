#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include <fcntl.h>
#include "elf64_header.h"
#include "program_header.h"
#include "section_header.h"
#include "section.h"
#include <assert.h>

char* read_null_terminated_string(FILE *file, long position) {
    // Move the file pointer to the desired position
    if (fseek(file, position, SEEK_SET) != 0) {
        perror("fseek failed");
        return NULL;
    }

    // Allocate initial memory for the string buffer
    size_t buffer_size = 128;
    size_t length = 0;
    char *buffer = (char *)malloc(buffer_size);
    if (!buffer) {
        perror("malloc failed");
        return NULL;
    }

    // Read the string character by character
    char ch;
    while (fread(&ch, 1, 1, file) == 1) {
        if (ch == '\0') {
            break;
        }
        buffer[length++] = ch;

        // Reallocate memory if buffer is full
        if (length >= buffer_size) {
            buffer_size *= 2;
            char *new_buffer = (char *)realloc(buffer, buffer_size);
            if (!new_buffer) {
                perror("realloc failed");
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
        }
    }

    // Null-terminate the string
    buffer[length] = '\0';
    return buffer;
}

void print_section_header(Section_Header_Readable header, char* name) {
    printf("name : %s\n", name);
    printf("name offset: %d\n", header.name_offset);
    printf("type: %d\n", header.type);
    printf("flags: %d\n", header.flags);
    printf("virtual_address: %d\n", header.virtual_address);
    printf("offset_in_file: %d\n", header.offset_in_file);
    printf("size_in_file: %d\n", header.size_in_file);
    printf("section_index: %d\n", header.section_index);
    printf("section_info: %d\n", header.section_info);
    printf("section_alignment: %d\n", header.section_alignment);
    printf("entry_size: %d\n", header.entry_size);
}

void print_program_header(Program_Header_Readable header) {
    printf("type: %d\n", header.type);
    printf("flags: %d\n", header.flags);
    printf("offset: %d\n", header.offset);
    printf("virtual_address: %d\n", header.virtual_address);
    printf("physical_address: %d\n", header.physical_address);
    printf("file_size: %d\n", header.file_size);
    printf("memory_size: %d\n", header.memory_size);
    printf("alignment: %d\n", header.alignment);
}

void print_header(ELF64_Header header) {
    printf("ei_mag0: %p\n", header.ei_mag0); 
    printf("ei_class: %p\n", header.ei_class); 
    printf("ei_data: %p\n", header.ei_data); 
    printf("ei_version: %p\n", header.ei_version); 
    printf("ei_osabi: %p\n", header.ei_osabi); 
    printf("ei_abiversion: %p\n", header.ei_abiversion); 
    printf("ei_pad_0: %p\n", header.ei_pad_0); 
    printf("ei_pad_1: %p\n", header.ei_pad_1); 
    printf("ei_pad_2: %p\n", header.ei_pad_2); 
    printf("e_type: %p\n", header.e_type); 
    printf("e_machine: %p\n", header.e_machine); 
    printf("e_version: %p\n", header.e_version); 
    printf("e_entry: %p\n", header.e_entry); 
    //printf("e_entry_rev: %p\n", reverse(header.e_entry)); 
    printf("e_phoff: %p\n", header.e_phoff); 
    printf("e_shoff: %p\n", header.e_shoff); 
    printf("e_flags: %p\n", header.e_flags); 
    printf("e_ehsize: %p\n", header.e_ehsize); 
    printf("e_phentsize: %p\n", header.e_phentsize); 
    printf("e_phnum: %p\n", header.e_phnum); 
    printf("e_shentsize: %p\n", header.e_shentsize); 
    printf("e_shnum: %p\n", header.e_shnum); 
    printf("e_shstrndx: %p\n", header.e_shstrndx); 
}


int main() {
    
    assert(sizeof(ELF64_Header) == sizeof(ELF64_Header_Readable));
    assert(sizeof(Program_Header) == sizeof(Program_Header_Readable));
    assert(sizeof(Section_Header) == sizeof(Section_Header_Readable));
    

    FILE* f = fopen("crash", "r");
    ELF64_Header header;

    fread(&header,sizeof(ELF64_Header),1,f);
    fseek(f, 0, SEEK_SET);

    //printf("Hello, World! %p\n",sizeof(Section_Header));

    fseek(f, header.e_phoff, SEEK_SET);

    Program_Header* pheads = malloc(header.e_phentsize * header.e_phnum);

    fread(pheads, header.e_phentsize, header.e_phnum, f);

    fseek(f,0,SEEK_SET);
    fseek(f,header.e_shoff,SEEK_SET);

    Section_Header* sheads = malloc(header.e_shentsize * header.e_shnum);

    fread(sheads, header.e_shentsize, header.e_shnum, f);

    char** names = malloc(sizeof(char*)*header.e_shnum);
    for (size_t i = 0; i < header.e_shnum; i++)
    {
        int index = (sheads[header.e_shstrndx].sh_offset + sheads[i].sh_name);
        names[i] = read_null_terminated_string(f,index);
    }

    printf("Program Headers\n---------------\n");
    for (__uint16_t i = 0; i < header.e_phnum; i++)
    {
        print_program_header(((Program_Header_Readable*)(pheads))[i]);
        printf("---------------\n");
    }

    printf("Section Headers\n---------------\n");
    Section* sections = (Section*)malloc(sizeof(Section) * header.e_shnum); 
    for (__uint16_t i = 0; i < header.e_shnum; i++)
    {
        print_section_header(((Section_Header_Readable*)(sheads))[i], names[i]);
        printf("---------------\n");
        sections[i] = new_section(sheads[i], names[i], f);
    }

    printf("Sections\n---------------\n");
    for (__uint16_t i = 0; i < header.e_shnum; i++)
    {
        print_section(sections[i]);
        printf("---------------\n");
    }


    return 0;
}