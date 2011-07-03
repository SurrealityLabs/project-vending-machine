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
    
    if(argc == 2) {
        int addr = strtol(argv[1], NULL, 0);
        
        if((addr >= 0) && (addr < 8)) {
            addr += MCP23017_BASE_ADDR;
            addr *= 2;
            if(set_i2c_register(i2c_file, addr, MCP23017_REG_IODIRA, 0x11)) {
                perror("Unable to set register A");
                close(i2c_file);
                exit(-1);
            }
            if(set_i2c_register(i2c_file, addr, MCP23017_REG_IODIRB, 0x88)) {
                perror("Unable to set register B");
                close(i2c_file);
                exit(-1);
            }
            close(i2c_file);
            return 0;
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