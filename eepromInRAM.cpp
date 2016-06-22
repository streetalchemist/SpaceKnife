#include "eepromInRAM.h"

int ArduboyEeprom::begin(unsigned int length) {
  eeLength = length;

  // check bounds
  if ((eeRam = (uint8_t*) malloc(eeLength)) == NULL) {
    return EEPROM_ERROR_ALLOCATE;
  }

  return EEPROM_ALLOCATED;
}

uint8_t ArduboyEeprom::read(unsigned int address) {
  if (address >= eeLength) {
    return 0;
  }

  return eeRam[address];
}

boolean ArduboyEeprom::write(unsigned int address, uint8_t data) {
  if (address >= eeLength) {
    return false;
  }

  eeRam[address] = data;
  return true;
}

boolean ArduboyEeprom::read(unsigned int address, uint8_t *buffer, size_t size) {
  if ((address + size) > eeLength) {
    return false;
  }

  memcpy(buffer, &eeRam[address], size);
  return true;
}

boolean ArduboyEeprom::write(unsigned int address, uint8_t *buffer, size_t size) {
  if ((address + size) > eeLength) {
    return false;
  }

  memcpy(&eeRam[address], buffer, size);
  return true;
}

