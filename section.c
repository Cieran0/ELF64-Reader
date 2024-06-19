#include <section.h>
#include <string.h>

Section new_section(Section_Header header, char* name, FILE* f) {
    Section new_section;
    new_section.header = header;
    new_section.name = name;
    
    new_section.size = header.sh_size;
    if(new_section.size <= 0) {
        new_section.data = NULL;
        return new_section;
    }


    __uint8_t* data = (__uint8_t*)malloc(new_section.size);

    if(fseek(f, header.sh_offset, SEEK_SET)) {
        printf("FUCKY\n");
        exit(-1);
    }
    printf("%d\n", header.sh_offset);
    printf("%d\n", new_section.size);
    

    if(fread(data, new_section.size, 1, f) != 1) {
        printf("Fuck!\n");
        exit(-1);
    }

    new_section.data = data;

    return new_section;
}

char buff[3] = {0,0,0};

char* as_hex(__uint8_t byte) {

    __uint8_t high = byte >> 4;
    __uint8_t low = byte & 0x0F;

    high += (high >= 10)? 55 : 48;
    low += (low >= 10)? 55 : 48;
    buff[0] = high;
    buff[1] = low;
    return buff;
}

void print_section(Section section) {
    printf("Name: %s\n",section.name);
    printf("Data [%d]: \n~~~~~~~~~~~~~~\n", section.size);
    int is_code = !strcmp(section.name, ".text");
    int is_string_table = !strcmp(section.name, ".shstrtab");
    if(is_code) {
        printf("CODE!\n");
    }
    for (__uint64_t i = 0; i < section.size && !is_code; i++)
    {
        if(i % 8 == 0 && i > 0 && !is_string_table) {
            printf("\n");
        }
        __uint8_t byte = section.data[i];
        if(is_string_table) {
            if(byte == 0)
                printf(" 00 ");
            else
                printf("%c",byte);

        } else {
            printf("%s ", as_hex(byte));
        }
        
    }
    printf("\n~~~~~~~~~~~~~~\n");
}