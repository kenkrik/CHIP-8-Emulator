#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h> // malloc etc
#include <time.h> 	// required for random number generation


#include <SDL2/SDL.h>


#define FONTSET_START_ADDRESS 0x50
#define START_ADDRESS 0x200
#define TOTAL_MEMORY 4096   //bytes
#define NUM_V_REGISTERS 16  //bits
#define STACK_SIZE 16       //levels
#define NUM_KEYS 16
#define FONTSET_SIZE 80
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

// Debug features, 0 off, 1 on
int debug = 0;
int runNextCycle = 1;


const int FPS = 60 * 5;

uint16_t address, Vx, Vy, value = 0;







uint8_t memory[TOTAL_MEMORY];
// registers
uint8_t registers[NUM_V_REGISTERS];
// index register
uint16_t IRegister;
// program counter               
uint16_t pc;                
uint16_t stack[STACK_SIZE]; 
// stack pointer
uint8_t sp;
// delay timer
uint8_t delayT; 
// sound timer                   
uint8_t soundT;
uint8_t keypad[NUM_KEYS];
uint32_t screen[SCREEN_WIDTH * SCREEN_HEIGHT]; //using uint32_t instead of uint16_t for better sdl compatibility



uint32_t screenPitch = (sizeof(screen[0]) * SCREEN_WIDTH);
uint16_t opcode;
char *buffer = NULL;
uint8_t draw = 0;

uint8_t fontset[FONTSET_SIZE] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

int run = 1;

