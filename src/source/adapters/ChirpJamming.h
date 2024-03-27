//
// Created by tang on 24-3-27.
//

#ifndef JAMMING_SDR_CHIRPJAMMING_H
#define JAMMING_SDR_CHIRPJAMMING_H

#include "BlockInterface.h"
#include "Chirp.h"

class ChirpJamming : public BlockInterface{
public:
    ChirpJamming(unsigned int in_streams,
                 unsigned int out_streams,
                 double samp_rate,
                 double min_freq,
                 double max_freq,
                 double period,
                 ChirpType type);
    ~ChirpJamming() override = default;
    inline size_t item_size() override
    {
        return sizeof(gr_complex);
    }

    void connect(gr::top_block_sptr top_block) override;
    void disconnect(gr::top_block_sptr top_block) override;
    gr::basic_block_sptr get_left_block() override;
    gr::basic_block_sptr get_right_block() override;

private:
    std::shared_ptr<Chirp> block_;

    unsigned int in_streams_;
    unsigned int out_streams_;

    double samplingFrequency_;
    double period_;
    double maxFrequency_;
    double minFrequency_;
    ChirpType type_;

};


#endif //JAMMING_SDR_CHIRPJAMMING_H
