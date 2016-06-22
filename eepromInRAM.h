#ifndef EEPROMMLXXXP_H
#define EEPROMMLXXXP_H

#include "Arduino.h"

// open() return values
#define EEPROM_ALLOCATED 1
#define EEPROM_ERROR_ALLOCATE -1

class ArduboyEeprom
{
  public:
    int begin(unsigned int length);

    uint8_t read(unsigned int address);
    boolean write(unsigned int address, uint8_t data);
    boolean read(unsigned int address, uint8_t *buffer, size_t size);
    boolean write(unsigned int address, uint8_t *buffer, size_t size);

  private:
    uint8_t *eeRam;
    unsigned int eeLength;
};

#endif
