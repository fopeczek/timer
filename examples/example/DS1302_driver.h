#include<stdint.h>

void get_time(uint8_t& sec, uint8_t& min, uint8_t& h);
void set_time(uint8_t sec, uint8_t min, uint8_t h);

void setup_pins(int kCePin   = 5, int kIoPin =6, int kSclkPin=7);
// kCePin = 5;  // Chip Enable RST
//kIoPin   = 6;  // Input/Output DAT
// kSclkPin = 7;  // Serial Clock CLK

//Added by Sloeber 
#pragma once
