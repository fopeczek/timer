/*
 * example.h
 *
 *  Created on: Oct 3, 2020
 *      Author: mikolaj
 */

#ifndef EXAMPLE_H_
#define EXAMPLE_H_

#include "Arduino.h"


// Class representing a particular time and date.
class Time {
 public:
  enum Day {
    kSunday    = 1,
    kMonday    = 2,
    kTuesday   = 3,
    kWednesday = 4,
    kThursday  = 5,
    kFriday    = 6,
    kSaturday  = 7
  };

  // Creates a Time object with a given time.
  //
  // Args:
  //   yr: year. Range: {2000, ..., 2099}.
  //   mon: month. Range: {1, ..., 12}.
  //   date: date (of the month). Range: {1, ..., 31}.
  //   hr: hour. Range: {0, ..., 23}.
  //   min: minutes. Range: {0, ..., 59}.
  //   sec: seconds. Range: {0, ..., 59}.
  //   day: day of the week. Sunday is 1. Range: {1, ..., 7}.
  Time(uint16_t yr, uint8_t mon, uint8_t date,
       uint8_t hr, uint8_t min, uint8_t sec,
       Day day);

  uint8_t sec;
  uint8_t min;
  uint8_t hr;
  uint8_t date;
  uint8_t mon;
  Day day;
  uint16_t yr;
};


#endif /* EXAMPLE_H_ */

//Added by Sloeber 
#pragma once
