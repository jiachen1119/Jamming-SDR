//
// Created by tang on 24-3-28.
//

#include "MatchedSpectrumJamming.h"

MatchedSpectrumJamming::MatchedSpectrumJamming(unsigned int in_streams, unsigned int out_streams, double samp_rate,
                                               double chip_rate): in_streams_(in_streams), out_streams_(out_streams),
                                               samplingFrequency_(samp_rate), chipRate_(chip_rate)
{
    block_ = MatchedSpectrum::make(samplingFrequency_, chipRate_);
}
void MatchedSpectrumJamming::connect(gr::top_block_sptr top_block) {
    top_block->connect(block_);
}

void MatchedSpectrumJamming::disconnect(gr::top_block_sptr top_block) {
    top_block->disconnect(block_);
}

gr::basic_block_sptr MatchedSpectrumJamming::get_left_block() {
    return block_;
}

gr::basic_block_sptr MatchedSpectrumJamming::get_right_block() {
    return block_;
}