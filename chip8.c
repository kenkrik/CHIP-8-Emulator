#include "chip8.h"


int initialize() {
    pc = START_ADDRESS;
    opcode = 0;
    IRegister = 0;
    sp = 0;
    srand(time(NULL));

    // cl display
    // cl stack
    // cl Vx
    // cl memory

    // reset timers
}

int loadRom(int argc, char *argv[]) {
    run = 1;

    // Reads rom path from the console
    char *romPath;
    if (argc == 2) {
        // Allocates enough memory to save argv[1]
        romPath = malloc(strlen(argv[1]) + 1);
        strcpy(romPath, argv[1]);

    } else if (argc > 2) {
        printf("Too many arguments!\nPlease enter a proper path for your ROM file. \nExample: /home/user/ROMS/chip8/pong\n");
        run = 0;
        return 0;
    } else {
        printf("Please enter a path for your ROM file. \nExample: /home/user/ROMS/chip8/pong\n");
        run = 0;
        return 0;
    }

    FILE *rom = NULL;
    rom = fopen(romPath, "rb");
    if (NULL == rom) {
        printf("Error loading the ROM file!\nCheck if you entered the proper path.\n");
    }

    // Goes to the end of the file and allocates buffer size
    fseek(rom, 0, SEEK_END);
    long fileSize = ftell(rom);
    buffer = malloc(fileSize + 1);

    // Goes to the beginning and fills the buffer
    fseek(rom, 0, SEEK_SET);
    fread(buffer, fileSize, 1, rom);
    fclose(rom);

    // Loads the rom into memory and frees buffer
    for (long i = 0; i < fileSize; ++i) {
        memory[START_ADDRESS + i] = buffer[i];
    }
    free(buffer);
}



void loadFontset() {
    for (int i = 0; i < FONTSET_SIZE; ++i) {
        memory[FONTSET_START_ADDRESS + i] = fontset[i];
    }
}

// Declarations
const int windowXSize = 640;
const int windowYSize = 320;
int frame = 0;
int deltaFrame = 0;
const int FPS = 60 * 5;
// Required lenght of one frame in order to archieve stabel FSP count
int frameLenght = 1000 / FPS;
int currentFrame = 0;

int main(int argc, char *argv[]) {
    // SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowXSize, windowYSize, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    initialize();
    loadFontset();
    loadRom(argc, argv);


    if (run == 0) {
        return 0;
    }


    // one cycle
    while (run == 1) {
        
        if (debug == 1) {
            runNextCycle = 0;
        }


        // increment program counter
        pc += 2;

        // delay timer and sound timer are kinda random now and not fully implemented
        if (delayT > 0) {
            delayT -= 1;
        }

        if (soundT > 0) {
            soundT -= 1;
            // beeeep 
        }

        opcode = memory[pc] << 8 | memory[pc + 1];

        // Constant FPS check
        deltaFrame = SDL_GetTicks() - frame;

        if (deltaFrame < frameLenght) {
            SDL_Delay(frameLenght - deltaFrame);
        }

        if ((currentFrame % 60) == 0) {
            printf("Current frame is: %d\n", currentFrame);
        }

        currentFrame++;
        frame = SDL_GetTicks();


        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    run = 0;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_ESCAPE:
                            run = 0;
                            break;
                        case SDL_SCANCODE_RETURN:
                            if (debug == 1) {
                                debug = 0;
                            }
                            else {
                                debug = 1;
                            }
                            break;
                        case SDL_SCANCODE_1:
                            //runNextCycle = 1;
                            keypad[1] = 1;
                            break;
                        case SDL_SCANCODE_2:
                            //runNextCycle = 1;
                            keypad[2] = 1;
                            break;
                        case SDL_SCANCODE_3:
                            //runNextCycle = 1;
                            keypad[3] = 1;
                            break;
                        case SDL_SCANCODE_4:
                            //runNextCycle = 1;
                            keypad[0xC] = 1;
                            break;
                        case SDL_SCANCODE_Q:
                            //runNextCycle = 1;
                            keypad[4] = 1;
                            break;
                        case SDL_SCANCODE_W:
                            //runNextCycle = 1;
                            keypad[5] = 1;
                            break;
                        case SDL_SCANCODE_E:
                            //runNextCycle = 1;
                            keypad[6] = 1;
                            break;
                        case SDL_SCANCODE_R:
                            //runNextCycle = 1;
                            keypad[0xD] = 1;
                            break;
                        case SDL_SCANCODE_A:
                            //runNextCycle = 1;
                            keypad[7] = 1;
                            break;
                        case SDL_SCANCODE_S:
                            //runNextCycle = 1;
                            keypad[8] = 1;
                            break;
                        case SDL_SCANCODE_D:
                            //runNextCycle = 1;
                            keypad[9] = 1;
                            break;
                        case SDL_SCANCODE_F:
                            //runNextCycle = 1;
                            keypad[0xE] = 1;
                            break;
                        case SDL_SCANCODE_Z:
                            //runNextCycle = 1;
                            keypad[0xA] = 1;
                            break;
                        case SDL_SCANCODE_X:
                            //runNextCycle = 1;
                            keypad[0] = 1;
                            break;
                        case SDL_SCANCODE_C:
                            //runNextCycle = 1;
                            keypad[0xB] = 1;
                            break;
                        case SDL_SCANCODE_V:
                            //runNextCycle = 1;
                            keypad[0xF] = 1;
                            break;

                        default:
                            break;
                    }

                case SDL_KEYUP:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_1:
                            //runNextCycle = 1;
                            keypad[1] = 0;
                            break;
                        case SDL_SCANCODE_2:
                            //runNextCycle = 1;
                            keypad[2] = 0;
                            break;
                        case SDL_SCANCODE_3:
                            //runNextCycle = 1;
                            keypad[3] = 0;
                            break;
                        case SDL_SCANCODE_4:
                            //runNextCycle = 1;
                            keypad[0xC] = 0;
                            break;
                        case SDL_SCANCODE_Q:
                            //runNextCycle = 1;
                            keypad[4] = 0;
                            break;
                        case SDL_SCANCODE_W:
                            //runNextCycle = 1;
                            keypad[5] = 0;
                            break;
                        case SDL_SCANCODE_E:
                            //runNextCycle = 1;
                            keypad[6] = 0;
                            break;
                        case SDL_SCANCODE_R:
                            //runNextCycle = 1;
                            keypad[0xD] = 0;
                            break;
                        case SDL_SCANCODE_A:
                            //runNextCycle = 1;
                            keypad[7] = 0;
                            break;
                        case SDL_SCANCODE_S:
                            //runNextCycle = 1;
                            keypad[8] = 0;
                            break;
                        case SDL_SCANCODE_D:
                            //runNextCycle = 1;
                            keypad[9] = 0;
                            break;
                        case SDL_SCANCODE_F:
                            //runNextCycle = 1;
                            keypad[0xE] = 0;
                            break;
                        case SDL_SCANCODE_Z:
                            //runNextCycle = 1;
                            keypad[0xA] = 0;
                            break;
                        case SDL_SCANCODE_X:
                            //runNextCycle = 1;
                            keypad[0] = 0;
                            break;
                        case SDL_SCANCODE_C:
                            //runNextCycle = 1;
                            keypad[0xB] = 0;
                            break;
                        case SDL_SCANCODE_V:
                            //runNextCycle = 1;
                            keypad[0xF] = 0;
                            break;

                        default:
                            break;
                    }




                default:
                    break;
            }
        }

        // fetch

        // decode
        // Implement to get IBM logo working
        // 00E0 *
        // 1NNN *
        // 6XNN *
        // 7XNN *
        // ANNN *
        // DXYN *

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

        switch (opcode & 0xF000) {
            // check for example for E0(fe. first opcode in 15PUZZLE)
            case 0x0000:
                switch (opcode & 0x00FF) {
                    case 0x00E0:
                        // I am not sure that the whole 0000 opcode branch is implemented properly
                        // 0x00E0
                        // clear screen
                        draw = 1;
                        //memset(screen, 0, sizeof(screen));
                        printf("clearing the screen\n");
                        break;

                    case 0x00EE:
                        sp -= 1;
                        pc = stack[sp];
                        break;
                        // https://multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/
                    default:
                        printf("Oopsie, unknown opcode(%X)\n\n", opcode);
                        break;
                }  // case 0x0000
                break;

            case 0x1000:
                // 0x1NNN
                // jumps to address NNN
                address = opcode & 0x0FFF;
                pc = address;
                // jumps shouldnt increase pc?
                pc -= 2;

                break;

            case 0x2000:
                stack[sp] = pc;
                printf("stack[sp]: %x\n", stack[sp]);
                sp += 1;
                address = opcode & 0x0FFF;
                pc = address;
                break;

            case 0x3000:
                Vx = (opcode & 0x0F00) >> 8;
                int value = opcode & 0x00FF;
                if (registers[Vx] == value) {
                    pc += 2;
                }
                break;

            case 0x4000:
                Vx = (opcode & 0x0F00) >> 8;
                if (registers[Vx] != (opcode & 0x00FF)) {
                    pc += 2;
                }
                break;

            case 0x6000:
                // 0x6XNN
                // Vx = NN
                Vx = (opcode & 0x0F00) >> 8;
                address = opcode & 0x00FF;
                registers[Vx] = address;

                break;

            case 0x7000:
                // 0x7XNN
                // Vx += NN
                // carry flag not changed
                Vx = (opcode & 0x0F00) >> 8;
                address = opcode & 0x00FF;
                registers[Vx] += address;

                break;

            case 0x8000:
                switch (opcode & 0x000F) {
                    case 0x0000:
                        Vx = (opcode & 0x0F00) >> 8;
                        Vy = (opcode & 0x00F0) >> 4;
                        
                        registers[Vx] = registers[Vy];
                
                        break;
                    case 0x0002:
                        Vx = (opcode & 0x0F00) >> 8;
                        Vy = (opcode & 0x00F0) >> 4;

                        registers[Vx] = registers[Vx] & registers[Vy];

                        break;

                    case 0x0004:
                        Vx = (opcode & 0x0F00) >> 8;
                        Vy = (opcode & 0x00F0) >> 4;

                        int sum = registers[Vx] + registers[Vy];

                        if (sum > 255) {
                            registers[0xF] = 1;
                        }
                        else {
                            registers[0xF] = 0;
                        }
                        registers[Vx] = sum & 0xFF;

                        break;
                    
                    case 0x0005:
                        Vx = (opcode & 0x0F00) >> 8;
                        Vy = (opcode & 0x00F0) >> 4;

                        if (registers[Vx] > registers[Vy]) {
                            registers[0xF] = 1;
                        } 
                        else {
                            registers[0xF] = 0;
                        }

                        registers[Vx] -= registers[Vy];

                        break;

                    
                    case 0x0008:
                        Vx = (opcode & 0x0F00) >> 8;
                        
                        // not sure if this is the correct way to write this
                        registers[0xF] = registers[Vx] >> 7;
                        printf("The rg Vx shifted by 7 to the right: %x\n",registers[Vx] >> 7);
                        printf("This opcode might not be working properly\n");
                        registers[Vx] = registers[Vx] << 1;

                        break;
            
                    default:
                        printf("Oopsie, unknown opcode(%X)\n\n", opcode);
                        break;
                    
                }
                break;

            case 0xA000:
                // 0xANNN
                // IRegister = NNN
                address = opcode & 0x0FFF;
                printf("address: %x\n", address);
                IRegister = address;

                break;
            case 0xC000:
                Vx = (opcode & 0x0F00) >> 8;
                int randomNumber = rand() % 255;
                registers[Vx] = randomNumber & (opcode & 0x00FF);
                break;

            case 0xD000:
                // 0xDXYN
                // draws a sprite at (Vx, Vy, N)
                draw = 1;
                //uint8_t Vx = (opcode & 0x0F00) >> 8;
                //uint8_t Vy = (opcode & 0x00F0) >> 4;
                
                Vx = (opcode & 0x0F00) >> 8;
                Vy = (opcode & 0x00F0) >> 4;
                
                // sprite height - N
                uint8_t height = (opcode & 0x000F);

                // % to make sprites overlap the screen
                // but the actual sprite shouldnt wrap but it should be clipped when drawn near the edge
                uint8_t xPos = registers[Vx] % SCREEN_WIDTH;
                uint8_t yPos = registers[Vy] % SCREEN_HEIGHT;

                registers[0xF] = 0;

                for (int row = 0; row < height; row++) {
                    uint8_t spriteData = memory[IRegister + row];

                    for (int column = 0; column < 8; column++) {
                        // 0x80 = 10000000
                        uint8_t spritePixel = spriteData & (0x80 >> column);
                        uint32_t *screenPixel = &screen[(xPos + column) + ((yPos + row) * SCREEN_WIDTH)];
                        if (spritePixel) {
                            // screen pixel is on, collision
                            if (*screenPixel == 0xFFFFFFFF) {
                                registers[0xF] = 1;
                            }
                            // XOR screen pixel (0xFFFFFFFF/0x00000000)-(on/off)
                            *screenPixel ^= 0xFFFFFFFF;
                        }
                    }
                }

                break;

            case 0xE000:
                switch (opcode & 0x00FF) {
                    case 0x009E:
                        Vx = (opcode & 0x0F00) >> 8;
                        
                        if (keypad[registers[Vx]]) {
                            pc += 2;
                        }

                        break;
                    
                    case 0x00A1:
                        Vx = (opcode & 0x0F00) >> 8;
                        
                        if (!keypad[registers[Vx]]) {
                            pc += 2;
                        }

                        break;
                    
                    default:
                        printf("Oopsie, unknown opcode(%X)\n\n", opcode);
                        break;
                }
                break;


            case 0xF000:
                switch (opcode & 0x00FF) {

                    case 0x000A: 
                        Vx = (opcode & 0x0F00) >> 8;
                        //runNextCycle = 0; 
                        //while(debug == 1) {
                            while (SDL_PollEvent(&event)) {
                                switch (event.type) {
                                    case SDL_QUIT:
                                        //runNextCycle = 1;
                                        run = 0;
                                        break;
                                    case SDL_KEYDOWN:
                                        switch (event.key.keysym.scancode) {
                                            case SDL_SCANCODE_ESCAPE:
                                                //runNextCycle = 1;
                                                run = 0;
                                                break;
                                            case SDL_SCANCODE_1:
                                                //runNextCycle = 1;
                                                registers[Vx] = 1;
                                                break;
                                            case SDL_SCANCODE_2:
                                                //runNextCycle = 1;
                                                registers[Vx] = 2;
                                                break;
                                            case SDL_SCANCODE_3:
                                                //runNextCycle = 1;
                                                registers[Vx] = 3;
                                                break;
                                            case SDL_SCANCODE_4:
                                                //runNextCycle = 1;
                                                registers[Vx] = 'C';
                                                break;
                                            case SDL_SCANCODE_Q:
                                                //runNextCycle = 1;
                                                registers[Vx] = 4;
                                                break;
                                            case SDL_SCANCODE_W:
                                                //runNextCycle = 1;
                                                registers[Vx] = 5;
                                                break;
                                            case SDL_SCANCODE_E:
                                                //runNextCycle = 1;
                                                registers[Vx] = 6;
                                                break;
                                            case SDL_SCANCODE_R:
                                                //runNextCycle = 1;
                                                registers[Vx] = 'D';
                                                break;
                                            case SDL_SCANCODE_A:
                                                //runNextCycle = 1;
                                                registers[Vx] = 7;
                                                break;
                                            case SDL_SCANCODE_S:
                                                //runNextCycle = 1;
                                                registers[Vx] = 8;
                                                break;
                                            case SDL_SCANCODE_D:
                                                //runNextCycle = 1;
                                                registers[Vx] = 9;
                                                break;
                                            case SDL_SCANCODE_F:
                                                //runNextCycle = 1;
                                                registers[Vx] = 'E';
                                                break;
                                            case SDL_SCANCODE_Z:
                                                //runNextCycle = 1;
                                                registers[Vx] = 'A';
                                                break;
                                            case SDL_SCANCODE_X:
                                                //runNextCycle = 1;
                                                registers[Vx] = 0;
                                                break;
                                            case SDL_SCANCODE_C:
                                                //runNextCycle = 1;
                                                registers[Vx] = 'B';
                                                break;
                                            case SDL_SCANCODE_V:
                                                //runNextCycle = 1;
                                                registers[Vx] = 'F';
                                                break;
                                            
                                            default:
                                                pc -= 2;
                                                break;
                                        }

                                    default:
                                        pc -= 2;
                                        break;
                                }

                            }
                            delayT -= 1;
                            soundT -= 1;
                            // !!!!!!!!!!!! increase the delay and sound timer !!!!!!!!!
                            // dont increase pc
                        
                        //}  
                        break;

                    case 0x0033:
                        Vx = (opcode & 0x0F00) >> 8;
                        int value = registers[Vx];
                        printf("value in Vx%x: %d\n",Vx, registers[Vx]);
                        // ones
                        memory[IRegister + 2] = value % 10;
                        printf("value in memory at address I + 2 (ones): %d\n", memory[IRegister + 2]) ;
                        value /= 10;
                        // tens
                        memory[IRegister + 1] = value % 10;
                        printf("value in memory at address I + 1 (tens): %d\n", memory[IRegister + 1]) ;
                        value /= 10;
                        // hundreds
                        memory[IRegister] = value % 10;
                        printf("value in memory at address I + 0 (hundreds): %d\n", memory[IRegister]) ;

                        //printf("IReg %x IReg + 1 %x IReg + 2 %x\n", memory[IRegister], memory[IRegister + 1], memory[IRegister + 2]) ;
                        break;

                    case 0x0065:
                        Vx = (opcode & 0x0F00) >> 8;
                        printf("Fx65 vx is: %x\n", Vx);
                        for (int i = 0; i <= Vx; i++) {
                            registers[i] = memory[IRegister + i];
                            printf ("memory[ireg]: %d\n", registers[i]);
                        }
                        printf("Fx65 vx after loop is: %x\n", Vx);
                        break;

                    case 0x0029:
                        Vx = (opcode & 0x0F00) >> 8;
                        // multiplid by 5 because each charecter has the size of 5 bytes
                        IRegister = FONTSET_START_ADDRESS + (5 * registers[Vx]);
                        break;
                    case 0x0015:
                        Vx = (opcode & 0x0F00) >> 8;
                        delayT = registers[Vx];
                        break;

                    case 0x0018:
                        Vx = (opcode & 0x0F00) >> 8;
                        soundT = registers[Vx];
                        break;
                    case 0x0007:
                        Vx = (opcode & 0x0F00) >> 8;
                        registers[Vx] = delayT;
                        break;
                    case 0x001E:
                        Vx = (opcode & 0x0F00) >> 8;
                        IRegister += registers[Vx];
                        break;


                    default:
                        printf("Oopsie, unknown opcode(%X)\n\n", opcode);
                        break;
                }
                break;

            default:
                printf("\nUnknown group: %X\n", (opcode & 0xF000) >> 12);
                printf("Oopsie, unknown opcode(%X)\n\n", opcode);
                break;

        }  // switch
        
            printf("vx test: %x\n", Vx);
        //draw = 1;
        //if (draw) {
            SDL_UpdateTexture(texture, NULL, screen, screenPitch);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
        //    draw = 0;
        //}

        //printf("Currently pressed keys: %d", *numkeys);


        while(runNextCycle != 1) {
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        runNextCycle = 1;
                        run = 0;
                        break;
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.scancode) {
                            case SDL_SCANCODE_ESCAPE:
                                runNextCycle = 1;
                                run = 0;
                                break;
                            case SDL_SCANCODE_N:
                                runNextCycle = 1;
                                break;
                            case SDL_SCANCODE_RETURN:
                                if (debug == 1) {
                                    debug = 0;
                                }
                                else {
                                    debug = 1;
                                }
                                runNextCycle = 1;
                                break;
                            case SDL_SCANCODE_P:
                                printf("\nThe index register is: %x\n", IRegister);
                                printf("The Vx register V%x is: %x\n",Vx, registers[Vx]);
                                printf("The stack pointer is: %x\n", sp);
                                printf("The program counter is: %x\n", pc);
                                printf("The delay timer is: %x\n", delayT);
                                printf("The sound timer is: %x\n\n", soundT);

                                printf("The V0 register is: %x\n",registers[0x0]);
                                printf("The V1 register is: %x\n",registers[0x1]);
                                printf("The V2 register is: %x\n",registers[0x2]);
                                printf("The V3 register is: %x\n",registers[0x3]);
                                printf("The V4 register is: %x\n",registers[0x4]);
                                printf("The V5 register is: %x\n",registers[0x5]);
                                printf("The V6 register is: %x\n",registers[0x6]);
                                printf("The V7 register is: %x\n",registers[0x7]);
                                printf("The V8 register is: %x\n",registers[0x8]);
                                printf("The V9 register is: %x\n",registers[0x9]);
                                printf("The VA register is: %x\n",registers[0xA]);
                                printf("The VB register is: %x\n",registers[0xB]);
                                printf("The VC register is: %x\n",registers[0xC]);
                                printf("The VD register is: %x\n",registers[0xD]);
                                printf("The VE register is: %x\n",registers[0xE]);
                                printf("The VF register is: %x\n",registers[0xF]);
                                
                                printf("\n");


                                break;
                            default:
                                break;
                        }

                    default:
                        break;
                }

            }  

            SDL_UpdateTexture(texture, NULL, screen, screenPitch);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
        }


    }  // while

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
} // main
