#include "chip8.h"


// What to do now: 
    // fetch the opcode from memory
    // decode op code
    // execute opcode


// Just found this amazing guide on fetching, decoding and executiong of opcodes:
    // it also shows how to initialize the system etc.
    // https://multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/

int initialize() {
    pc = START_ADDRESS;
    opcode = 0;
    IRegister = 0;
    sp = 0;

    // cl display
    // cl stack
    // cl Vx 
    // cl memory

    // reset timers 
}



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

// Declarations
const int windowXSize = 600;
const int windowYSize = 400;
int frame = 0;
int deltaFrame = 0;
const int FPS = 60;
// Required lenght of one frame in order to archieve stabel FSP count
int frameLenght = 1000 / FPS;
int currentFrame = 0;


int main(int argc, char *argv[]) {


    // SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowXSize, windowYSize, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);





    initialize();
    
    loadFontset();

    loadRom(argc, argv);


uint8_t N, NN, NNN, Vx ;
N = NN = NN = Vx = 0;


// one cycle
int run = 1;
while(run == 1)
{
    // increment program counter
    pc += 2;


    // Constant FPS check
    deltaFrame = SDL_GetTicks() - frame;

    if(deltaFrame < frameLenght)
    {
        SDL_Delay(frameLenght - deltaFrame);
    }   
    
    frame = SDL_GetTicks();
    currentFrame++;

    if((currentFrame % 60) == 0)
    {
        
        printf("Current frame is: %d\n", currentFrame);

    }


    SDL_Event event;
    
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            run = 0;
            break;
        
        default:
            break;
        }




    }
    
    
    // fetch 
        opcode = memory[pc] << 8 | memory[pc + 1];

    // decode
        // Implement to get IBM logo working
            // 00E0 
            // 1NNN *
            // 6XNN *
            // 7XNN *
            // ANNN *
            // DXYN

        // 00
        // 1 - 7
        // 8XY*
        // 9
        // A - C
        
        // EX9E
        // EXA1
        
        // FX



    // definitions
        // N: 4-bit constant
        // NN: 8-bit constant
        // NNN: address 
        // Vx: 4-bit register identifier
        // Vy: 4-bit register identifier

        printf("Current opcode: %X\n", opcode);
        
        switch(opcode & 0xF000) {
             
            // check for example for E0(fe. first opcode in 15PUZZLE)
            case 0x0000:
                switch(opcode & 0x000F) {
                   case 0x0000:
                        // 0x00E0
                        // clear screen
                        break;
                        
                    case 0x000E:
                        printf("00EE");
                        break;
                    
                    default: 
                        printf("the 0x0000 opcode aint working right\n");
                        break; 
                }
                break;
            
            case 0x1000:
                // 0x1NNN
                // jumps to address NNN
                NNN = opcode & 0x0FFF;
                pc = NNN;

                break;
            
            case 0x6000:
                // 0x6XNN
                // Vx = NN
                Vx = (opcode & 0x0F00u);
                NN = opcode & 0x00FFu;
                registers[Vx] = NN;
                
                break;
            
            case 0x7000:
                // 0x7XNN
                // Vx += NN 
                // carry flag not changed
                NN = opcode & 0x00FF;
                registers[Vx] += NN;

                break;
            
            case 0xA000:
                // 0xANNN
                // IRegister = NNN

                NNN = opcode & 0x0FFF;
                IRegister = NNN; 
                
                break;

            case 0xD000:
                // 0xDXYN
                // draws a sprite at (Vx, Vy, N)
                break;

            default:
                printf("%X\n", opcode & 0xF000);
                printf("Oopsie, unknown opcode(%X)\n", opcode);


        }
    }     





    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}


