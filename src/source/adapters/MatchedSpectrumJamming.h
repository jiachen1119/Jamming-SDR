//
// Created by tang on 24-3-28.
//

#ifndef JAMMING_SDR_MATCHEDSPECTRUMJAMMING_H
#define JAMMING_SDR_MATCHEDSPECTRUMJAMMING_H

#include "BlockInterface.h"
#include "MatchedSpectrum.h"

class MatchedSpectrumJamming : public BlockInterface{
public:
    MatchedSpectrumJamming(unsigned int in_streams,
                           unsigned int out_streams,
                           double samp_rate,
                           double chip_rate);
    ~MatchedSpectrumJamming() override = default;
    inline size_t item_size() override
    {
        return sizeof(gr_complex);
    }
    void connect(gr::top_block_sptr top_block) override;
    void disconnect(gr::top_block_sptr top_block) override;
    gr::basic_block_sptr get_left_block() override;
    gr::basic_block_sptr get_right_block() override;

private:
    std::shared_ptr<MatchedSpectrum> block_;
    unsigned int in_streams_;
    unsigned int out_streams_;

    double samplingFrequency_;
    double chipRate_;
};


#endif //JAMMING_SDR_MATCHEDSPECTRUMJAMMING_H
