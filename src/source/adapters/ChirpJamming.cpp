//
// Created by tang on 24-3-27.
//

#include "ChirpJamming.h"

ChirpJamming::ChirpJamming(unsigned int in_streams, unsigned int out_streams, double samp_rate, double min_freq,
                           double max_freq, double period, ChirpType type)
                           : in_streams_(in_streams), out_streams_(out_streams),
                           samplingFrequency_(samp_rate), minFrequency_(min_freq), maxFrequency_(max_freq),
                           period_(period), type_(type)
                           {
    block_ = Chirp::make(samplingFrequency_, min_freq, max_freq, period_, type);

}

void ChirpJamming::connect(gr::top_block_sptr top_block) {
    top_block->connect(block_);
}

void ChirpJamming::disconnect(gr::top_block_sptr top_block) {
    top_block->disconnect(block_);
}

gr::basic_block_sptr ChirpJamming::get_left_block() {
    return block_;
}

gr::basic_block_sptr ChirpJamming::get_right_block() {
    return block_;
}