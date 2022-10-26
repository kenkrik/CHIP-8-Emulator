#include <stdio.h>
#include <stdint.h>

// This is a little learning file 

/*
int main(int argc, char *argv[]) {

    uint8_t memory[4000];
    int byte1 = 0xA2;
    int byte2 = 0xF0; 
    int opcode;

// fetch
    opcode = byte1 << 8 | byte2;

//decode
    int result;
    int decoded = opcode >> 12;

    if(decoded == 0xA) {
    //execute 
        printf("This is the value: %X.\n", decoded);
        result = opcode & 0x0FFF; 
    }
    
    printf("The index register now stores: 0x%X.\n", result);




    return 0;

}
*/


int main(int argc, char *argv[]) {

    #define STARTING_ADRESS 200
    uint8_t memory[4000];
    int byte1 = 0xA2;
    int byte2 = 0xF0; 
    int opcode;

// load stuff into memory
memory[STARTING_ADRESS] = byte1;
memory[STARTING_ADRESS + 1] = byte2;


uint8_t *pc = &memory[STARTING_ADRESS];

// fetch
    // make sure to write brackets around pc + 1
    opcode = *pc << 8 | *(pc + 1);
    printf("%X\n", opcode);
    pc += 2;
    
//decode
    int result;
    int decoded = opcode >> 12;

    if(decoded == 0xA) {
    //execute 
        printf("This is the value: %X.\n", decoded);
        result = opcode & 0x0FFF; 
    }
    
    printf("The index register now stores: 0x%X.\n", result);




    return 0;

}

