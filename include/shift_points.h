#ifndef SHIFT_POINTS_H
#define SHIFT_POINTS_H
#include <map>
#include <stdint.h>
/// @brief EDIT THESE SHIFT POINTS TO CHANGE WHEN SHIFT LIGHT BLINKS
const std::map<uint8_t, uint16_t> shiftpointmap = 
{
    {0,11000},
    {1,11000},
    {2,11000},
    {3,11000},
    {4,11000},
    {5,11000},
    {6,11000}
};
#endif