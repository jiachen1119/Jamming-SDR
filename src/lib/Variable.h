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
    QString type;
};

struct SingleToneStruct{
    double sampling_freq;
    double wave_freq;
    double ampl;
};

struct SquareStruct{
    double sampling_freq;
    double wave_freq;
    double ampl;
};

struct TriangeStruct{
    double sampling_freq;
    double wave_freq;
    double ampl;
};

struct SawToothStruct{
    double sampling_freq;
    double wave_freq;
    double ampl;
};

struct MatchedStruct{
    double sampling_freq;
    double chip_rate;
};

#endif //JAMMING_SDR_JAMMINGTYPE_H
