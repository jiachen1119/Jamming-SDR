//
// Created by tang on 24-3-22.
//

#include "SignalSource.h"

SignalSource::SignalSource(unsigned int in_streams, unsigned int out_streams, gr::analog::gr_waveform_t waveform,
                           double sample_freq, double wave_freq, double ampl, gr_complex offset, float phase)
        : in_streams_(in_streams), out_streams_(out_streams), waveform_(waveform), sample_frequency_(sample_freq),
        wave_frequency_(wave_freq),amplitude_(ampl), offset_(offset), phase_(phase)
                           {
    block_ = gr::analog::sig_source<gr_complex>::make(sample_frequency_,
                                                      waveform_,wave_frequency_,
                                                      amplitude_,offset_,phase_);
}

void SignalSource::connect(gr::top_block_sptr top_block) {
    top_block->connect(block_);
}

void SignalSource::disconnect(gr::top_block_sptr top_block) {
    top_block->disconnect(block_);
}

gr::basic_block_sptr SignalSource::get_left_block() {
    return block_;
}

gr::basic_block_sptr SignalSource::get_right_block() {
    return block_;
}



