#pragma once
#include <section_header.h>
#include <stdlib.h>
#include <stdio.h>

struct Section
{
    Section_Header header;
    char* name;
    __uint64_t size;
    __uint8_t* data;
} typedef Section;

Section new_section(Section_Header header, char* name, FILE* f);

void print_section(Section section);
