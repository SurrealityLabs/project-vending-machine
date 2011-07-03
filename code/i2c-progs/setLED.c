#include "vend_i2c.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char colourArrayA[] = {0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E};
unsigned char colourArrayB[] = {0x00, 0x04, 0x02, 0x06, 0x01, 0x05, 0x03, 0x07};

int main(int argc, char **argv) {
    int i2c_file;

    // Open a connection to the I2C userspace control file.
    if ((i2c_file = open(I2C_FILE_NAME, O_RDWR)) < 0) {
        perror("Unable to open i2c control file");
        exit(-1);
    }
    
    if(argc == 4) {
        int addr = strtol(argv[1], NULL, 0);
        int ledNum = strtol(argv[2], NULL, 0);
        int ledColour = strtol(argv[3], NULL, 0);
        
        if((addr >= 0) && (addr < 8)) {
            addr += MCP23017_BASE_ADDR;
            addr *= 2;
            
            if((ledNum >= 0) && (ledNum < 4)) {
                unsigned char ledOutColour;
                unsigned char ledCurrent;
                
                if((ledColour >= 0) && (ledColour < 8)) {
                    if(ledNum == 0) {
                        ledOutColour = colourArrayA[ledColour];
                        if(get_i2c_register(i2c_file, addr, MCP23017_REG_OLATA, &ledCurrent)) {
                            perror("Unable to get register A");
                            close(i2c_file);
                            exit(-1);                        
                        }
                        
                        ledCurrent &= 0xF0;
                        ledCurrent |= ledOutColour;
                        
                        if(set_i2c_register(i2c_file, addr, MCP23017_REG_OLATA, ledCurrent)) {
                            perror("Unable to set register A");
                            close(i2c_file);
                            exit(-1);
                        }
                        
                        close(i2c_file);
                        return 0;
                    } else if(ledNum == 1) {
                        ledOutColour = colourArrayA[ledColour];
                        if(get_i2c_register(i2c_file, addr, MCP23017_REG_OLATA, &ledCurrent)) {
                            perror("Unable to get register A");
                            close(i2c_file);
                            exit(-1);                        
                        }
                        
                        ledCurrent &= 0x0F;
                        ledOutColour <<= 4;
                        ledCurrent |= ledOutColour;
                        
                        if(set_i2c_register(i2c_file, addr, MCP23017_REG_OLATA, ledCurrent)) {
                            perror("Unable to set register A");
                            close(i2c_file);
                            exit(-1);
                        }
                        
                        close(i2c_file);
                        return 0;
                    } else if(ledNum == 2) {
                        ledOutColour = colourArrayB[ledColour];
                        if(get_i2c_register(i2c_file, addr, MCP23017_REG_OLATB, &ledCurrent)) {
                            perror("Unable to get register B");
                            close(i2c_file);
                            exit(-1);                        
                        }
                        
                        ledCurrent &= 0xF0;
                        ledCurrent |= ledOutColour;
                        
                        if(set_i2c_register(i2c_file, addr, MCP23017_REG_OLATB, ledCurrent)) {
                            perror("Unable to set register B");
                            close(i2c_file);
                            exit(-1);
                        }
                        
                        close(i2c_file);
                        return 0;
                    } else if(ledNum == 3) {
                        ledOutColour = colourArrayB[ledColour];
                        if(get_i2c_register(i2c_file, addr, MCP23017_REG_OLATB, &ledCurrent)) {
                            perror("Unable to get register B");
                            close(i2c_file);
                            exit(-1);                        
                        }
                        
                        ledCurrent &= 0x0F;
                        ledOutColour <<= 4;
                        ledCurrent |= ledOutColour;
                        
                        if(set_i2c_register(i2c_file, addr, MCP23017_REG_OLATB, ledCurrent)) {
                            perror("Unable to set register B");
                            close(i2c_file);
                            exit(-1);
                        }
                        
                        close(i2c_file);
                        return 0;
                    }
                } else {
                    perror("Invalid colour");
                    close(i2c_file);
                    return -5;
                }
            } else {
                perror("Invalid LED number");
                close(i2c_file);
                return -4;
            }
        } else {
            perror("Address out of range");
            close(i2c_file);
            return -3;
        }
    } else {
        perror("Incorrect syntax");
        close(i2c_file);
        return -1;
    }
}