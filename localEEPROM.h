// This file should be copied to the folder containing the sketch

#ifndef LOCALEEPROM_H
#define LOCALEEPROM_H

// ========== Change the following value as required ==========

// Number of EEPROM bytes required by this sketch, in decimal
#define SKETCH_EEPROM_SIZE 20

// ========== DO NOT CHANGE ANYTHING BEYOND THIS POINT ==========
#include "eepromInRAM.h"
#define EEPROM_BEGIN begin(SKETCH_EEPROM_SIZE)

#endif
