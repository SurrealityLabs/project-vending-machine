#include "vend_i2c.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int i2c_file;

    // Open a connection to the I2C userspace control file.
    if ((i2c_file = open(I2C_FILE_NAME, O_RDWR)) < 0) {
        perror("Unable to open i2c control file");
        exit(-1);
    }
    
    if(argc == 3) {
        int addr = strtol(argv[1], NULL, 0);
        int switchNum = strtol(argv[2], NULL, 0);
        
        if((addr >= 0) && (addr < 8)) {
            addr += MCP23017_BASE_ADDR;
            addr *= 2;
            
            if((switchNum >= 0) && (switchNum < 4)) {
                unsigned char portVal;
                if(switchNum == 0) {
                    if(get_i2c_register(i2c_file, addr, MCP23017_REG_GPIOA, &portVal)) {
                        perror("Unable to get register A");
                        close(i2c_file);
                        exit(-1);                        
                    }
                    if(portVal & 0x01) {
                        close(i2c_file);
                        return 1;
                    } else {
                        close(i2c_file);
                        return 0;
                    }
                } else if(switchNum == 1) {
                    if(get_i2c_register(i2c_file, addr, MCP23017_REG_GPIOA, &portVal)) {
                        perror("Unable to get register A");
                        close(i2c_file);
                        exit(-1);                        
                    }
                    if(portVal & 0x10) {
                        close(i2c_file);
                        return 1;
                    } else {
                        close(i2c_file);
                        return 0;
                    }                    
                } else if(switchNum == 2) {
                    if(get_i2c_register(i2c_file, addr, MCP23017_REG_GPIOB, &portVal)) {
                        perror("Unable to get register B");
                        close(i2c_file);
                        exit(-1);                        
                    }
                    if(portVal & 0x08) {
                        close(i2c_file);
                        return 1;
                    } else {
                        close(i2c_file);
                        return 0;
                    }
                } else if(switchNum == 3) {
                    if(get_i2c_register(i2c_file, addr, MCP23017_REG_GPIOB, &portVal)) {
                        perror("Unable to get register B");
                        close(i2c_file);
                        exit(-1);                        
                    }
                    if(portVal & 0x80) {
                        close(i2c_file);
                        return 1;
                    } else {
                        close(i2c_file);
                        return 0;
                    }
                }
            } else {
                perror("Invalid switch number");
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