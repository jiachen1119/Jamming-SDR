//
// Created by tang on 24-3-22.
//

#ifndef JAMMING_SDR_SIGNALSOURCE_H
#define JAMMING_SDR_SIGNALSOURCE_H

#include <gnuradio/runtime_types.h>
#include <pmt/pmt.h>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <gnuradio/top_block.h>
#include <gnuradio/analog/sig_source.h>
#include <gnuradio/analog/sig_source_waveform.h>
#include "ValveBlock.h"
#include "BlockInterface.h"

class SignalSource : public BlockInterface{
public:
    SignalSource(unsigned int in_streams,
                 unsigned int out_streams,
                 gr::analog::gr_waveform_t waveform,
                 double sample_freq,
                 double wave_freq,
                 double ampl,
                 gr_complex offset,
                 float phase);

    ~SignalSource() = default;

    inline size_t item_size() override
    {
        return sizeof(gr_complex);
    }

    void connect(gr::top_block_sptr top_block) override;
    void disconnect(gr::top_block_sptr top_block) override;
    gr::basic_block_sptr get_left_block() override;
    gr::basic_block_sptr get_right_block() override;

private:
    gr::analog::sig_source<gr_complex>::sptr block_;
    gr::analog::gr_waveform_t waveform_;

    unsigned int in_streams_;
    unsigned int out_streams_;

    double sample_frequency_;
    double wave_frequency_;
    double amplitude_;
    gr_complex offset_;
    float phase_;

};


#endif //JAMMING_SDR_SIGNALSOURCE_H
