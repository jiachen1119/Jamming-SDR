//
// Created by tang on 24-3-27.
//

#ifndef JAMMING_SDR_JAMMINGTYPE_H
#define JAMMING_SDR_JAMMINGTYPE_H
#include "Chirp.h"

typedef enum{
    SingleTone,
    Chirp,
    Square,
    Triangle,
    SawTooth
}JammingType;

struct ChirpStruct{
    double sampling_freq;
    double min_freq;
    double max_freq;
    double period;
    ChirpType type;
};

struct SingleToneStruct{
    double sampling_freq;
    double wave_freq;
    double ampl;
};

#endif //JAMMING_SDR_JAMMINGTYPE_H
