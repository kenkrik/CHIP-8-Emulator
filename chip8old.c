#include "chip8.h"



int loadRom(int argc, char *argv[]) {

// Reads rom path from the console
    char *romPath; 
    if(argc == 2) {

    // Allocates enough memory to save argv[1]
        romPath = malloc(strlen(argv[1]) + 1);
        strcpy(romPath, argv[1]);

    }
    else if(argc > 2) {
        printf("Too many arguments!\nPlease enter a path for your ROM file. \nExample: /home/user/ROMS/chip8/pong\n");
        return 0;
    }
    else {
        printf("Please enter a path for your ROM file. \nExample: /home/user/ROMS/chip8/pong\n");
        return 0;
    }


    FILE *rom;
    rom = fopen(romPath, "rb");
    if(NULL == rom) {
        printf("Error loading the ROM file!\nCheck if you entered the proper path.\n");
    }
    
// Goes to the end of the file and allocates buffer size
    fseek(rom, 0, SEEK_END);
    long fileSize = ftell(rom);
    char *buffer = malloc(fileSize + 1);
    
// Goes to the beginning and fills the buffer 
    fseek(rom, 0, SEEK_SET);
    fread(buffer, fileSize, 1, rom); 
    fclose(rom);

// Loads the rom into memory and frees buffer
    for(long i = 0; i < fileSize; ++i) {
        memory[START_ADDRESS + i] = buffer[i];
    }
    free(buffer);
}


void loadFontset() {
    for(int i = 0; i < FONTSET_SIZE; ++i) {
        memory[FONTSET_START_ADDRESS + i] = fontset[i];

    }
}


int main(int argc, char *argv[]) {


    loadRom(argc, argv);
    
    loadFontset();




     








    return 0;
}



// What to do now: 
    // fetch the opcode from memory
    // decode op code
    // execute opcode


// Just found this amazing guide on fetching, decoding and executiong of opcodes:
    // it also shows how to initialize the system etc.
    // https://multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/



